
#include "module_COMMS_LST2WH.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  orc_Mod_COMMS_LST2WH::orc_Mod_COMMS_LST2WH (/*ModuleTask* mt,
						int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_COMMS_LST2WH", mt, indexclk*/)
  {
    
  }
  
  orc_Mod_COMMS_LST2WH::~orc_Mod_COMMS_LST2WH ()
  {

  }
  
  void orc_Mod_COMMS_LST2WH::param (char *params)
  {
    fprintf (stderr, "COMMS_LST2WH:: param\n");
  
    if (1 != sscanf(params, "%s", unitid)) {
      fprintf(stderr, "In COMMS_LST2WH param failed\n");
      //      theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
      return;
    }
  }
  
  void orc_Mod_COMMS_LST2WH::reparam (char *params)
  {
    
  }
  
  void orc_Mod_COMMS_LST2WH::init ()
  {
    //  std::cerr << "-> COMMS_LST2WH: start init" << std::endl;
    
    // example code
    index = 0;
    
    for (int i=0; i<MAX_STATE_SIZE; i++) {
      CommsState[i] = 0.0;
    }
    
    COMMS_LST2WH_prec = NO_EVENT;
    COMMS_LST2WH_post = NO_EVENT;
    
    // Get Action ID
    rtId = 23; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
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
    }
    else if (!strcmp(unitid, "REDUNDANT")) {
      cmd_index = COMMS_REDUNDANT_CMD_INDEX;
      status_index = COMMS_REDUNDANT_STATUS_INDEX;
    }
    else {
      cmd_index = COMMS_MAIN_CMD_INDEX;
      status_index = COMMS_MAIN_STATUS_INDEX;
      //      theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), unitid);
    }
    
    cmd_id  = ORC_TC_WH_RX;
    final_state = ORC_COMMS_STATE_WH_RX;
    
    CommsState[COMMS_ACTION_ID_INDEX]  = rtId;
    CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    
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
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "CommsState");
    }
    
    COMMS_LST2WH_prec = SET_EVENT;
    //    moduleSendEvent("COMMS_LST2WH_prec;");
    
  }
  
  void orc_Mod_COMMS_LST2WH::compute ()
  {
    //  std::cerr << "-> COMMS_LST2WH: start compute" << std::endl;
    
    // Get Action ID
    rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
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
    
    // example code
    if (index == 2) {
      CommsState[cmd_index] = cmd_id;
    }
    
    // if (CommsState[status_index] == final_state) {
    if (index >= 10) {
      // Set Action ID and Ret val
      CommsState[COMMS_ACTION_ID_INDEX] = 0;
      CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;
      CommsState[status_index] = final_state;
      
      printf("state: %d \n",final_state);
      
      COMMS_LST2WH_post = SET_EVENT;
      //      moduleSendEvent("COMMS_LST2WH_post;");
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
    
    index ++;
    
  }
  
  void orc_Mod_COMMS_LST2WH::end ()
  {
    //  fprintf( stderr, "COMMS_LST2WH:: End\n" );
    COMMS_LST2WH_prec = NO_EVENT;
    COMMS_LST2WH_post = NO_EVENT;
  }

}

// End class orc_Mod_COMMS_LST2WH

