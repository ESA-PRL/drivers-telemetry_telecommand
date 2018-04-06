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
      if (rtName == "ADEs_Activate") { 
          computeADEs_Activate();
      }
      else if (rtName == "ADEs_DeActivate") { 
          computeADEs_DeActivate();
      }
      else if (rtName == "ADE_LEFT_Initialise") { 
	computeADE_LEFT_Initialise();
      }
      else if (rtName == "ADE_LEFT_conf") { 
	computeADE_LEFT_conf();
      }
      else if (rtName == "ADE_LEFT_ReleaseHDRM") { 
	computeADE_LEFT_ReleaseHDRM();
      }
      else if (rtName == "ADE_LEFT_SwitchOff") { 
	computeADE_LEFT_SwitchOff();
      }
      else if (rtName == "ADE_RIGHT_Initialise") { 
	computeADE_RIGHT_Initialise();
      }
      else if (rtName == "ADE_RIGHT_conf") {
	computeADE_RIGHT_conf();
      }
      else if (rtName == "ADE_RIGHT_ReleaseHDRM") { 
	computeADE_RIGHT_ReleaseHDRM();
      }
      else if (rtName == "ADE_RIGHT_SwitchOff") { 
	computeADE_RIGHT_SwitchOff();
      }
      else if (rtName == "SA_LEFT_Initialise") { 
	computeSA_LEFT_Initialise();
      }
      else if (rtName == "SA_LEFT_PrimaryMoveTo") { 
	computeSA_LEFT_PrimaryMoveTo();
      }
      else if (rtName == "SA_LEFT_SecondaryMoveTo") { 
	computeSA_LEFT_SecondaryMoveTo();
      }
      else if (rtName == "SA_LEFT_SwitchOff") { 
	computeSA_LEFT_SwitchOff();
      }
      else if (rtName == "SA_RIGHT_Initialise") { 
	computeSA_RIGHT_Initialise();
      }
      else if (rtName == "SA_RIGHT_PrimaryMoveTo") { 
	computeSA_RIGHT_PrimaryMoveTo();
      }
      else if (rtName == "SA_RIGHT_SecondaryMoveTo") { 
	computeSA_RIGHT_SecondaryMoveTo();
      }
      else if (rtName == "SA_RIGHT_SwitchOff") { 
	computeSA_RIGHT_SwitchOff();
      }
      else if (rtName == "Deploy_LEFT_SA") { 
          computeDeploy_LEFT_SA();
      }
      else if (rtName == "Deploy_RIGHT_SA") { 
          computeDeploy_RIGHT_SA();
      }
      
      else if (rtName == "PanCam_Initialise") { 
	computePanCam_Initialise();
      }
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
      else if (rtName == "PanCam_PIUSwitchOff") { 
	computePanCam_PIUSwitchOff();
      }
      else if (rtName == "PANCAM_WAC_RRGB") { 
	computePANCAM_WAC_RRGB();
      }
      else if (rtName == "PanCam_FilterSel") { 
	computePanCam_FilterSel();
      }
      
      else if (rtName == "MAST_TILT_Initialise") { 
	computeMAST_TILT_Initialise();
      }
     else if (rtName == "MAST_PAN_Initialise") { 
	computeMAST_PAN_Initialise();
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
      else if (rtName == "GNC_Initialise") { 
	computeGNC_Initialise();
      }
      else if (rtName == "Release_Umbilical") { 
          computeRelease_Umbilical();
      }
      else if (rtName == "GNC_SwitchOff") { 
	computeGNC_SwitchOff();
      }
      else if (rtName == "GNC_MonitoringOnly") { 
	computeGNC_MonitoringOnly();
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
      else if (rtName == "DHS_Go2Nominal") { 
	computeDHS_Go2Nominal();
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


      sleep(1);
      
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

int RobotTask::computeGNC_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  static int index = 0; 
  GNCState[GNC_ACTION_ID_INDEX]  = 754.0;
  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_OFF; 
  if (index == 2) {
    GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_STNDBY;
    GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;
    GNCState[GNC_ACTION_ID_INDEX]  = 0.0;
    post_cond = 1;
    index = 0;
  }

  index++;
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeGNC_SwitchOff(){
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  GNCState[GNC_ACTION_ID_INDEX]  = 753.0;
  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  if (index == 2) {
    GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_OFF;
    GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;
    GNCState[GNC_ACTION_ID_INDEX]  = 0.0;
    post_cond = 1;
    index = 0;
  }
  index++;
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

int RobotTask::computeGNC_MonitoringOnly(){
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  GNCState[GNC_ACTION_ID_INDEX]  = 753.0;
  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  if (index == 2) {
    GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_MONO;
    GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;
    GNCState[GNC_ACTION_ID_INDEX]  = 0.0;
    post_cond = 1;
    index = 0;
  }
  index++;
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

int RobotTask::computeRV_WakeUp(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 2) {
    post_cond = 1;
  }

  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    param_completed = 1;
  }
  if (init_completed == 0){
    // set the duration
    rvr_duration = dhs_go2_duration + 
      comms_switchon_duration +
      comms_conf_duration +
      comms_switchon_duration +
      comms_conf_duration;

    init_completed = 1;
  }

  if (compute_completed == 0){ 
    // ActivateActionFromTask()("DHS_Go2Reduced", "");
    // ActivateActionFromTask()("COMMS_SwitchOn", "MAIN");
    // ActivateActionFromTask()("COMMS_Conf", "MAIN WH");
    // ActivateActionFromTask()("COMMS_SwitchOn", "REDUNDANT");
    // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT WH");

    if (index >= ((rvr_duration)/theRobotProcedure->Clock->GetBasePeriod())) {
      
      // because the previous action ("COMMS_Conf", "REDUNDANT WH") completed 
      TTCState[COMMS_ACTION_ID_INDEX]  = 0;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
      TTCState[COMMS_REDUNDANT_STATUS_INDEX] = ORC_COMMS_STATE_WH_RX;
      // finished
      post_cond = 1;
    }
    else if (index >= ((dhs_go2_duration + 
			comms_switchon_duration + 
			comms_conf_duration +
			comms_switchon_duration
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT WH");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
      
      // because the previous action ("COMMS_SwitchOn", "REDUNDANT") completed 
      TTCState[COMMS_REDUNDANT_STATUS_INDEX] = ORC_COMMS_STATE_INIT;
    }
    else if (index >= ((dhs_go2_duration + 
			comms_switchon_duration + 
			comms_conf_duration 
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_SwitchOn", "REDUNDANT");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_SwitchOn_ID;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

      // because the previous action ("COMMS_Conf", "MAIN WH") completed 
      TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_WH_RX;
      TTCState[COMMS_ACTION_ID_INDEX]  = 0;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
    }
    else if (index >= ((dhs_go2_duration + 
			comms_switchon_duration 
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_Conf", "MAIN WH");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
      // TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_INIT;
      
      // because the previous action (COMMS_SwitchOn) completed 
    }
    else if (index >= ((dhs_go2_duration 
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_SwitchOn", "MAIN");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_SwitchOn_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
      TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_INIT;

      // because the previous action (DHS_Go2Reduced) completed 
      DHSState[DHS_STATUS_INDEX]     = DHS_OPER_MODE_REDUCED;
      DHSState[DHS_ACTION_ID_INDEX]  = 0;
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;
    }
    else if (index >= 0 ) {
      // ActivateActionFromTask()("DHS_Go2Reduced", "");
      DHSState[DHS_ACTION_ID_INDEX]  = DHS_Go2Reduced_ID; 
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    }
    
    index++;
    
  }

  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeMMS_WaitAbsTime(){ 
  std::cerr << rtName << std::endl; 

  double warmUpTimeout = 10;
  if (index >= (warmUpTimeout/theRobotProcedure->Clock->GetBasePeriod())) {
    post_cond = 1;
  }

  index++;
}

int RobotTask::computeMMS_WaitRelTime(){ 
  std::cerr << rtName << std::endl; 

  double warmUpTimeout = 10;
  if (index >= (warmUpTimeout/theRobotProcedure->Clock->GetBasePeriod())) {
    post_cond = 1;
  }

  index++;
}

int RobotTask::computeRV_Prepare4Comms(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 2) {
    post_cond = 1;
  }

  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    param_completed = 1;
  }
  if (init_completed == 0){
    rvr_duration = dhs_go2_duration + 
      comms_conf_duration +
      comms_conf_duration;
    
    init_completed = 1;
  }
  
  if (compute_completed == 0){ 
    
    // ActivateActionFromTask()("COMMS_Conf", "MAIN LST");
    // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT LST");
    // ActivateActionFromTask()("DHS_Go2HighPwr", "");

    if (index >= ((rvr_duration)/theRobotProcedure->Clock->GetBasePeriod())) {
      
      // because the previous action ("DHS_Go2HighPwr") completed 
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_HIGHPOWER;
      DHSState[DHS_ACTION_ID_INDEX]  = 0.0;
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      // finished
      post_cond = 1;
    }
    else if (index >= ((dhs_go2_duration + 
			comms_conf_duration
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("DHS_Go2HighPwr", "")
      DHSState[DHS_ACTION_ID_INDEX]  = DHS_Go2HighPwr_ID; 
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
      
      // because the previous action (("COMMS_Conf", "REDUNDANT LST") completed 
      TTCState[COMMS_REDUNDANT_STATUS_INDEX] = ORC_COMMS_STATE_LST_RX;
      TTCState[COMMS_ACTION_ID_INDEX]  = 0;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
    }
    else if (index >= ((dhs_go2_duration 
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT LST");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

      // because the previous action ("COMMS_Conf", "MAIN LST") completed 
      TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_LST_RX;
    }
    else if (index >= 0 ) {
      // ActivateActionFromTask()("COMMS_Conf", "MAIN LST");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    }
    
    index++;
    
  }

  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeRV_PostComms(){ 
  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    param_completed = 1;
  }
  if (init_completed == 0){
    rvr_duration = comms_conf_duration +
      comms_conf_duration + 
      dhs_go2_duration;

    init_completed = 1;
  }
  
  if (compute_completed == 0){ 
    
  // ActivateActionFromTask()("COMMS_Conf", "MAIN WH");
  // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT WH");
  // ActivateActionFromTask()("DHS_Go2Reduced", "");

    if (index >= ((rvr_duration)/theRobotProcedure->Clock->GetBasePeriod())) {
      
      // because the previous action ("DHS_Go2Reduced", "") completed 
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_REDUCED;
      DHSState[DHS_ACTION_ID_INDEX]  = 0.0;
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      // finished
      post_cond = 1;
    }
    else if (index >= ((comms_conf_duration + 
			comms_conf_duration
			) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("DHS_Go2Reduced", "")
      DHSState[DHS_ACTION_ID_INDEX]  = DHS_Go2Reduced_ID; 
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
      
      // because the previous action (("COMMS_Conf", "REDUNDANT LST") completed 
      TTCState[COMMS_REDUNDANT_STATUS_INDEX] = ORC_COMMS_STATE_LST_RX;
      TTCState[COMMS_ACTION_ID_INDEX]  = 0.0;
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
    }
    else if (index >= (( comms_conf_duration
			 ) / 
		       theRobotProcedure->Clock->GetBasePeriod())) {
      // ActivateActionFromTask()("COMMS_Conf", "REDUNDANT WH");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

      // because the previous action ("COMMS_Conf", "MAIN WH") completed 
      TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_LST_RX;
    }
    else if (index >= 0 ) {
      // ActivateActionFromTask()("COMMS_Conf", "MAIN WH");
      TTCState[COMMS_ACTION_ID_INDEX]  = COMMS_Conf_ID; 
      TTCState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    }
    
    index++;
    
  }

  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
//
//
//
int RobotTask::computeDHS_Go2Nominal(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "DHSState", 
						DOUBLE, MAX_STATE_SIZE, 0, 
						( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    param_completed = 1;
  }
  if (init_completed == 0){
    init_completed = 1;
  }
  
  if (compute_completed == 0){ 

    DHSState[DHS_ACTION_ID_INDEX]  = DHS_Go2Nominal_ID; 
    DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index >= ((dhs_go2_duration) / 
		  theRobotProcedure->Clock->GetBasePeriod())) {
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_NOMINAL;
      DHSState[DHS_ACTION_ID_INDEX]  = 0.0;
      DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }
  }
  if (end_completed == 0){
    end_completed = 1;
  }
  
  index++;

  if ( theRobotProcedure->GetParameters()->set( "DHSState", 
						DOUBLE, MAX_STATE_SIZE, 0, 
						( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeRV_SwitchOffMobility(){
  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 2) {
      GNCState[GNC_STATUS_INDEX] = GNC_OPER_MODE_OFF;
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_REDUCED;
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeRelease_Umbilical(){
  std::cerr << rtName << std::endl; 
  double duration = 5.0; // sec
  if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
    post_cond = 1;
  }
  index++;
}

int RobotTask::computeRV_Prepare4Travel(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 2) {
      GNCState[GNC_STATUS_INDEX] = GNC_OPER_MODE_ABS_LOC;
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_HIGHPOWER;
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
      post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeRV_Prepare4Night(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 2) {
      DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_REDUCED;
      TTCState[COMMS_MAIN_STATUS_INDEX] = ORC_COMMS_STATE_OFF;
      TTCState[COMMS_REDUNDANT_STATUS_INDEX] = ORC_COMMS_STATE_OFF;
      post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "DHSState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "TTCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeRV_Prepare4Dozing(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (index == 2) {
    post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
