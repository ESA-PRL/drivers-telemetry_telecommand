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
				   MessageProducer* messproducer, double * transform) {
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
    imageMessage->setFloatProperty("X",transform[0]);
    imageMessage->setFloatProperty("Y",transform[1]);
    imageMessage->setFloatProperty("Z",transform[2]);
    imageMessage->setFloatProperty("qX",transform[3]);
    imageMessage->setFloatProperty("qY",transform[4]);
    imageMessage->setFloatProperty("qZ",transform[5]);
    imageMessage->setFloatProperty("qW",transform[6]);
    messproducer->send(imageMessage.get()); 
}

int CommTmServer::sendFileMessage(const char* filename, int size, 
				   const unsigned char * data, 
				   MessageProducer* messproducer) {
  std::auto_ptr<BytesMessage> 
    fileMessage(activemqTMSender->
		 sessionMonitor->createBytesMessage((const unsigned char *)data, size));
    fileMessage->setStringProperty("filename",filename);
   messproducer->send(fileMessage.get()); 
}

int CommTmServer::sendDEMMessage(const char* filename, int seq, long time, int size, 
				   std::vector<unsigned char> data, 
				   MessageProducer* messproducer, double * transform) {
  std::auto_ptr<StreamMessage> 
    demMessage(activemqTMSender->
		 sessionMonitor->createStreamMessage());
    demMessage->writeBytes(data);
    demMessage->setStringProperty("filename",filename);
    demMessage->setStringProperty("Method","DEM");
    demMessage->setIntProperty("size",size);
    demMessage->setIntProperty("Seq",seq);
    demMessage->setLongProperty("time",time);
    demMessage->setFloatProperty("X",transform[0]);
    demMessage->setFloatProperty("Y",transform[1]);
    demMessage->setFloatProperty("Z",transform[2]);
    demMessage->setFloatProperty("qX",transform[3]);
    demMessage->setFloatProperty("qY",transform[4]);
    demMessage->setFloatProperty("qZ",transform[5]);
    demMessage->setFloatProperty("qW",transform[6]);
    messproducer->send(demMessage.get()); 
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
		GNCState[GNC_ROVER_DEPLOYMENT_Q1_INDEX],
		GNCState[GNC_ROVER_DEPLOYMENT_Q2_INDEX],
		GNCState[GNC_ROVER_DEPLOYMENT_Q3_INDEX],
		GNCState[GNC_ROVER_DEPLOYMENT_Q4_INDEX],
		GNCState[GNC_ROVER_DEPLOYMENT_Q5_INDEX],
		GNCState[GNC_ROVER_DEPLOYMENT_Q6_INDEX],
		GNCState[GNC_ACTION_RET_INDEX],
		GNCState[GNC_ACTION_ID_INDEX]
		);
	tmmsg += buffer;

        std::auto_ptr<TextMessage> gncMessage(activemqTMSender->sessionMonitor->createTextMessage
						    ("I'm a gnc message"));
	gncMessage->setIntProperty("iter",seq);
	gncMessage->setLongProperty("time",time1);
	gncMessage->setIntProperty("Status",(int)GNCState[GNC_OPER_MODE_INDEX]);
	gncMessage->setFloatProperty("X", GNCState[GNC_ROVER_POSEX_INDEX]);
	gncMessage->setFloatProperty("Y", GNCState[GNC_ROVER_POSEY_INDEX]);
	gncMessage->setFloatProperty("Z", GNCState[GNC_ROVER_POSEZ_INDEX]);
	gncMessage->setFloatProperty("RX", GNCState[GNC_ROVER_POSERX_INDEX]);
	gncMessage->setFloatProperty("RY", GNCState[GNC_ROVER_POSERY_INDEX]);
	gncMessage->setFloatProperty("RZ", GNCState[GNC_ROVER_POSERZ_INDEX]);
	gncMessage->setFloatProperty("DEPLOYMENTQ1", GNCState[GNC_ROVER_DEPLOYMENT_Q1_INDEX]);
	gncMessage->setFloatProperty("DEPLOYMENTQ2", GNCState[GNC_ROVER_DEPLOYMENT_Q2_INDEX]);
	gncMessage->setFloatProperty("DEPLOYMENTQ3", GNCState[GNC_ROVER_DEPLOYMENT_Q3_INDEX]);;
	gncMessage->setFloatProperty("DEPLOYMENTQ4", GNCState[GNC_ROVER_DEPLOYMENT_Q4_INDEX]);
	gncMessage->setFloatProperty("DEPLOYMENTQ5", GNCState[GNC_ROVER_DEPLOYMENT_Q5_INDEX]);
	gncMessage->setFloatProperty("DEPLOYMENTQ6", GNCState[GNC_ROVER_DEPLOYMENT_Q6_INDEX]);
	gncMessage->setIntProperty("ActionStatus", (int)GNCState[GNC_ACTION_RET_INDEX]);
	gncMessage->setIntProperty("ActionId", (int)GNCState[GNC_ACTION_ID_INDEX]);
	activemqTMSender->gncProducerMonitoring->send(gncMessage.get()); 
	
      }
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	lastGNCState[i]=GNCState[i];
      }
      
      //
      // PTU_STATE
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
	activemqTMSender->ptuProducerMonitoring->send(mastMessage.get()); 
	
      }
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	lastMastState[i]=MastState[i];
      }
      
/*      
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
*/
      //      std::cout << "Sent" << std::endl;
    } catch (CMSException& e) {
      e.printStackTrace();
      std::cout << "tmgeneration (ActiveMQTMSender) - exception detected" << std::endl;
      activemqTMSender->isConnected = false;
    }
  }
}


