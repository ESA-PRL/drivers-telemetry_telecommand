#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

#include "ctrl_state.h"
#include "comm.h"

#include <stdio.h>

static int ctrl_time = 0;

void CommTmServer::orcGetTmMsg(std::string &tmmsg) {
  
 // State variables definition
 double State[MAX_STATE_SIZE];
 double ADEState[MAX_STATE_SIZE]; // Needed?
 double SAState[MAX_STATE_SIZE];  // Needed?
 double PanCamState[MAX_STATE_SIZE];
 double MastState[MAX_STATE_SIZE];
 double GNCState[MAX_STATE_SIZE];

  //
  // dummy initialisation of the TM
  //
  for (int i=0; i<MAX_STATE_SIZE; i++) {
    State[i] = 0.0;
    ADEState[i] = 0.0;
    SAState[i] = 0.0;
    PanCamState[i] = 0.0;
    MastState[i] = 0.0;
    GNCState[i] = 0.0;
  }


  if ( prr->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ){
         std::cout << "Error getting GNCState" << std::endl;
  }

  if ( prr->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ){
         std::cout << "Error getting MastState" << std::endl;
  }

  if ( prr->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ){
         std::cout << "Error getting SAState" << std::endl;
  }


  char buffer[1024];

  //ctrl_time = prr->Clock->GetTime(); 
  ctrl_time + 200; // 0.2 sec in msec

  tmmsg = "TmPacket MODE ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.0lf;\n", GNCState[7]);
  tmmsg += buffer;

  
  //
  // MAST_STATE
  //
  tmmsg += "TmPacket MAST_STATE ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf,%.2lf %.2lf,%.2lf,%.2lf %.2lf;\n", 
	  MastState[MAST_STATUS_INDEX], 
	  MastState[MAST_CURRENT_Q1_INDEX],
	  MastState[MAST_CURRENT_Q2_INDEX],
	  MastState[MAST_CURRENT_Q3_INDEX],
	  MastState[MAST_ACTION_RET_INDEX],
	  MastState[MAST_ACTION_ID_INDEX]);
  tmmsg += buffer;

  //
  // SA_STATE
  //
  tmmsg += "TmPacket SA_STATE ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf;\n", 
	  SAState[SA_STATUS_INDEX], 
	  SAState[SA_LEFT_PRIMARY_STATUS_INDEX], 
	  SAState[SA_LEFT_SECONDARY_STATUS_INDEX],
	  SAState[SA_RIGHT_PRIMARY_STATUS_INDEX], 
	  SAState[SA_RIGHT_SECONDARY_STATUS_INDEX], 
	  SAState[SA_CURRENT_Q1_INDEX],
	  SAState[SA_CURRENT_Q2_INDEX],
	  SAState[SA_CURRENT_Q3_INDEX],
	  SAState[SA_CURRENT_Q4_INDEX],
	  SAState[SA_ACTION_ID_INDEX]);
  tmmsg += buffer;

  //
  // ADE_STATE
  //
  tmmsg += "TmPacket ADE_STATE ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf;\n", 
	  ADEState[ADE_STATUS_LEFT_INDEX], 
	  ADEState[ADE_STATUS_RIGHT_INDEX], 
	  ADEState[HDRM_SA_LEFT_1_STATUS_INDEX],
	  ADEState[HDRM_SA_LEFT_2_STATUS_INDEX], 
	  ADEState[HDRM_SA_LEFT_3_STATUS_INDEX], 
	  ADEState[HDRM_SA_RIGHT_1_STATUS_INDEX],
	  ADEState[HDRM_SA_RIGHT_2_STATUS_INDEX],
	  ADEState[HDRM_SA_RIGHT_3_STATUS_INDEX],
	  ADEState[ADE_ACTION_ID_INDEX],
	  ADEState[ADE_ACTION_RET_INDEX]);
  tmmsg += buffer;
}
