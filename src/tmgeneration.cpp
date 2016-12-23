#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

#include "ctrl_state.h"
#include "comm.h"

#include <stdio.h>

static int ctrl_time = 0;

static int wac_l_prev_image = 0;
static int wac_r_prev_image = 0;
static int wac_stereo_prev_image = 0;
static int floc_r_prev_image = 0;
static int floc_l_prev_image = 0;
static int floc_stereo_prev_image = 0;
static int rloc_l_prev_image = 0;
static int rloc_r_prev_image = 0;
static int rloc_stereo_prev_image = 0;

// Copy of las state variables sent
//static double lastState[MAX_STATE_SIZE];
static double lastADEState[MAX_STATE_SIZE];
static double lastSAState[MAX_STATE_SIZE];
static double lastPanCamState[MAX_STATE_SIZE];
static double lastMastState[MAX_STATE_SIZE];
static double lastGNCState[MAX_STATE_SIZE];

static bool first_time=false;

void CommTmServer::orcGetTmMsg(std::string &tmmsg) {

 // State variables definition
 //double State[MAX_STATE_SIZE];
 double ADEState[MAX_STATE_SIZE];
 double SAState[MAX_STATE_SIZE];
 double PanCamState[MAX_STATE_SIZE];
 double MastState[MAX_STATE_SIZE];
 double GNCState[MAX_STATE_SIZE];
 // flags for state changes

 bool ADEStateChanged;
 bool SAStateChanged;
 bool PanCamStateChanged;
 bool MastStateChanged;
 bool GNCStateChanged;


  //
  // dummy initialisation of the TM
  //
  if (first_time==false){
  for (int i=0; i<MAX_STATE_SIZE; i++) {
    //State[i] = 0.0;
    ADEState[i] = 0.0;
    SAState[i] = 0.0;
    PanCamState[i] = 0.0;
    MastState[i] = 0.0;
    GNCState[i] = 0.0;
    //lastState[i] = 0.0;
    lastADEState[i] = -100.0;
    lastSAState[i] = -100.0;
    lastPanCamState[i] = -100.0;
    lastMastState[i] = -100.0;
    lastGNCState[i] = -100.0;
  }
  first_time=true;
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
  
  if ( prr->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ){
         std::cout << "Error getting SAState" << std::endl;
  }

  if ( prr->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
         std::cout << "Error getting SAState" << std::endl;
  }


  char buffer[1024];

  //ctrl_time = prr->Clock->GetTime(); 
  ctrl_time += 1000; // 1.02 sec in msec
  
  //
  // GNC_STATE
  //
  GNCStateChanged=false;
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      if (GNCState[i]!=lastGNCState[i])
          GNCStateChanged=true;
  }
  if (GNCStateChanged){
  tmmsg = "TmPacket GNC_STATE ";
//  sprintf(buffer, "%.2lf %.2lf %.2lf %.2lf %d:", GNCState[GNC_ROVER_POSEX_INDEX], GNCState[GNC_ROVER_POSEY_INDEX], MastState[MAST_CURRENT_Q2_INDEX], MastState[MAST_CURRENT_Q3_INDEX], ctrl_time);
  sprintf(buffer, " %d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf;\n",
      GNCState[GNC_OPER_MODE_INDEX],
      GNCState[GNC_ROVER_POSEX_INDEX],
      GNCState[GNC_ROVER_POSEY_INDEX],
      GNCState[GNC_ROVER_POSEZ_INDEX],
      GNCState[GNC_ROVER_POSERX_INDEX],
      GNCState[GNC_ROVER_POSERY_INDEX],
      GNCState[GNC_ROVER_POSERZ_INDEX],
      GNCState[GNC_ROVER_BEMA_Q1_INDEX],
      GNCState[GNC_ROVER_BEMA_Q2_INDEX],
      GNCState[GNC_ROVER_BEMA_Q3_INDEX],
      GNCState[GNC_ROVER_BEMA_Q4_INDEX],
      GNCState[GNC_ROVER_BEMA_Q5_INDEX],
      GNCState[GNC_ROVER_BEMA_Q6_INDEX],
      GNCState[GNC_ACTION_RET_INDEX],
      GNCState[GNC_ACTION_ID_INDEX]
      );
  tmmsg += buffer;
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      lastGNCState[i]=GNCState[i];
  }

  //
  // MAST_STATE
  //
  MastStateChanged=false;
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      if (MastState[i]!=lastMastState[i])
          MastStateChanged=true;
  }
  if (MastStateChanged){
  tmmsg += "TmPacket MAST_STATE ";
  //sprintf(buffer, "%.2lf %.2lf %.2lf %.2lf %d:", GNCState[GNC_ROVER_POSEX_INDEX], GNCState[GNC_ROVER_POSEY_INDEX], MastState[MAST_CURRENT_Q2_INDEX], MastState[MAST_CURRENT_Q3_INDEX], ctrl_time);
  sprintf(buffer, " %d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf;\n",
      MastState[MAST_STATUS_INDEX],
      MastState[MAST_CURRENT_Q1_INDEX],
      MastState[MAST_CURRENT_Q2_INDEX],
      MastState[MAST_CURRENT_Q3_INDEX],
      MastState[MAST_ACTION_RET_INDEX],
      MastState[MAST_ACTION_ID_INDEX]);
  tmmsg += buffer;
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      lastMastState[i]=MastState[i];
  }

  //
  // SA_STATE
  //
  SAStateChanged=false;
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      if (SAState[i]!=lastSAState[i])
          SAStateChanged=true;
  }
  if (SAStateChanged){
  tmmsg += "TmPacket SA_STATE ";
  //sprintf(buffer, "%.2lf %.2lf %.2lf %.2lf %d:", GNCState[GNC_ROVER_POSEX_INDEX], GNCState[GNC_ROVER_POSEY_INDEX], MastState[MAST_CURRENT_Q2_INDEX], MastState[MAST_CURRENT_Q3_INDEX], ctrl_time);
  sprintf(buffer, " %d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf;\n", 
	  SAState[SA_STATUS_INDEX], 
	  SAState[SA_LEFT_PRIMARY_STATUS_INDEX], 
	  SAState[SA_LEFT_SECONDARY_STATUS_INDEX],
	  SAState[SA_RIGHT_PRIMARY_STATUS_INDEX], 
	  SAState[SA_RIGHT_SECONDARY_STATUS_INDEX], 
	  SAState[SA_CURRENT_Q1_INDEX],
	  SAState[SA_CURRENT_Q2_INDEX],
	  SAState[SA_CURRENT_Q3_INDEX],
	  SAState[SA_CURRENT_Q4_INDEX],
	  SAState[SA_ACTION_RET_INDEX],
	  SAState[SA_ACTION_ID_INDEX]);
  tmmsg += buffer;
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      lastSAState[i]=SAState[i];
  }

  //
  // ADE_STATE
  //
  ADEStateChanged=false;
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      if (ADEState[i]!=lastADEState[i]) {
          ADEStateChanged=true;
	}
  }
  if (ADEStateChanged){
  tmmsg += "TmPacket ADE_STATE ";
  //sprintf(buffer, "%.2lf %.2lf %.2lf %.2lf %d:", GNCState[GNC_ROVER_POSEX_INDEX], GNCState[GNC_ROVER_POSEY_INDEX], MastState[MAST_CURRENT_Q2_INDEX], MastState[MAST_CURRENT_Q3_INDEX], ctrl_time);
  sprintf(buffer, " %d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf;\n", 
	  ADEState[ADE_STATUS_LEFT_INDEX], 
	  ADEState[ADE_STATUS_RIGHT_INDEX], 
	  ADEState[HDRM_BODY_1_STATUS_INDEX],
	  ADEState[HDRM_BODY_2_STATUS_INDEX], 
	  ADEState[HDRM_BODY_3_STATUS_INDEX], 
	  ADEState[HDRM_DRILL_1_STATUS_INDEX],
	  ADEState[HDRM_DRILL_2_STATUS_INDEX],
	  ADEState[HDRM_MAST_STATUS_INDEX],
	  ADEState[HDRM_SA_LEFT_1_STATUS_INDEX],
	  ADEState[HDRM_SA_LEFT_2_STATUS_INDEX], 
	  ADEState[HDRM_SA_LEFT_3_STATUS_INDEX], 
	  ADEState[HDRM_SA_RIGHT_1_STATUS_INDEX],
	  ADEState[HDRM_SA_RIGHT_2_STATUS_INDEX],
	  ADEState[HDRM_SA_RIGHT_3_STATUS_INDEX],
	  ADEState[HDRM_UMBILICAL_1_STATUS_INDEX],
	  ADEState[HDRM_UMBILICAL_2_STATUS_INDEX], 
	  ADEState[HDRM_WHEEL_FL_STATUS_INDEX],
	  ADEState[HDRM_WHEEL_FR_STATUS_INDEX], 
	  ADEState[HDRM_WHEEL_ML_STATUS_INDEX], 
	  ADEState[HDRM_WHEEL_MR_STATUS_INDEX],
	  ADEState[HDRM_WHEEL_RL_STATUS_INDEX],
	  ADEState[HDRM_WHEEL_RR_STATUS_INDEX],
	  ADEState[ADE_ACTION_RET_INDEX],
	  ADEState[ADE_ACTION_ID_INDEX]);
  tmmsg += buffer;
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      lastADEState[i]=ADEState[i];
  }

  //
  // PanCam State
  //
  
  if ( wac_l_prev_image == PanCamState[PANCAM_WAC_L_INDEX] )
  {
	PanCamState[PANCAM_WAC_L_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
            std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( wac_r_prev_image == PanCamState[PANCAM_WAC_R_INDEX] )
  {
	PanCamState[PANCAM_WAC_R_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
           std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( wac_stereo_prev_image == PanCamState[PANCAM_PAN_STEREO_INDEX] )
  {
	PanCamState[PANCAM_PAN_STEREO_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
            std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( floc_l_prev_image == PanCamState[LOCCAM_FLOC_L_INDEX] )
  {
	PanCamState[LOCCAM_FLOC_L_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
           std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( floc_r_prev_image == PanCamState[LOCCAM_FLOC_R_INDEX] )
  {
	PanCamState[LOCCAM_FLOC_R_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
            std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( floc_stereo_prev_image == PanCamState[LOCCAM_FLOC_STEREO_INDEX] )
  {
	PanCamState[LOCCAM_FLOC_STEREO_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
           std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( rloc_l_prev_image == PanCamState[LOCCAM_RLOC_L_INDEX] )
  {
	PanCamState[LOCCAM_RLOC_L_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
           std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( rloc_r_prev_image == PanCamState[LOCCAM_RLOC_R_INDEX] )
  {
	PanCamState[LOCCAM_RLOC_R_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
            std::cout << "Error setting SAState" << std::endl;
        }
  }
  if ( rloc_stereo_prev_image == PanCamState[LOCCAM_RLOC_STEREO_INDEX] )
  {
	PanCamState[LOCCAM_RLOC_STEREO_INDEX] = 0;
        if ( prr->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ){
           std::cout << "Error setting SAState" << std::endl;
        }
  }
 
  wac_l_prev_image=PanCamState[PANCAM_WAC_L_INDEX];
  wac_r_prev_image=PanCamState[PANCAM_WAC_R_INDEX];
  wac_stereo_prev_image=PanCamState[PANCAM_PAN_STEREO_INDEX];
  floc_l_prev_image=PanCamState[LOCCAM_FLOC_L_INDEX];
  floc_r_prev_image=PanCamState[LOCCAM_FLOC_R_INDEX];
  floc_stereo_prev_image=PanCamState[LOCCAM_FLOC_STEREO_INDEX];
  rloc_l_prev_image=PanCamState[LOCCAM_RLOC_L_INDEX];
  rloc_r_prev_image=PanCamState[LOCCAM_RLOC_R_INDEX];
  rloc_stereo_prev_image=PanCamState[LOCCAM_RLOC_STEREO_INDEX];
 
  PanCamStateChanged=false;
  for (int i=0; i<MAX_STATE_SIZE; i++) {
     if (PanCamState[i]!=lastPanCamState[i])
         PanCamStateChanged=true;
  }
  if (PanCamStateChanged){
  tmmsg += "TmPacket PANCAM_STATE ";
  //sprintf(buffer, "%.2lf %.2lf %.2lf %.2lf %d:", GNCState[GNC_ROVER_POSEX_INDEX], GNCState[GNC_ROVER_POSEY_INDEX], MastState[MAST_CURRENT_Q2_INDEX], MastState[MAST_CURRENT_Q3_INDEX], ctrl_time);
  sprintf(buffer, " %d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf;\n",
      PanCamState[PANCAM_OPER_MODE_INDEX],
      PanCamState[PANCAM_WAC_L_INDEX],
      PanCamState[PANCAM_WAC_R_INDEX],
      PanCamState[PANCAM_PAN_STEREO_INDEX],
      PanCamState[LOCCAM_FLOC_L_INDEX],
      PanCamState[LOCCAM_FLOC_R_INDEX],
      PanCamState[LOCCAM_FLOC_STEREO_INDEX],
      PanCamState[LOCCAM_RLOC_L_INDEX],
      PanCamState[LOCCAM_RLOC_R_INDEX],
      PanCamState[LOCCAM_RLOC_STEREO_INDEX],
      PanCamState[PANCAM_ACTION_RET_INDEX],
      PanCamState[PANCAM_ACTION_ID_INDEX]);
  tmmsg += buffer;
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
      lastPanCamState[i]=PanCamState[i];
  }
 
    if (activemqTMSender->isConnected) {
       
      try {
int seq = 1;
  struct timeval tp;
  gettimeofday(&tp, NULL);
  long long time1 = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;

	std::auto_ptr<TextMessage> mastMessage(activemqTMSender->sessionMonitor->createTextMessage
					      ("I'm a Gnc message"));
	mastMessage->setIntProperty("Status",2);
	mastMessage->setFloatProperty("Deploy joint",7);
	mastMessage->setFloatProperty("Pan",8);
	mastMessage->setFloatProperty("Tilt",9);;
	mastMessage->setIntProperty("iter",seq);
	mastMessage->setIntProperty("Action status",1);
	mastMessage->setIntProperty("Action Id",3);
	mastMessage->setLongProperty("time",time1);
	activemqTMSender->mastProducerMonitoring->send(mastMessage.get()); 


	std::auto_ptr<TextMessage> gncexoterMessage(activemqTMSender->sessionMonitor->createTextMessage
					      ("I'm a gncexoter message"));
	gncexoterMessage->setIntProperty("Status",2);
	gncexoterMessage->setFloatProperty("X",1);
	gncexoterMessage->setFloatProperty("Y",2);
	gncexoterMessage->setFloatProperty("Z",3);
	gncexoterMessage->setFloatProperty("RX",4);
	gncexoterMessage->setFloatProperty("RY",5);
	gncexoterMessage->setFloatProperty("RZ",6);
	gncexoterMessage->setFloatProperty("Bema Q1",7);
	gncexoterMessage->setFloatProperty("Bema Q2",8);
	gncexoterMessage->setFloatProperty("Bema Q3",9);;
	gncexoterMessage->setFloatProperty("Bema Q4",10);
	gncexoterMessage->setFloatProperty("Bema Q5",11);
	gncexoterMessage->setFloatProperty("Bema Q6",12);
	gncexoterMessage->setIntProperty("Action status",1);
	gncexoterMessage->setIntProperty("Action Id",3);
	gncexoterMessage->setIntProperty("iter",seq);
	gncexoterMessage->setLongProperty("time",time1);
	activemqTMSender->gncexoterProducerMonitoring->send(gncexoterMessage.get()); 


	std::auto_ptr<TextMessage> pancamMessage(activemqTMSender->sessionMonitor->createTextMessage
					      ("I'm a pancam message"));
	pancamMessage->setIntProperty("PANCAM Status",2);
	pancamMessage->setFloatProperty("WAC_L",1);
	pancamMessage->setFloatProperty("WAC_R",2);
	pancamMessage->setFloatProperty("WAC Stereo",3);
	pancamMessage->setFloatProperty("FLOC_L",4);
	pancamMessage->setFloatProperty("FLOC_R",5);
	pancamMessage->setFloatProperty("FLOC Stereo",6);
	pancamMessage->setFloatProperty("RLOC_L",7);
	pancamMessage->setFloatProperty("LOC_R",8);
	pancamMessage->setFloatProperty("RLOC Stereo",9);
	pancamMessage->setIntProperty("Action status",1);
	pancamMessage->setIntProperty("Action Id",3);
	pancamMessage->setIntProperty("iter",seq);
	pancamMessage->setLongProperty("time",time1);
	activemqTMSender->pancamProducerMonitoring->send(pancamMessage.get()); 


	std::auto_ptr<TextMessage> saMessage(activemqTMSender->sessionMonitor->createTextMessage
					      ("I'm a sa message"));
	saMessage->setIntProperty("Status",2);
	saMessage->setFloatProperty("Q1",7);
	saMessage->setFloatProperty("Q2",8);
	saMessage->setFloatProperty("Q3",9);
	saMessage->setFloatProperty("Q4",10);
	saMessage->setIntProperty("Action status",1);
	saMessage->setIntProperty("Action Id",3);
	saMessage->setIntProperty("iter",seq);
	saMessage->setLongProperty("time",time1);
	activemqTMSender->saProducerMonitoring->send(saMessage.get()); 
 
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cout << "tmgeneration (ActiveMQTMSender) - exception detected" << std::endl;
	activemqTMSender->isConnected = false;
      }
    }
}


