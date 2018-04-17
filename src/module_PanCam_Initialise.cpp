
#include "module_PanCam_Initialise.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  orc_Mod_PanCam_Initialise::orc_Mod_PanCam_Initialise (/*ModuleTask* mt,
							  int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_PanCam_Initialise", mt, indexclk*/)
  {
    //    PRINT1("** orc_Mod_PanCam_Initialise constructor")
  }
  
  orc_Mod_PanCam_Initialise::~orc_Mod_PanCam_Initialise ()
  {
    //  PRINT1( "** orc_Mod_PanCam_Initialise destructor" )
  }
  
  void orc_Mod_PanCam_Initialise::param (char *params)
  {
    fprintf (stderr, "PanCam_Initialise:: param\n");
    /*  
    int tmp1, tmp2, tmp3;
    if (3 != sscanf(params, "%d %d %d", 
		    &tmp1,
		    &tmp2,
		    &tmp3)) {
      std::cerr << "In PanCam_Initialise param failed" << std::endl;
      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
					       params);
      return;
    }
    */
    //
    // the action status is ok
    //
    action_exec_status = ACTION_RET_OK;
    
    
  }
  
  void orc_Mod_PanCam_Initialise::reparam (char *params)
  {
    //  fprintf( stderr, "PanCam_Initialise:: reparam\n" );
    // #include   "PanCam_Initialise/user_code/reparam_code.c"
  }
  
  void orc_Mod_PanCam_Initialise::init ()
  {
    std::cerr << "-> PanCam_Initialise: start init" << std::endl;
    //
    // if the action status is not ok (because of bad parameterisation
    // the code is not executed
    //
    if (action_exec_status != ACTION_RET_OK) {
      return;
    }
    
    
    // reset the counter
    index = 0;
    
    //
    // reset the events
    //
    PanCam_Initialise_prec = NO_EVENT;
    PanCam_Initialise_post = NO_EVENT;
    
    //
    // reset the states
    //
    for (int i=0; i<MAX_STATE_SIZE; i++) {
      PanCamState[i] = 0.0;
    }
    
    
    //
    // get the warm-up duration
    //
    warmUpTimeout = 10.0; // ((orc_PhR_PanCam *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()))->PanCamWarmUpTime; 
    //
    // Get Action ID
    //
    rtId = 51; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
    //
    // reset the resources of the robot task
    //
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
    */
    
    //
    // get the global state of the PanCam s/s to initialise the local variable
    //
    if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) PanCamState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "PanCamState");
    }
    
    //
    // set action execution information
    //
    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    
    //    PanCamState[PANCAM_NBRPACKETHK_INDEX]           = floor(warmUpTimeout/10); 
    //    PanCamState[PANCAM_NBRPACKETHKN_INDEX]          = floor(warmUpTimeout) - floor(warmUpTimeout/10);
    //    PanCamState[PANCAM_NBRPACKETHKDURATION_INDEX]   = warmUpTimeout;
    
    
    
    //
    // Check that the PANCAM State is OFF in order to accept the
    // Initialisation Action
    //
    /*
      if (PanCamState[PANCAM_OPER_MODE_INDEX] != PANCAM_OPER_MODE_OFF) {
      fprintf(stderr, "In PanCam_Initialise::init() PanCam not in PANCAM_OPER_MODE_OFF mode\n");
      PanCamState[ABORT_INDEX]       = ACTION_RET_ERROR;
      PanCamState[ABORT_ERROR_INDEX] = PANCAM_WRONG_STATE_ERROR;
      // set the actions status
      action_exec_status = ACTION_RET_ERROR;
      getModuleTaskPtr()->GetRobotTaskPtr()->setError(RT_EXEC_WRONG_MODE);
      ((orc_PhR_PanCam *)(Mt_ptr->GetRobotTaskPtr()->
      GetPhR ()))->statePanCamTransitionError(PanCamState[PANCAM_OPER_MODE_INDEX],
      PANCAM_OPER_MODE_STNDBY,
      (char *)getModuleTaskPtr()->GetRobotTaskPtr()->GetMnemonic().c_str());
      theRobotProcedure->ExitOnInitialStateError();
      return;
      }
    */
    
    
    //
    // set back the pancam state
    //
    if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) PanCamState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "PanCamState");
    }
    
    //
    // the preconditions are satisfied
    //
    PanCam_Initialise_prec = SET_EVENT;
    //    moduleSendEvent("PanCam_Initialise_prec;");
    
  }
  
  void orc_Mod_PanCam_Initialise::compute ()
  {
    //  std::cerr << "-> PanCam_Initialise: start compute:" << std::endl;
    
    //
    // if the action status is not ok the code is not executed
    //
    if (action_exec_status != ACTION_RET_OK) {
      return;
    }
    
    
    //
    // get the global state of the PanCam s/s to initialise the local variable
    //
    if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) PanCamState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "PanCamState");
    }
    
    //
    // Set the state of the PanCam s/s
    //
    PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_INIT;
    
    //
    // Set Action ID and Ret val
    //
    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    
    //
    // in the case of timeout on the temperature
    //
    if (index >= (warmUpTimeout/theRobotProcedure->GetClock()->GetBasePeriod())) {
      PanCamState[PANCAM_OPER_MODE_INDEX]   = PANCAM_OPER_MODE_STANDBY;
      // Set Action ID and Ret val
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      // send the post-condition
      PanCam_Initialise_post = SET_EVENT;
      //      moduleSendEvent("PanCam_Initialise_post;");
    }
    
    //
    // update the resources of the robot task
    //
    /*
    double energy_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
      PanCamState[PANCAM_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0;
    
    double memmass_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
      PanCamState[PANCAM_DATARATE_INDEX]*getSampleTime();
    
    double act_duration =
      getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
    
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

    //
    // set back the pancam state
    //
    if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) PanCamState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "PanCamState");
    }
    
    
    index++;


}

void orc_Mod_PanCam_Initialise::end ()
{
  fprintf( stderr, "PanCam_Initialise:: End\n" );
	PanCam_Initialise_prec = NO_EVENT;
	PanCam_Initialise_post = NO_EVENT;


}

}

// End class orc_Mod_PanCam_Initialise

