#include "rt.h"
#include "param.h"
#include "prr.h"
#include "RobotProcedure.h"
#include "comm.h"
#include "ActiveMQTCReceiver.h"

#define COMMS_SwitchOn_ID 150
#define COMMS_Conf_ID 140
#define DHS_Go2Nominal_ID 110
#define DHS_Go2Reduced_ID 100
#define DHS_Go2HighPwr_ID 120

extern ActiveMQTCReceiver* activemqTCReceiver;

RobotTask::RobotTask (std::string name)
{
  std::cout << "** RobotTask constructor:" << name << std::endl;
  tcRequestId = -1;

  if (( waitEndActionSem = orcSemCreate( ORCEMPTY ) ) == NULL ) {
    //EventStorage->displayError( RT_ERROR3, Clock->GetTime() );
  }
  for (int i=0; i<MAX_STATE_SIZE; i++) {
    State[i] = 0.0;
    ADEState[i] = 0.0;
    SAState[i] = 0.0;
    PanCamState[i] = 0.0;
    MastState[i] = 0.0;
    GNCState[i] = 0.0;
    TTCState[i] = 0.0;
    DHSState[i] = 0.0;
  }
  dhs_go2_duration = 2.0;
  comms_switchon_duration = 2.5;
  comms_conf_duration = 2.0;

  param_completed   = 0;
  init_completed    = 0;
  compute_completed = 0;
  end_completed     = 0;
  current_time = 0.0;
  index = 0;
  post_cond = 0;

  // set the name
  rtName = name;

  // sequence counters for SA deployment
  deploy_left_sa_seq = 0;
  deploy_right_sa_seq = 0;
}

RobotTask::~RobotTask ()
{
}

int RobotTask::SetTcRequestId (int tc_req_id) {
  tcRequestId = tc_req_id;
}

int RobotTask::GetTcRequestId () {
  return tcRequestId;
}


int RobotTask::Control ()
{
  if ( createThread() == ERROR ) {
    return 0;
  }
  
  return 1;
}


int RobotTask::waitEndActionExec () {
  if ( orcSemTake( waitEndActionSem, ORCFOREVER ) == ERROR ) {
    
  }
}

std::string RobotTask::GetName ()
{
  return rtName;
}
int RobotTask::GetId ()
{
  return rtId;
}

int RobotTask::SetParam (char* params)
{
  strcpy(rtParams, params);
}


