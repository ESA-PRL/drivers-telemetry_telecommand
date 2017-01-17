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

int CommTmServer::sendImageMessage(int seq, long time, int size, 
				   const unsigned char * data, 
				   MessageProducer* messproducer) {
  std::auto_ptr<BytesMessage> 
    imageMessage(activemqTMSender->
		 sessionMonitor->createBytesMessage((const unsigned char *)data, size));
    imageMessage->setStringProperty("Encoding","mono9");
    imageMessage->setIntProperty("Seq",seq);
    imageMessage->setIntProperty("Height",780);
    imageMessage->setIntProperty("Width",1024);
    imageMessage->setBooleanProperty("Bigendian", true);
    imageMessage->setIntProperty("Step",1);
    imageMessage->setLongProperty("time",time);
    imageMessage->setFloatProperty("X",0.0);
    imageMessage->setFloatProperty("Y",0.0);
    imageMessage->setFloatProperty("Z",1.0);
    imageMessage->setFloatProperty("qX",0.354);
    imageMessage->setFloatProperty("qY",0.354);
    imageMessage->setFloatProperty("qZ",0.146);
    imageMessage->setFloatProperty("qW",0.854);
    messproducer->send(imageMessage.get()); 
}

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
  
 
  if (activemqTMSender->isConnected) {
    
    try {
      int seq = 1;
      struct timeval tp;
      gettimeofday(&tp, NULL);
      long long time1 = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;   

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
	
	std::auto_ptr<TextMessage> gncexoterMessage(activemqTMSender->sessionMonitor->createTextMessage
						    ("I'm a gncexoter message"));
	gncexoterMessage->setIntProperty("iter",seq);
	gncexoterMessage->setLongProperty("time",time1);
	gncexoterMessage->setIntProperty("Status",(int)GNCState[GNC_OPER_MODE_INDEX]);
	gncexoterMessage->setFloatProperty("X", GNCState[GNC_ROVER_POSEX_INDEX]);
	gncexoterMessage->setFloatProperty("Y", GNCState[GNC_ROVER_POSEY_INDEX]);
	gncexoterMessage->setFloatProperty("Z", GNCState[GNC_ROVER_POSEZ_INDEX]);
	gncexoterMessage->setFloatProperty("RX", GNCState[GNC_ROVER_POSERX_INDEX]);
	gncexoterMessage->setFloatProperty("RY", GNCState[GNC_ROVER_POSERY_INDEX]);
	gncexoterMessage->setFloatProperty("RZ", GNCState[GNC_ROVER_POSERZ_INDEX]);
	gncexoterMessage->setFloatProperty("BemaQ1", GNCState[GNC_ROVER_BEMA_Q1_INDEX]);
	gncexoterMessage->setFloatProperty("BemaQ2", GNCState[GNC_ROVER_BEMA_Q2_INDEX]);
	gncexoterMessage->setFloatProperty("BemaQ3", GNCState[GNC_ROVER_BEMA_Q3_INDEX]);;
	gncexoterMessage->setFloatProperty("BemaQ4", GNCState[GNC_ROVER_BEMA_Q4_INDEX]);
	gncexoterMessage->setFloatProperty("BemaQ5", GNCState[GNC_ROVER_BEMA_Q5_INDEX]);
	gncexoterMessage->setFloatProperty("BemaQ6", GNCState[GNC_ROVER_BEMA_Q6_INDEX]);
	gncexoterMessage->setIntProperty("ActionStatus", (int)GNCState[GNC_ACTION_RET_INDEX]);
	gncexoterMessage->setIntProperty("ActionId", (int)GNCState[GNC_ACTION_ID_INDEX]);
	activemqTMSender->gncexoterProducerMonitoring->send(gncexoterMessage.get()); 
	
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
	
	std::auto_ptr<TextMessage> mastMessage(activemqTMSender->sessionMonitor->createTextMessage
					       ("I'm a Gnc message"));
	mastMessage->setIntProperty("iter",seq);
	mastMessage->setLongProperty("time",time1);
	mastMessage->setIntProperty("Status", (int)MastState[MAST_STATUS_INDEX]);
	mastMessage->setFloatProperty("DeployJoint", MastState[MAST_CURRENT_Q1_INDEX]);
	mastMessage->setFloatProperty("Pan", MastState[MAST_CURRENT_Q2_INDEX]);
	mastMessage->setFloatProperty("Tilt", MastState[MAST_CURRENT_Q3_INDEX]);
	mastMessage->setIntProperty("ActionStatus", (int)MastState[MAST_ACTION_RET_INDEX]);
	mastMessage->setIntProperty("ActionId", (int)MastState[MAST_ACTION_ID_INDEX]);
	activemqTMSender->mastProducerMonitoring->send(mastMessage.get()); 
	
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
	
	std::auto_ptr<TextMessage> saMessage(activemqTMSender->sessionMonitor->createTextMessage
					     ("I'm a sa message"));
	saMessage->setIntProperty("iter",seq);
	saMessage->setLongProperty("time",time1);
	saMessage->setIntProperty("Status", (int)SAState[SA_STATUS_INDEX]);
	saMessage->setIntProperty("Status1", (int)SAState[SA_LEFT_PRIMARY_STATUS_INDEX]);
	saMessage->setIntProperty("Status2", (int)SAState[SA_LEFT_SECONDARY_STATUS_INDEX]);
	saMessage->setIntProperty("Status3", (int)SAState[SA_RIGHT_PRIMARY_STATUS_INDEX]);
	saMessage->setIntProperty("Status4", (int)SAState[SA_RIGHT_SECONDARY_STATUS_INDEX]);
	saMessage->setFloatProperty("Q1", SAState[SA_CURRENT_Q1_INDEX]);
	saMessage->setFloatProperty("Q2", SAState[SA_CURRENT_Q2_INDEX]);
	saMessage->setFloatProperty("Q3", SAState[SA_CURRENT_Q3_INDEX]);
	saMessage->setFloatProperty("Q4", SAState[SA_CURRENT_Q4_INDEX]);
	saMessage->setIntProperty("ActionStatus", SAState[SA_ACTION_RET_INDEX]);
	saMessage->setIntProperty("ActionId", SAState[SA_ACTION_ID_INDEX]);
	activemqTMSender->saProducerMonitoring->send(saMessage.get()); 
	
	
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


	std::auto_ptr<TextMessage> adeMessage(activemqTMSender->sessionMonitor->createTextMessage
					     ("I'm a ade message"));
	adeMessage->setIntProperty("iter",seq);
	adeMessage->setLongProperty("time",time1);
	adeMessage->setIntProperty("StatusLeft", (int)ADEState[ADE_STATUS_LEFT_INDEX]); 
	adeMessage->setIntProperty("StatusRight", (int)ADEState[ADE_STATUS_RIGHT_INDEX]); 
	adeMessage->setIntProperty("HDRMB1", (int)ADEState[HDRM_BODY_1_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRMB2", (int)ADEState[HDRM_BODY_2_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRMB3", (int)ADEState[HDRM_BODY_3_STATUS_INDEX]); 
	adeMessage->setIntProperty("DRILL1", (int)ADEState[HDRM_DRILL_1_STATUS_INDEX]);
	adeMessage->setIntProperty("DRILL2", (int)ADEState[HDRM_DRILL_2_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRMMast", (int)ADEState[HDRM_MAST_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_SA_L1", (int)ADEState[HDRM_SA_LEFT_1_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_SA_L2", (int)ADEState[HDRM_SA_LEFT_2_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRM_SA_L3", (int)ADEState[HDRM_SA_LEFT_3_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRM_SA_R1", (int)ADEState[HDRM_SA_RIGHT_1_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_SA_R2", (int)ADEState[HDRM_SA_RIGHT_2_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_SA_R3", (int)ADEState[HDRM_SA_RIGHT_3_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_UMB_1", (int)ADEState[HDRM_UMBILICAL_1_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_UMB_2", (int)ADEState[HDRM_UMBILICAL_2_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_FL", (int)ADEState[HDRM_WHEEL_FL_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_WHEEL_FR", (int)ADEState[HDRM_WHEEL_FR_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_ML", (int)ADEState[HDRM_WHEEL_ML_STATUS_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_MR", (int)ADEState[HDRM_WHEEL_MR_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_WHEEL_RL", (int)ADEState[HDRM_WHEEL_RL_STATUS_INDEX]);
	adeMessage->setIntProperty("HDRM_WHEEL_RR", (int)ADEState[HDRM_WHEEL_RR_STATUS_INDEX]);
	adeMessage->setIntProperty("ActionStatus", (int)ADEState[ADE_ACTION_RET_INDEX]);
	adeMessage->setIntProperty("ActionId", (int)ADEState[ADE_ACTION_ID_INDEX]);
	activemqTMSender->adeProducerMonitoring->send(adeMessage.get()); 
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
	
	std::auto_ptr<TextMessage> pancamMessage(activemqTMSender->sessionMonitor->createTextMessage
						 ("I'm a pancam message"));
	pancamMessage->setIntProperty("iter",seq);
	pancamMessage->setLongProperty("time",time1);
	pancamMessage->setIntProperty("Status", (int)PanCamState[PANCAM_OPER_MODE_INDEX]);
	pancamMessage->setIntProperty("WAC_L", (int)PanCamState[PANCAM_WAC_L_INDEX]);
	pancamMessage->setIntProperty("WAC_R", (int)PanCamState[PANCAM_WAC_R_INDEX]);
	pancamMessage->setIntProperty("WAC_Stereo", (int)PanCamState[PANCAM_PAN_STEREO_INDEX]);
	pancamMessage->setIntProperty("FLOC_L", (int)PanCamState[LOCCAM_FLOC_L_INDEX]);
	pancamMessage->setIntProperty("FLOC_R", (int)PanCamState[LOCCAM_FLOC_R_INDEX]);
	pancamMessage->setIntProperty("FLOC_Stereo", (int)PanCamState[LOCCAM_FLOC_STEREO_INDEX]);
	pancamMessage->setIntProperty("RLOC_L", (int)PanCamState[LOCCAM_RLOC_L_INDEX]);
	pancamMessage->setIntProperty("RLOC_R", (int)PanCamState[LOCCAM_RLOC_R_INDEX]);
	pancamMessage->setIntProperty("RLOC_Stereo", (int)PanCamState[LOCCAM_RLOC_STEREO_INDEX]);
	pancamMessage->setIntProperty("ActionStatus", (int)PanCamState[PANCAM_ACTION_RET_INDEX]);
	pancamMessage->setIntProperty("ActionId", (int)PanCamState[PANCAM_ACTION_ID_INDEX]);
	activemqTMSender->pancamProducerMonitoring->send(pancamMessage.get()); 
	
      }
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	lastPanCamState[i]=PanCamState[i];
      }

      //      std::cout << "Sent" << std::endl;
    } catch (CMSException& e) {
      e.printStackTrace();
      std::cout << "tmgeneration (ActiveMQTMSender) - exception detected" << std::endl;
      activemqTMSender->isConnected = false;
    }
  }
}


