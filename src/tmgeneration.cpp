#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

#include "comm.h"

#include <stdio.h>

// Copy of las state variables sent
//static double lastState[MAX_STATE_SIZE];
static double lastLOCOMState[MAX_STATE_SIZE];
static double lastMastState[MAX_STATE_SIZE];
static double lastGNCState[MAX_STATE_SIZE];
static double lastDhsState[MAX_STATE_SIZE];
static double lastTtcState[MAX_STATE_SIZE];
static double lastDHSState[MAX_STATE_SIZE];
static double lastTTCState[MAX_STATE_SIZE];
static double lastADEState[MAX_STATE_SIZE];
static double lastSAState[MAX_STATE_SIZE];

static bool first_time=true;

static long long offsetTime = 0; 

void addOffsetTime(double seconds) {
  offsetTime = offsetTime + ((long long) seconds)*1000;
}

int CommTmServer::sendImageMessage(const char* filename, int seq, long time, const char* date, int size, 
				   const unsigned char * data, 
				   MessageProducer* messproducer, double * transform) {
  std::auto_ptr<BytesMessage> 
    imageMessage(activemqTMSender->
		 sessionMonitor->createBytesMessage((const unsigned char *)data, size));
    imageMessage->setStringProperty("filename",filename);
    imageMessage->setStringProperty("Encoding","mono9");
    imageMessage->setIntProperty("Seq",seq);
    imageMessage->setIntProperty("Height",780);
    imageMessage->setIntProperty("Width",1024);
    imageMessage->setBooleanProperty("Bigendian", true);
    imageMessage->setIntProperty("Step",1);
    imageMessage->setStringProperty("Date",date);
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

int CommTmServer::sendDEMMessage(const char* filename, int seq, long time, const char* date, int size, 
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
    demMessage->setStringProperty("Date",date);
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
 double LOCOMState[MAX_STATE_SIZE];
 double MastState[MAX_STATE_SIZE];
 double GNCState[MAX_STATE_SIZE];
 double DHSState[MAX_STATE_SIZE];
 double TTCState[MAX_STATE_SIZE];
 double ADEState[MAX_STATE_SIZE];
 double SAState[MAX_STATE_SIZE];

 // flags for state changes
 bool LOCOMStateChanged;
 bool MastStateChanged;
 bool GNCStateChanged;
 bool ADEStateChanged;
 bool DHSStateChanged;
 bool TTCStateChanged;
 bool SAStateChanged;


  //
  // dummy initialisation of the TM
  //
  if (first_time){
    for (int i=0; i<MAX_STATE_SIZE; i++) {
      LOCOMState[i] = 0.0;
      MastState[i]  = 0.0;
      GNCState[i]   = 0.0;
      DHSState[i]   = 0.0;
      TTCState[i]   = 0.0;
      ADEState[i]   = 0.0;
      SAState[i]    = 0.0;
      lastLOCOMState[i] = -100.0;
      lastMastState[i]  = -100.0;
      lastGNCState[i]   = -100.0;
      lastDHSState[i]   = -100.0;
      lastTTCState[i]   = -100.0;
      lastADEState[i]   = -100.0;
      lastSAState[i]    = -100.0;
    }
    first_time=false;
  }


  if ( prr->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ){
         std::cout << "Error getting GNCState" << std::endl;
  }

  if ( prr->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ){
         std::cout << "Error getting MastState" << std::endl;
  }

  if ( prr->GetParameters()->get( "LOCOMState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) LOCOMState ) == ERROR ){
         std::cout << "Error getting LOCOMState" << std::endl;
  }

  if ( prr->GetParameters()->get( "AdeState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ){
         std::cout << "Error getting ADEState" << std::endl;
  }

  if ( prr->GetParameters()->get( "CommsState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) TTCState ) == ERROR ){
         std::cout << "Error getting TTCState" << std::endl;
  }

  if ( prr->GetParameters()->get( "DhsState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ){
         std::cout << "Error getting DHSState" << std::endl;
  }

  if ( prr->GetParameters()->get( "SolarArrayState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ){
         std::cout << "Error getting SAState" << std::endl;
  }

  if (activemqTMSender->isConnected)
  {
      try
      {
          int seq = 1;
          struct timeval tp;
          gettimeofday(&tp, NULL);
          long long time1 = (long long) (tp.tv_sec * 1000L + (tp.tv_usec / 1000) + offsetTime); 

          //
          // GNC_STATE
          //
          GNCStateChanged=false;
          for (int i=0; i<MAX_STATE_SIZE; i++)
          {
              switch (i)
              {
                  case GNC_ROVER_POSEX_INDEX:
                  case GNC_ROVER_POSEY_INDEX:
                  case GNC_ROVER_POSEZ_INDEX:
                      if (std::abs(GNCState[i] - lastGNCState[i]) > 0.01)
                          GNCStateChanged = true;
                      break;
                  case GNC_ROVER_POSERX_INDEX:
                  case GNC_ROVER_POSERY_INDEX:
                  case GNC_ROVER_POSERZ_INDEX:
                      if (std::abs(GNCState[i] - lastGNCState[i]) > 0.1)
                          GNCStateChanged = true;
                      break;
                  default:
                      if (GNCState[i]!=lastGNCState[i])
                          GNCStateChanged = true;
                      break;
              }
          }
          if (GNCStateChanged)
          {
              tmmsg = "TmPacket GNC_STATE ";

              std::auto_ptr<TextMessage> gncMessage(activemqTMSender->sessionMonitor->createTextMessage
                      ("I'm a gnc message"));
              gncMessage->setIntProperty("iter",seq);
              gncMessage->setLongProperty("time",time1);
              gncMessage->setFloatProperty("X", GNCState[GNC_ROVER_POSEX_INDEX]);
              gncMessage->setFloatProperty("Y", GNCState[GNC_ROVER_POSEY_INDEX]);
              gncMessage->setFloatProperty("Z", GNCState[GNC_ROVER_POSEZ_INDEX]);
              gncMessage->setFloatProperty("RX", GNCState[GNC_ROVER_POSERX_INDEX]);
              gncMessage->setFloatProperty("RY", GNCState[GNC_ROVER_POSERY_INDEX]);
              gncMessage->setFloatProperty("RZ", GNCState[GNC_ROVER_POSERZ_INDEX]);
              gncMessage->setIntProperty("Trajectory_STATUS", GNCState[GNC_TRAJECTORY_STATUS_INDEX]);
              activemqTMSender->gncProducerMonitoring->send(gncMessage.get()); 
              for (int i=0; i<MAX_STATE_SIZE; i++)
              {
                  lastGNCState[i]=GNCState[i];
              }
          }
          //
          // MAST_STATE
          //
          MastStateChanged=false;
          for (int i=0; i<MAX_STATE_SIZE; i++)
          {
              if (MastState[i]!=lastMastState[i])
                  MastStateChanged=true;
          }
          if (MastStateChanged)
          {
              tmmsg += "TmPacket MAST_STATE ";

              std::auto_ptr<TextMessage> mastMessage(activemqTMSender->sessionMonitor->createTextMessage
                      ("I'm a mast message"));
	      mastMessage->setIntProperty("iter",seq);
	      mastMessage->setLongProperty("time",time1);
	      mastMessage->setIntProperty("StatusDep", (int)MastState[MAST_DEP_STATUS_INDEX]);
	      mastMessage->setIntProperty("StatusPan", (int)MastState[MAST_PAN_STATUS_INDEX]);
	      mastMessage->setIntProperty("StatusTilt", (int)MastState[MAST_TILT_STATUS_INDEX]);
	      mastMessage->setFloatProperty("Dep", MastState[MAST_CURRENT_Q1_INDEX]);
	      mastMessage->setFloatProperty("Pan", MastState[MAST_CURRENT_Q2_INDEX]);
	      mastMessage->setFloatProperty("Tilt", MastState[MAST_CURRENT_Q3_INDEX]);
	      mastMessage->setIntProperty("ActionStatus", (int)MastState[MAST_ACTION_RET_INDEX]);
	      mastMessage->setIntProperty("ActionId", (int)MastState[MAST_ACTION_ID_INDEX]);
              activemqTMSender->mastProducerMonitoring->send(mastMessage.get()); 
              for (int i=0; i<MAX_STATE_SIZE; i++)
              {
                  lastMastState[i]=MastState[i];
              }
          }
          
	  //
	  // DHS_STATE
	  //
	  DHSStateChanged = false;
          for (int i=0; i<MAX_STATE_SIZE; i++)
	    {
              if (DHSState[i] != lastDHSState[i])
		DHSStateChanged = true;
	    }
          if (DHSStateChanged) {
	    std::auto_ptr<TextMessage> dhsMessage(activemqTMSender->sessionMonitor->createTextMessage
						  ("I'm a dhs message"));
	    dhsMessage->setIntProperty("iter",seq);
	    dhsMessage->setLongProperty("time",time1);
	    dhsMessage->setIntProperty("Status", (int)DHSState[DHS_STATUS_INDEX]);
	    dhsMessage->setIntProperty("ActionStatus", (int)DHSState[DHS_ACTION_RET_INDEX]);
	    dhsMessage->setIntProperty("ActionId", (int)DHSState[DHS_ACTION_ID_INDEX]);
	    activemqTMSender->dhsProducerMonitoring->send(dhsMessage.get()); 
	    for (int i=0; i<MAX_STATE_SIZE; i++) {
	      lastDhsState[i] = DHSState[i];
	    }
	  }

      //
      // TTC_STATE
      //
      TTCStateChanged = false;
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	if (TTCState[i]!=lastTTCState[i])
	  TTCStateChanged=true;
      }
      if (TTCStateChanged) {
	std::auto_ptr<TextMessage> ttcMessage(activemqTMSender->sessionMonitor->createTextMessage
					       ("I'm a ttc message"));
	ttcMessage->setIntProperty("iter",seq);
	ttcMessage->setLongProperty("time",time1);
	ttcMessage->setIntProperty("StatusMain",   (int)TTCState[COMMS_MAIN_STATUS_INDEX]);
	ttcMessage->setIntProperty("StatusRed",    (int)TTCState[COMMS_REDUNDANT_STATUS_INDEX]);
	ttcMessage->setIntProperty("ActionStatus", (int)TTCState[COMMS_ACTION_RET_INDEX]);
	ttcMessage->setIntProperty("ActionId",     (int)TTCState[COMMS_ACTION_ID_INDEX]);
	activemqTMSender->ttcProducerMonitoring->send(ttcMessage.get()); 
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  lastTtcState[i]=TTCState[i];
	}
      }


      //
      // SA_STATE
      //
      SAStateChanged = false;
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	if (SAState[i] != lastSAState[i])
	  SAStateChanged=true;
      }
      if (SAStateChanged) {
	std::auto_ptr<TextMessage> saMessage(activemqTMSender->sessionMonitor->createTextMessage
					     ("I'm a sa message"));
	saMessage->setIntProperty("iter",seq);
	saMessage->setLongProperty("time",time1);
	saMessage->setFloatProperty("SALEFTPrimStatus", SAState[SA_LEFT_PRIMARY_STATUS_INDEX]);
	saMessage->setFloatProperty("SALEFTSecStatus", SAState[SA_LEFT_SECONDARY_STATUS_INDEX]);
	saMessage->setFloatProperty("SARIGHTPrimStatus", SAState[SA_RIGHT_PRIMARY_STATUS_INDEX]);
	saMessage->setFloatProperty("SARIGHTSecStatus", SAState[SA_RIGHT_SECONDARY_STATUS_INDEX]);
	saMessage->setFloatProperty("Q1", SAState[SA_CURRENT_Q1_INDEX]);
	saMessage->setFloatProperty("Q2", SAState[SA_CURRENT_Q2_INDEX]);
	saMessage->setFloatProperty("Q3", SAState[SA_CURRENT_Q3_INDEX]);
	saMessage->setFloatProperty("Q4", SAState[SA_CURRENT_Q4_INDEX]);
	saMessage->setIntProperty("ActionStatus", (int)SAState[SA_ACTION_RET_INDEX]);
	saMessage->setIntProperty("ActionId", (int)SAState[SA_ACTION_ID_INDEX]);
	activemqTMSender->saProducerMonitoring->send(saMessage.get()); 
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  lastSAState[i]=SAState[i];
	}
      }

      //
      // ADE_STATE
      //
      ADEStateChanged = false;
      for (int i=0; i<MAX_STATE_SIZE; i++) {
	if (ADEState[i] != lastADEState[i])
	  ADEStateChanged=true;
      }
      if (ADEStateChanged) {
	std::auto_ptr<TextMessage> adeMessage(activemqTMSender->sessionMonitor->createTextMessage
				     ("I'm a sa message"));
	adeMessage->setIntProperty("iter",seq);
	adeMessage->setLongProperty("time",time1);
	adeMessage->setIntProperty("StatusLeft", ADEState[ADE_STATUS_LEFT_INDEX]);
	adeMessage->setIntProperty("StatusRight", ADEState[ADE_STATUS_RIGHT_INDEX]);
	adeMessage->setIntProperty("HDRM_DMA_1", (int) ADEState[HDRM_DMA_1_INDEX]);    
	adeMessage->setIntProperty("HDRM_DMA_2", (int) ADEState[HDRM_DMA_2_INDEX]);    
	adeMessage->setIntProperty("HDRM_DRILL_L", (int) ADEState[HDRM_DRILL_L_INDEX]);  
	adeMessage->setIntProperty("HDRM_DRILL_R", (int) ADEState[HDRM_DRILL_R_INDEX]);  
	adeMessage->setIntProperty("HDRM_SA_LFI",  (int) ADEState[HDRM_SA_LFI_INDEX]);   
	adeMessage->setIntProperty("HDRM_SA_LFO",  (int) ADEState[HDRM_SA_LFO_INDEX]);   
	adeMessage->setIntProperty("HDRM_SA_LRI",  (int) ADEState[HDRM_SA_LRI_INDEX]);   
	adeMessage->setIntProperty("HDRM_SA_RFI",  (int) ADEState[HDRM_SA_RFI_INDEX]);   
	adeMessage->setIntProperty("HDRM_SA_RFO",  (int) ADEState[HDRM_SA_RFO_INDEX]);   
	adeMessage->setIntProperty("HDRM_SA_RRI",  (int) ADEState[HDRM_SA_RRI_INDEX]);   
	adeMessage->setIntProperty("HDRM_UMB_L",   (int) ADEState[HDRM_UMB_L_INDEX]);    
	adeMessage->setIntProperty("HDRM_UMB_R",    (int) ADEState[HDRM_UMB_R_INDEX]);    
	adeMessage->setIntProperty("HDRM_WHEEL_LF", (int) ADEState[HDRM_WHEEL_LF_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_LM", (int) ADEState[HDRM_WHEEL_LM_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_LR", (int) ADEState[HDRM_WHEEL_LR_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_RF", (int) ADEState[HDRM_WHEEL_RF_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_RM", (int) ADEState[HDRM_WHEEL_RM_INDEX]); 
	adeMessage->setIntProperty("HDRM_WHEEL_RR", (int) ADEState[HDRM_WHEEL_RR_INDEX]); 
	adeMessage->setIntProperty("HDRM_BODY_LF", (int) ADEState[HDRM_BODY_LF_INDEX]);  
	adeMessage->setIntProperty("HDRM_BODY_RF", (int) ADEState[HDRM_BODY_RF_INDEX]);  
	adeMessage->setIntProperty("HDRM_BODY_R", (int) ADEState[HDRM_BODY_R_INDEX]);   
	adeMessage->setIntProperty("ActionStatus", (int)ADEState[ADE_ACTION_RET_INDEX]);
	adeMessage->setIntProperty("ActionId", (int)ADEState[ADE_ACTION_ID_INDEX]);
	activemqTMSender->adeProducerMonitoring->send(adeMessage.get()); 
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  lastADEState[i] = ADEState[i];
	}
      }


      //
          // LOCOM State
          //      

          LOCOMStateChanged=false;
          for (int i=0; i<MAX_STATE_SIZE; i++)
          {
              switch (i)
              {
                  case GNC_ROVER_WHEEL1_TEMPERATURE_INDEX:
                  case GNC_ROVER_WHEEL2_TEMPERATURE_INDEX:
                  case GNC_ROVER_WHEEL3_TEMPERATURE_INDEX:
                  case GNC_ROVER_WHEEL4_TEMPERATURE_INDEX:
                  case GNC_ROVER_WHEEL5_TEMPERATURE_INDEX:
                  case GNC_ROVER_WHEEL6_TEMPERATURE_INDEX:
                     if (std::abs(LOCOMState[i] - lastLOCOMState[i]) > 0.5)
                          LOCOMStateChanged = true;
                      break;
                  case GNC_ROVER_LEFT_ROCKER_INDEX:
                  case GNC_ROVER_RIGHT_ROCKER_INDEX:
                  case GNC_ROVER_LEFT_BOGIE_INDEX:
                  case GNC_ROVER_RIGHT_BOGIE_INDEX:
                  case GNC_ROVER_REAR_BOGIE_INDEX:
                      if (std::abs(LOCOMState[i] - lastLOCOMState[i]) > 1.0)
                          LOCOMStateChanged = true;
                      break;
                  default:
                      if (LOCOMState[i]!=lastLOCOMState[i])
                          LOCOMStateChanged = true;
                      break;
              }
          }
          if (LOCOMStateChanged){
	    tmmsg += "TmPacket LOCOM_STATE ";
	    
	    std::auto_ptr<TextMessage> locomMessage(activemqTMSender->sessionMonitor->createTextMessage
						    ("I'm a locom message"));
	    if (rover == HDPR)
	    {
              locomMessage->setIntProperty("iter",seq);
              locomMessage->setLongProperty("time",time1);
              locomMessage->setFloatProperty("SpeedFL", LOCOMState[GNC_ROVER_WHEEL1_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedFR", LOCOMState[GNC_ROVER_WHEEL2_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCL", LOCOMState[GNC_ROVER_WHEEL3_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCR", LOCOMState[GNC_ROVER_WHEEL4_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRL", LOCOMState[GNC_ROVER_WHEEL5_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRR", LOCOMState[GNC_ROVER_WHEEL6_SPEED_INDEX]);
              locomMessage->setFloatProperty("AngleFL", LOCOMState[GNC_ROVER_STEER1_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleFR", LOCOMState[GNC_ROVER_STEER2_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRL", LOCOMState[GNC_ROVER_STEER5_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRR", LOCOMState[GNC_ROVER_STEER6_POSITION_INDEX]);
              locomMessage->setFloatProperty("CurrentFL", LOCOMState[GNC_ROVER_WHEEL1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentFR", LOCOMState[GNC_ROVER_WHEEL2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCL", LOCOMState[GNC_ROVER_WHEEL3_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCR", LOCOMState[GNC_ROVER_WHEEL4_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRL", LOCOMState[GNC_ROVER_WHEEL5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRR", LOCOMState[GNC_ROVER_WHEEL6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFL", LOCOMState[GNC_ROVER_STEER1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFR", LOCOMState[GNC_ROVER_STEER2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRL", LOCOMState[GNC_ROVER_STEER5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRR", LOCOMState[GNC_ROVER_STEER6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("LeftRocker", LOCOMState[GNC_ROVER_LEFT_ROCKER_INDEX]);
              locomMessage->setFloatProperty("RightRocker", LOCOMState[GNC_ROVER_RIGHT_ROCKER_INDEX]);
              locomMessage->setFloatProperty("LeftBogie", LOCOMState[GNC_ROVER_LEFT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("RightBogie", LOCOMState[GNC_ROVER_RIGHT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("TemperatureFL", LOCOMState[GNC_ROVER_WHEEL1_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureFR", LOCOMState[GNC_ROVER_WHEEL2_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureCL", LOCOMState[GNC_ROVER_WHEEL3_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureCR", LOCOMState[GNC_ROVER_WHEEL4_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureRL", LOCOMState[GNC_ROVER_WHEEL5_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureRR", LOCOMState[GNC_ROVER_WHEEL6_TEMPERATURE_INDEX]);
              activemqTMSender->locomProducerMonitoring->send(locomMessage.get()); 
	    }
	    else if (rover == ExoTeR) {
	      locomMessage->setIntProperty("iter",seq);
              locomMessage->setLongProperty("time",time1);
              locomMessage->setFloatProperty("SpeedFL", LOCOMState[GNC_ROVER_WHEEL1_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedFR", LOCOMState[GNC_ROVER_WHEEL2_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCL", LOCOMState[GNC_ROVER_WHEEL3_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCR", LOCOMState[GNC_ROVER_WHEEL4_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRL", LOCOMState[GNC_ROVER_WHEEL5_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRR", LOCOMState[GNC_ROVER_WHEEL6_SPEED_INDEX]);
              locomMessage->setFloatProperty("AngleFL", LOCOMState[GNC_ROVER_STEER1_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleFR", LOCOMState[GNC_ROVER_STEER2_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRL", LOCOMState[GNC_ROVER_STEER5_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRR", LOCOMState[GNC_ROVER_STEER6_POSITION_INDEX]);
              locomMessage->setFloatProperty("DeploymentFL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q1_INDEX]);
              locomMessage->setFloatProperty("DeploymentFR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q2_INDEX]);
              locomMessage->setFloatProperty("DeploymentCL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q3_INDEX]);
              locomMessage->setFloatProperty("DeploymentCR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q4_INDEX]);
              locomMessage->setFloatProperty("DeploymentRL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q5_INDEX]);
              locomMessage->setFloatProperty("DeploymetnRR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q6_INDEX]);
              locomMessage->setFloatProperty("CurrentFL", LOCOMState[GNC_ROVER_WHEEL1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentFR", LOCOMState[GNC_ROVER_WHEEL2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCL", LOCOMState[GNC_ROVER_WHEEL3_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCR", LOCOMState[GNC_ROVER_WHEEL4_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRL", LOCOMState[GNC_ROVER_WHEEL5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRR", LOCOMState[GNC_ROVER_WHEEL6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFL", LOCOMState[GNC_ROVER_STEER1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFR", LOCOMState[GNC_ROVER_STEER2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRL", LOCOMState[GNC_ROVER_STEER5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRR", LOCOMState[GNC_ROVER_STEER6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDFL", LOCOMState[GNC_ROVER_DEPLOYMENT1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDFR", LOCOMState[GNC_ROVER_DEPLOYMENT2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDCL", LOCOMState[GNC_ROVER_DEPLOYMENT3_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDCR", LOCOMState[GNC_ROVER_DEPLOYMENT4_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDRL", LOCOMState[GNC_ROVER_DEPLOYMENT5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDRR", LOCOMState[GNC_ROVER_DEPLOYMENT6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("LeftBogie", LOCOMState[GNC_ROVER_LEFT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("RightBogie", LOCOMState[GNC_ROVER_RIGHT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("RearBogie", LOCOMState[GNC_ROVER_REAR_BOGIE_INDEX]);
              locomMessage->setFloatProperty("TemperatureFL", LOCOMState[GNC_ROVER_WHEEL1_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureFR", LOCOMState[GNC_ROVER_WHEEL2_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureCL", LOCOMState[GNC_ROVER_WHEEL3_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureCR", LOCOMState[GNC_ROVER_WHEEL4_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureRL", LOCOMState[GNC_ROVER_WHEEL5_TEMPERATURE_INDEX]);
              locomMessage->setFloatProperty("TemperatureRR", LOCOMState[GNC_ROVER_WHEEL6_TEMPERATURE_INDEX]);
              activemqTMSender->locomProducerMonitoring->send(locomMessage.get()); 
	    }
	    else if (rover == MaRTA) {
              locomMessage->setIntProperty("iter",seq);
              locomMessage->setLongProperty("time",time1);
              locomMessage->setFloatProperty("SpeedFL", LOCOMState[GNC_ROVER_WHEEL1_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedFR", LOCOMState[GNC_ROVER_WHEEL2_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCL", LOCOMState[GNC_ROVER_WHEEL3_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedCR", LOCOMState[GNC_ROVER_WHEEL4_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRL", LOCOMState[GNC_ROVER_WHEEL5_SPEED_INDEX]);
              locomMessage->setFloatProperty("SpeedRR", LOCOMState[GNC_ROVER_WHEEL6_SPEED_INDEX]);
              locomMessage->setFloatProperty("AngleFL", LOCOMState[GNC_ROVER_STEER1_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleFR", LOCOMState[GNC_ROVER_STEER2_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRL", LOCOMState[GNC_ROVER_STEER5_POSITION_INDEX]);
              locomMessage->setFloatProperty("AngleRR", LOCOMState[GNC_ROVER_STEER6_POSITION_INDEX]);
              locomMessage->setFloatProperty("DeploymentFL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q1_INDEX]);
              locomMessage->setFloatProperty("DeploymentFR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q2_INDEX]);
              locomMessage->setFloatProperty("DeploymentCL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q3_INDEX]);
              locomMessage->setFloatProperty("DeploymentCR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q4_INDEX]);
              locomMessage->setFloatProperty("DeploymentRL", LOCOMState[GNC_ROVER_DEPLOYMENT_Q5_INDEX]);
              locomMessage->setFloatProperty("DeploymetnRR", LOCOMState[GNC_ROVER_DEPLOYMENT_Q6_INDEX]);
              locomMessage->setFloatProperty("CurrentFL", LOCOMState[GNC_ROVER_WHEEL1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentFR", LOCOMState[GNC_ROVER_WHEEL2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCL", LOCOMState[GNC_ROVER_WHEEL3_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentCR", LOCOMState[GNC_ROVER_WHEEL4_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRL", LOCOMState[GNC_ROVER_WHEEL5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentRR", LOCOMState[GNC_ROVER_WHEEL6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFL", LOCOMState[GNC_ROVER_STEER1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSFR", LOCOMState[GNC_ROVER_STEER2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRL", LOCOMState[GNC_ROVER_STEER5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentSRR", LOCOMState[GNC_ROVER_STEER6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDFL", LOCOMState[GNC_ROVER_DEPLOYMENT1_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDFR", LOCOMState[GNC_ROVER_DEPLOYMENT2_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDCL", LOCOMState[GNC_ROVER_DEPLOYMENT3_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDCR", LOCOMState[GNC_ROVER_DEPLOYMENT4_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDRL", LOCOMState[GNC_ROVER_DEPLOYMENT5_CURRENT_INDEX]);
              locomMessage->setFloatProperty("CurrentDRR", LOCOMState[GNC_ROVER_DEPLOYMENT6_CURRENT_INDEX]);
              locomMessage->setFloatProperty("LeftBogie", LOCOMState[GNC_ROVER_LEFT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("RightBogie", LOCOMState[GNC_ROVER_RIGHT_BOGIE_INDEX]);
              locomMessage->setFloatProperty("RearBogie", LOCOMState[GNC_ROVER_REAR_BOGIE_INDEX]);
              activemqTMSender->locomProducerMonitoring->send(locomMessage.get()); 
	      
	    }
	    for (int i=0; i<MAX_STATE_SIZE; i++) {
	      lastLOCOMState[i]=LOCOMState[i];
	    }
	    //      std::cout << "Sent" << std::endl;
          }
      } catch (CMSException& e) {
          e.printStackTrace();
          std::cout << "tmgeneration (ActiveMQTMSender) - exception detected" << std::endl;
          activemqTMSender->isConnected = false;
      }
  }
}


