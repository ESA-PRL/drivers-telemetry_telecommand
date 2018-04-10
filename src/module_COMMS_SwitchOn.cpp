#include "module_COMMS_SwitchOn.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_COMMS_SwitchOn::orc_Mod_COMMS_SwitchOn(/*ModuleTask* mt,
						   int indexclk*/) 
//: ModuleAlgo("orc_Mod_COMMS_SwitchOn", mt, indexclk) 
  { 
    
  }
  
  orc_Mod_COMMS_SwitchOn::~orc_Mod_COMMS_SwitchOn() {
    
  }
  
  void orc_Mod_COMMS_SwitchOn::param(char *params) {  
    if (1 != sscanf(params, "%s", unitid)) {
      fprintf(stderr, "In COMMS_SwitchOnUnit param failed\n");
//      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
//					       params);
      return;
    }
    else {
      //   fprintf(stderr, "In COMMS_SwitchOnUnit param unitid = '%s'\n", unitid);
    }
  }
  
  void orc_Mod_COMMS_SwitchOn::reparam(char *params) { 
    
  }
  
  void orc_Mod_COMMS_SwitchOn::init() { 
    
    index = 0;
    
    for (int i=0; i<MAX_STATE_SIZE; i++) {
      CommsState[i] = 0.0;
    }
    
    COMMS_SwitchOn_prec = NO_EVENT;
    COMMS_SwitchOn_post = NO_EVENT;
    
    //CL 20152310 added to load the action duration parameter
    //    phrComms = (orc_PhR_Comms *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ());
    // Get Switch on time
    duration = 10; // phrComms->PARAM_COMMS_INITIALISATION_TIME; 
    
    // Get Action ID
    rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
    
    if ( theRobotProcedure->GetParameters()->get( "CommsState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) CommsState ) == ERROR ) {
//      theRobotProcedure->ExitOnMissingStateSymbol(
//						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
//						  "CommsState");
    }
    
    if (!strcmp(unitid, "MAIN")) {
      cmd_index = COMMS_MAIN_CMD_INDEX;
      status_index = COMMS_MAIN_STATUS_INDEX;
      final_state = ORC_COMMS_STATE_LST_RX;
    }
    else if (!strcmp(unitid, "REDUNDANT")) {
      cmd_index = COMMS_REDUNDANT_CMD_INDEX;
      status_index = COMMS_REDUNDANT_STATUS_INDEX;
      final_state = ORC_COMMS_STATE_LST_RX;
    }
    else {
      cmd_index = COMMS_MAIN_CMD_INDEX;
      status_index = COMMS_MAIN_STATUS_INDEX;
      final_state = ORC_COMMS_STATE_LST_RX;
//      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
//					       unitid);
    }
    
    cmd_id = ORC_TC_LST_RX;
    
    CommsState[COMMS_ACTION_ID_INDEX]  = rtId;
    CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    
    CommsState[cmd_index] = cmd_id;
    
    // CL 20152310 commented
    //duration = 3.5;
    //current_time = 0.0;
    
    //
    // reset the resources of the robot task
    //
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
						 */

    if ( theRobotProcedure->GetParameters()->set( "CommsState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) CommsState ) == ERROR ) {
//      theRobotProcedure->ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
//						  "CommsState");
    }
    
    COMMS_SwitchOn_prec = SET_EVENT;
//    moduleSendEvent("COMMS_SwitchOn_prec;");
  }
  
  void orc_Mod_COMMS_SwitchOn::compute() { 
    
    //
    // get the global state
    //
    if ( theRobotProcedure->GetParameters()->get( "CommsState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) CommsState ) == ERROR ) {
//      theRobotProcedure->ExitOnMissingStateSymbol(
//						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
//						  "CommsState");
    }
    
    // Set Action ID and Ret val
    CommsState[COMMS_ACTION_ID_INDEX]  = rtId;
    CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    CommsState[status_index] = ORC_COMMS_STATE_INIT;
    
    //std::cerr << "In COMMS_SwitchOnUnit: " << CommsState[status_index] << std::endl;
    //if (CommsState[status_index] == final_state) {
    
    //CL 20152310 WAS if (current_time  > duration ) {
    if (index  > (duration/0.2)) { 		
      // Set Action ID and Ret val
      CommsState[COMMS_ACTION_ID_INDEX] = 0;
      CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
      COMMS_SwitchOn_post = SET_EVENT;
//      moduleSendEvent("COMMS_SwitchOn_post;");
      CommsState[status_index]  = final_state;
    }
    
    
    /*
    double act_duration =
    getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
						 */
    //
    // set the global state
    //
    if ( theRobotProcedure->GetParameters()->set( "CommsState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) CommsState ) == ERROR ) {
//      theRobotProcedure->ExitOnMissingStateSymbol(
//						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
//						  "CommsState");
    }
    
    //CL 20152310 commented
    //current_time  = current_time  + getSampleTime();
    index ++;
    
    // end example code
  }
  
  void orc_Mod_COMMS_SwitchOn::end() {
    COMMS_SwitchOn_prec = NO_EVENT;
    COMMS_SwitchOn_post = NO_EVENT;
  }
  
}

// End class orc_Mod_COMMS_SwitchOn

