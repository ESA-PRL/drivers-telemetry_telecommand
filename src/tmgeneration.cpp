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
  for (int i=0; i<CTRL_MAX_STATE_SIZE; i++) {
    ctrlstate[i] = i;
    rrpstate[i] = i;
    ptustate[i] = i;
    gncstate[i] = i;
    navcamstate[i] = i;
    pancamstate[i] = i;
    hazcamstate[i] = i;
    minicamstate[i] = i;
    tofcamstate[i] = i;
    inclinostate[i] = i;
    ttcstate[i] = i;
  }


  if ( prr->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ){
         std::cout << "Error getting GNCState" << std::endl;
  }

  char buffer[1024];

  ctrl_time = ctrl_time + 200; // 0.2 sec in msec

  tmmsg = "TmPacket MODE ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.0lf;\n", GNCState[7]);
  tmmsg += buffer;

/*
  //
  // ACT_STAT
  //
  tmmsg += "TmPacket ACT_STAT ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.0lf;\n", 1.0);
  tmmsg += buffer;

  //
  // ACT_ID
  //
  tmmsg += "TmPacket ACT_ID ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.0lf;\n", 1.0);
  tmmsg += buffer;

  //
  // ROVER_STAT
  //
  tmmsg += "TmPacket ROV_STAT ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", gncstate[LRM_OPER_MODE_INDEX]);
  tmmsg += buffer;

  tmmsg += "TmPacket ROV_MEAS ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSEX_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSEY_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSERZ_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", 0.7);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", 45.7);
  tmmsg += buffer;


  tmmsg += "TmPacket WHE_MEAS ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_DRIVING_SPEED_FL_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_DRIVING_SPEED_FR_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_DRIVING_SPEED_RL_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_DRIVING_SPEED_RR_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_STEERING_ANGLE_FL_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_STEERING_ANGLE_FR_INDEX] );
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_STEERING_ANGLE_RL_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", gncstate[LRM_STEERING_ANGLE_RR_INDEX]);
  tmmsg += buffer;


  //
  // RRP
  //
  tmmsg += "TmPacket ARM_STAT ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.0lf;\n", rrpstate[RRP_STATUS_INDEX]);
  tmmsg += buffer;


  tmmsg += "TmPacket ARM_POS ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Q1_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Q1_INDEX+1]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Q1_INDEX+2]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Q1_INDEX+3]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", rrpstate[RRP_CURRENT_Q1_INDEX+4]);
  tmmsg += buffer;

  //tm_fake_value++;
  //  if (tm_fake_value > 360) tm_fake_value = -360;

  tmmsg +="TmPacket ArmCartPosition " ;
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_X_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Y_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_Z_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_RX_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", rrpstate[RRP_CURRENT_RY_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", rrpstate[RRP_CURRENT_RZ_INDEX]);
  tmmsg += buffer;


  //
  // PTU
  //
  tmmsg += "TmPacket PTU_STAT ";
  sprintf(buffer, "%d:", ctrl_time);
  sprintf(buffer, "%.0lf;\n", ptustate[LRM_MAST_STATUS_INDEX]);
  tmmsg += buffer;

  tmmsg += "TmPacket PTU_POS ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", ptustate[LRM_MAST_CURRENT_Q1_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", ptustate[LRM_MAST_CURRENT_Q1_INDEX+1]);
  tmmsg += buffer;


  //
  // NAVIGATION
  //

  int navcam1_status = navcamstate[LRM_NAVCAM1_OPER_MODE_INDEX];
  int navcam2_status = navcamstate[LRM_NAVCAM2_OPER_MODE_INDEX];
  int navcam3_status = navcamstate[LRM_NAVCAM3_OPER_MODE_INDEX];
  int navcam_status = 0;
  if (navcam1_status == LRM_NAVCAM_OPER_MODE_OPERATING ||
      navcam2_status == LRM_NAVCAM_OPER_MODE_OPERATING ||
      navcam3_status == LRM_NAVCAM_OPER_MODE_OPERATING) {
    navcam_status = 1;
  }
  else {
    navcam_status = 0;
  }
  int hazcam1_status = hazcamstate[LRM_HAZCAM1_OPER_MODE_INDEX];
  int hazcam2_status = hazcamstate[LRM_HAZCAM2_OPER_MODE_INDEX];
  int hazcam3_status = hazcamstate[LRM_HAZCAM3_OPER_MODE_INDEX];
  int hazcam_status = 0;
  if (hazcam1_status == LRM_HAZCAM_OPER_MODE_OPERATING ||
      hazcam2_status == LRM_HAZCAM_OPER_MODE_OPERATING ||
      hazcam3_status == LRM_HAZCAM_OPER_MODE_OPERATING) {
    hazcam_status = 1;
  }
  else {
    hazcam_status = 0;
  }
  int pancam1_status = pancamstate[LRM_PANCAM1_OPER_MODE_INDEX];
  int pancam2_status = pancamstate[LRM_PANCAM2_OPER_MODE_INDEX];
  int pancam3_status = pancamstate[LRM_PANCAM3_OPER_MODE_INDEX];
  int pancam4_status = pancamstate[LRM_PANCAM4_OPER_MODE_INDEX];
  int pancam5_status = pancamstate[LRM_PANCAM5_OPER_MODE_INDEX];
  int pancam6_status = pancamstate[LRM_PANCAM6_OPER_MODE_INDEX];
  int pancam_status = 0;
  if (pancam1_status == LRM_PANCAM_OPER_MODE_OPERATING ||
      pancam2_status == LRM_PANCAM_OPER_MODE_OPERATING ||
      pancam3_status == LRM_PANCAM_OPER_MODE_OPERATING ||
      pancam4_status == LRM_PANCAM_OPER_MODE_OPERATING ||
      pancam5_status == LRM_PANCAM_OPER_MODE_OPERATING ||
      pancam6_status == LRM_PANCAM_OPER_MODE_OPERATING) {
    pancam_status = 1;
  }
  else {
    pancam_status = 0;
  }
  int tofcam_status = tofcamstate[LRM_TOFCAM_OPER_MODE_INDEX];
  if (tofcam_status == LRM_TOFCAM_OPER_MODE_OPERATING) {
    tofcam_status = 1;
  }
  else {
    tofcam_status = 0;
  }
  int minicam_status = minicamstate[LRM_MINICAM_OPER_MODE_INDEX];
  if (minicam_status == LRM_MINICAM_OPER_MODE_OPERATING) {
    minicam_status = 1;
  }
  else {
    minicam_status = 0;
  }

  tmmsg += "TmPacket NAV_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", navcam_status); tmmsg += buffer; tmmsg += ";\n";
  tmmsg += "TmPacket PAN_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", pancam_status); tmmsg += buffer; tmmsg += ";\n";
  tmmsg += "TmPacket HAZ_STAT ";sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", hazcam_status); tmmsg += buffer; tmmsg += ";\n";
  tmmsg += "TmPacket TOF_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", tofcam_status); tmmsg += buffer; tmmsg += ";\n";
  tmmsg += "TmPacket MINICAM_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", minicam_status); tmmsg += buffer; tmmsg += ";\n";

  tmmsg += "TmPacket IMU_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", 1); tmmsg += buffer; tmmsg += ";\n";

  tmmsg += "TmPacket IMU_MEAS " ;
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_ACCX_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_ACCY_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_ACCZ_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_VELRX_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_VELRY_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_VELRZ_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSERX_INDEX] );
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSERY_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", gncstate[LRM_ROVER_POSERZ_INDEX]);
  tmmsg += buffer;

  tmmsg += "TmPacket INC_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", 1); tmmsg += buffer; tmmsg += ";\n";

  tmmsg += "TmPacket INC_MEAS ";
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", gncstate[LRM_ROVER_POSERX_INDEX]);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", gncstate[LRM_ROVER_POSERY_INDEX]);
  tmmsg += buffer;

  tmmsg += "TmPacket SUN_STAT "; sprintf(buffer, "%d:", ctrl_time); tmmsg += buffer; sprintf(buffer, "%d", 1); tmmsg += buffer; tmmsg += ";\n";


  tmmsg += "TmPacket SUN_MEAS " ;
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%.3lf,", sin(ctrl_time));
  tmmsg += buffer;
  sprintf(buffer, "%.3lf;\n", cos(ctrl_time));
  tmmsg += buffer;


  tmmsg += "TmPacket TweakerParams " ;
  sprintf(buffer, "%d:", ctrl_time);
  tmmsg += buffer;
  sprintf(buffer, "%lf,%lf,%lf,%lf,%lf,%lf,%lf;\n", 
	  ttcstate[COMMS_TM_POWNLOAD_CAPACITY_LIMIT_INDEX],
	  ttcstate[COMMS_TC_UPLOAD_CAPACITY_LIMIT_INDEX],
	  ttcstate[COMMS_TM_PACKET_DELAY_INDEX],
	  ttcstate[COMMS_TC_PACKET_DELAY_INDEX],
	  ttcstate[COMMS_TM_PACKET_DROP_RATE_INDEX],
	  ttcstate[COMMS_TC_PACKET_DROP_RATE_INDEX],
	  ttcstate[COMMS_LOG_VERBOSITY_LEVEL_INDEX]);
  tmmsg += buffer;
*/
}