void* RobotTask::thread ()
{
  std::cerr << "++ Thread RobotTask::thread spawned" << std::endl;
        if (post_cond == 1) {
	post_cond = 0;
	//current_time = 0.0;
	//index = 0;
	//param_completed = 0;
	//init_completed = 0;
	//compute_completed = 0;
	//end_completed = 0;
      }

  int run = TRUE;
  do
    {
      //
      // PANCAM s/s KK
      //
      if (rtName == "PanCam_Initialise") { 
	computePanCam_Initialise();
      }
      else if (rtName == "PanCam_PIUSwitchOff") { 
	computePanCam_PIUSwitchOff();
      }
      /*
      else if (rtName == "PanCam_InitWACs") { 
	computePanCam_InitWACs();
      }
      else if (rtName == "PanCam_SwitchOn") { 
	computePanCam_SwitchOn();
      }
      else if (rtName == "PanCam_WACAcqImage") { 
	computePanCam_WACAcqImage();
      }
      else if (rtName == "PanCam_WACGetImage") { 
	computePanCam_WACGetImage();
      }
      else if (rtName == "PanCam_SwitchOff") { 
	computePanCam_SwitchOff();
      }
      else if (rtName == "PANCAM_WAC_RRGB") { 
	computePANCAM_WAC_RRGB();
      }
      else if (rtName == "PanCam_FilterSel") { 
	computePanCam_FilterSel();
      }
      */
      
      //
      // MAST s/s 
      // MAST_DEP_MoveTo, MAST_PAN_MoveTo, MAST_TILT_MoveTo, 
      // MAST_PTU_MoveTo are missing (TBC that are implemented)
      // 
      else if (rtName == "MAST_DEP_Initialise") { 
    computeMAST_DEP_Initialise();
      }
     else if (rtName == "MAST_PAN_Initialise") { 
	computeMAST_PAN_Initialise();
      }
      else if (rtName == "MAST_TILT_Initialise") { 
	computeMAST_TILT_Initialise();
      }
      else if (rtName == "MAST_DEP_SwitchOff") { 
	computeMAST_DEP_SwitchOff();
      }
      else if (rtName == "MAST_PAN_SwitchOff") { 
	computeMAST_PAN_SwitchOff();
      }
      else if (rtName == "MAST_TILT_SwitchOff") { 
	computeMAST_TILT_SwitchOff();
      }
      else if (rtName == "Deploy_Mast") {
	computeDeploy_Mast();
        if (post_cond == 1)
        {
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
        }
      }

      //
      // DHS s/s
      //
      else if (rtName == "DHS_HighPwr2Reduced") { 
	computeDHS_HighPwr2Reduced();
      }
      else if (rtName == "DHS_LowPwr2Reduced") { 
	computeDHS_LowPwr2Reduced();
      }
      else if (rtName == "DHS_Nominal2Reduced") { 
	computeDHS_Nominal2Reduced();
      }
      else if (rtName == "DHS_Reduced2HighPwr") { 
	computeDHS_Reduced2HighPwr();
      }
      else if (rtName == "DHS_Reduced2LowPwr") { 
	computeDHS_Reduced2LowPwr();
      }
      else if (rtName == "DHS_Reduced2Nominal") { 
	computeDHS_Reduced2Nominal();
      }

      //
      // COMMS s/s
      //
      else if (rtName == "COMMS_SwitchOn") { 
	computeCOMMS_SwitchOn();
      }
      else if (rtName == "COMMS_LST2WH") { 
	computeCOMMS_LST2WH();
      }
      else if (rtName == "COMMS_WH2LST") { 
	computeCOMMS_WH2LST();
      }
      else if (rtName == "COMMS_SwitchOff") { 
	computeCOMMS_SwitchOff();
      }

      //
      // SA s/s
      //
      else if (rtName == "Deploy_LEFT_SA") { 
	computeDeploy_LEFT_SA();
      }
      else if (rtName == "Deploy_RIGHT_SA") { 
	computeDeploy_RIGHT_SA();
      }
      else if (rtName == "SA_LEFT_Primary_Initialise") { 
	computeSA_LEFT_Primary_Initialise();
      }
      else if (rtName == "SA_LEFT_Primary_MoveTo") { 
	computeSA_LEFT_Primary_MoveTo();
      }
      else if (rtName == "SA_LEFT_Primary_SwitchOff") { 
	computeSA_LEFT_Primary_SwitchOff();
      }
      else if (rtName == "SA_LEFT_Secondary_Initialise") { 
	computeSA_LEFT_Secondary_Initialise();
      }
      else if (rtName == "SA_LEFT_Secondary_MoveTo") { 
	computeSA_LEFT_Secondary_MoveTo();
      }
      else if (rtName == "SA_LEFT_Secondary_SwitchOff") { 
	computeSA_LEFT_Secondary_SwitchOff();
      }
      else if (rtName == "SA_RIGHT_Primary_Initialise") { 
	computeSA_RIGHT_Primary_Initialise();
      }
      else if (rtName == "SA_RIGHT_Primary_MoveTo") { 
	computeSA_RIGHT_Primary_MoveTo();
      }
      else if (rtName == "SA_RIGHT_Primary_SwitchOff") { 
	computeSA_RIGHT_Primary_SwitchOff();
      }
      else if (rtName == "SA_RIGHT_Secondary_Initialise") { 
	computeSA_RIGHT_Secondary_Initialise();
      }
      else if (rtName == "SA_RIGHT_Secondary_MoveTo") { 
	computeSA_RIGHT_Secondary_MoveTo();
      }
      else if (rtName == "SA_RIGHT_Secondary_SwitchOff") { 
	computeSA_RIGHT_Secondary_SwitchOff();
      }

      //
      // ADE s/s
      //
      else if (rtName == "ADE_Operational2Standby") { 
	computeADE_Operational2Standby();
      }
      else if (rtName == "ADE_Standby2Operational") { 
	computeADE_Standby2Operational();
      }
      else if (rtName == "ADE_SwitchOn") { 
	computeADE_SwitchOn();
      }
      else if (rtName == "ADE_SwitchOff") { 
	computeADE_SwitchOff();
      }
      else if (rtName == "ADEs_Activate") { 
	computeADEs_Activate();
      }
      else if (rtName == "ADEs_DeActivate") { 
	computeADEs_DeActivate();
      }
      else if (rtName == "ADE_ReleaseHDRM") { 
	computeHDRM_Release();
      }
      else if (rtName == "HDRM_Release") { 
	computeHDRM_Release();
      }

      //
      // GNC s/s
      //
      else if (rtName == "GNC_Initialise") { 
	computeGNC_Initialise();
      }
      else if (rtName == "GNC_MonitoringOnly") { 
	computeGNC_MonitoringOnly();
      }
      else if (rtName == "GNC_SwitchOff") { 
	computeGNC_SwitchOff();
      }
      else if (rtName == "GNC_AbsLocalisation") { 
	computeGNC_AbsLocalisation();
      }


      else if (rtName == "Release_Umbilical") { 
          computeRelease_Umbilical();
      }
      else if (rtName == "RV_WakeUp") { 
	computeRV_WakeUp();
      }
      else if (rtName == "MMS_WaitAbsTime") { 
	computeMMS_WaitAbsTime();
      }
      else if (rtName == "MMS_WaitRelTime") { 
	computeMMS_WaitRelTime();
      }
      else if (rtName == "RV_Prepare4Comms") { 
	computeRV_Prepare4Comms();
      }
      else if (rtName == "RV_PostComms") { 
	computeRV_PostComms();
      }
      else if (rtName == "RV_SwitchOffMobility") { 
	computeRV_SwitchOffMobility();
      }
      else if (rtName == "RV_Prepare4Travel") { 
	computeRV_Prepare4Travel();
      }
      else if (rtName == "RV_Prepare4Night") { 
	computeRV_Prepare4Night();
      }
      else if (rtName == "RV_Prepare4Dozing") { 
	computeRV_Prepare4Dozing();
      }
      else if (rtName == "Release_Body") { 
	computeRelease_Body();
      }

    else if (rtName == "GNC_LLO") {
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_ACKERMANN_GOTO") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_TURNSPOT_GOTO") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_TRAJECTORY") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_TRAJECTORY_WISDOM") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "MAST_PTU_MoveTo") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "PANCAM_PANORAMA") {
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "TOF_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "LIDAR_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "NAVCAM_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "FRONT_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "MAST_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "PANCAM_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "REAR_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "LOCCAM_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "HAZCAM_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "Deployment_All") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "Deployment_Front") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "Deployment_Rear") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_Update") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_ACKERMANN_DIRECT") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNC_TURNSPOT_DIRECT") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "ALL_ACQ") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "GNCG") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }
    else if (rtName == "ABORT") { 
        if (param_completed == 0){
            CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
            activemqTCReceiver->addCommandInfo(cmd_info);
            param_completed=1;
        }
        else if (post_cond == 1)
        {
            // notify activity finished    
        }
        else
        {
            // notify activity running
        }
    }

      usleep(200 * 1000); // KK sleep replaced by usleep
      
      if (post_cond == 1) {
	run = FALSE;
	post_cond = 0;
	current_time = 0.0;
	index = 0;
	param_completed = 0;
	init_completed = 0;
	compute_completed = 0;
	end_completed = 0;
      }
    }
  while ( run );
  
  
  // at the end of the Control method
  if ( orcSemGive(waitEndActionSem) == ERROR ) { 
    return NULL;
  }
  
  std::cout << "-- Thread RobotTask::thread terminated" << std::endl;
}




int RobotTask::computeBEMA_Deploy_1(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
int RobotTask::computeBEMA_Deploy_2(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}



