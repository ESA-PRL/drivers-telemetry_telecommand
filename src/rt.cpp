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
  dhs_go2_duration = 5.0;
  comms_switchon_duration = 3.5; 
  comms_conf_duration = 4.0;

  param_completed   = 0;
  init_completed    = 0;
  compute_completed = 0;
  end_completed     = 0;
  current_time = 0.0;
  index = 0;
  post_cond = 0;

  // set the name
  rtName = name;
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


void RobotTask::waitEndActionExec () {
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
  
  int run = TRUE;
  do
    {
      if (rtName == "ADE_LEFT_Initialise") { 
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
      
      else if (rtName == "MAST_DEP_Initialise") { 
	computeMAST_DEP_Initialise();
      }
      else if (rtName == "MAST_DEP_Deploy") { 
	computeMAST_DEP_Deploy();
      }
      else if (rtName == "MAST_PTU_Initialise") { 
	computeMAST_PTU_Initialise();
      }
      else if (rtName == "MAST_PTU_MoveTo") { 
    	//computeMAST_PTU_MoveTo();
        if (param_completed==0){
        CommandInfo *cmd_info = new CommandInfo(rtName, rtParams);
        activemqTCReceiver->addCommandInfo(cmd_info);
        param_completed=1;
        }
        else
        {
            // notify activity running    
        }
      }
      else if (rtName == "MAST_SwitchOff") { 
	computeMAST_SwitchOff();
      }
      
      else if (rtName == "GNC_Initialise") { 
	computeGNC_Initialise();
      }
      else if (rtName == "GNC_LLO") { 
	computeGNC_LLO();
      }
      else if (rtName == "GNC_SwitchOff") { 
	computeGNC_SwitchOff();
      }
      
      else if (rtName == "RV_WakeUp") { 
	computeRV_WakeUp();
      }
      else if (rtName == "MMS_WaitAbsTime") { 
	computeMMS_WaitAbsTime();
      }
      else if (rtName == "RV_Prepare4Comms") { 
	computeRV_Prepare4Comms();
      }
      else if (rtName == "RV_PostComms") { 
	computeRV_PostComms();
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




void RobotTask::computeBEMA_Deploy_1(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeBEMA_Deploy_2(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computeGNC_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  static int index = 0; 
  GNCState[GNC_ACTION_ID_INDEX]  = 754.0;
  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_OFF; 
  if (index == 10) {
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
void RobotTask::computeGNC_LLO(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeGNC_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_STNDBY; 
  GNCState[GNC_ACTION_ID_INDEX]  = 753.0;
  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  if (index == 10) {
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
}

void RobotTask::computeRV_WakeUp(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 10) {
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

void RobotTask::computeMMS_WaitAbsTime(){ 
  std::cerr << rtName << std::endl; 
}
void RobotTask::computeRV_Prepare4Comms(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "TTCState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) TTCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (index == 10) {
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

void RobotTask::computeRV_PostComms(){ 
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
void RobotTask::computeDHS_Go2Nominal(){ 
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

void RobotTask::computeRV_Prepare4Travel(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (index == 10) {
    post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeRV_Prepare4Night(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (index == 10) {
    post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeRV_Prepare4Dozing(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (index == 10) {
    post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
