#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

#include "ctrl_state.h"
#include "comm.h"

#include <stdio.h>

// Copy of las state variables sent
//static double lastState[MAX_STATE_SIZE];
static double lastLOCOMState[MAX_STATE_SIZE];
static double lastMastState[MAX_STATE_SIZE];
static double lastGNCState[MAX_STATE_SIZE];

static bool first_time=true;

RoverName rover = HDPR;

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
 // flags for state changes
 bool LOCOMStateChanged;
 bool MastStateChanged;
 bool GNCStateChanged;


  //
  // dummy initialisation of the TM
  //
  if (first_time){
  for (int i=0; i<MAX_STATE_SIZE; i++) {
    LOCOMState[i] = 0.0;
    MastState[i] = 0.0;
    GNCState[i] = 0.0;
    lastLOCOMState[i] = -100.0;
    lastMastState[i] = -100.0;
    lastGNCState[i] = -100.0;
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

  if (activemqTMSender->isConnected)
  {
      try
      {
          int seq = 1;
          struct timeval tp;
          gettimeofday(&tp, NULL);
          long long time1 = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;   

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
          // PTU_STATE
          //
          MastStateChanged=false;
          for (int i=0; i<MAX_STATE_SIZE; i++)
          {
              if (MastState[i]!=lastMastState[i])
                  MastStateChanged=true;
          }
          if (MastStateChanged)
          {
              tmmsg += "TmPacket PTU_STATE ";

              std::auto_ptr<TextMessage> mastMessage(activemqTMSender->sessionMonitor->createTextMessage
                      ("I'm a mast message"));
              mastMessage->setIntProperty("iter",seq);
              mastMessage->setLongProperty("time",time1);
              mastMessage->setIntProperty("Status", (int)MastState[MAST_STATUS_INDEX]);
              mastMessage->setFloatProperty("Pan", MastState[MAST_CURRENT_Q2_INDEX]);
              mastMessage->setFloatProperty("Tilt", MastState[MAST_CURRENT_Q3_INDEX]);
              //mastMessage->setIntProperty("ActionStatus", (int)MastState[MAST_ACTION_RET_INDEX]);
              //mastMessage->setIntProperty("ActionId", (int)MastState[MAST_ACTION_ID_INDEX]);
              activemqTMSender->ptuProducerMonitoring->send(mastMessage.get()); 
              for (int i=0; i<MAX_STATE_SIZE; i++)
              {
                  lastMastState[i]=MastState[i];
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
              else if (rover == ExoTeR)
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
              else if (rover == MaRTA)
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


