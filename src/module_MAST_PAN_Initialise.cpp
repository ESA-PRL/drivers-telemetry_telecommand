
#include "module_MAST_PAN_Initialise.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_MAST_PAN_Initialise::orc_Mod_MAST_PAN_Initialise (/*ModuleTask* mt,
							      int indexclk*/)
  //    : ModuleAlgo ("orc_Mod_MAST_PAN_Initialise", mt, indexclk)
  {
    //    PRINT1("** orc_Mod_MAST_PAN_Initialise constructor")
  }
  
  orc_Mod_MAST_PAN_Initialise::~orc_Mod_MAST_PAN_Initialise ()
  {
    //    PRINT1( "** orc_Mod_MAST_PAN_Initialise destructor" )
  }
  
  void orc_Mod_MAST_PAN_Initialise::param (char *params)
  {
    
    //  fprintf (stderr, "MAST_PAN_Initialise: param %s\n", params);
    
    int tmp1, tmp2;
    if (2 != sscanf(params, "%d %d", &tmp1, &tmp2)) {
      
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      //      MastState[ABORT_ERROR_INDEX] = MAST_PARAMETERISATION_ERROR;
      //      theRobotProcedure->
      //	ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //			      params);
      return;
    }

    targetMechanism = TARGET_MECHANISM_PAN;

    // the action status is ok
    action_exec_status = ACTION_RET_OK;
    
    //
    // get the Mast state
    //
    if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) MastState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //
    // Not any parameters are considered
    //
    
    
  }
  
  void orc_Mod_MAST_PAN_Initialise::reparam (char *params)
  {
    //  fprintf( stderr, "MAST_PAN_Initialise:: reparam\n" );
    // #include   "MAST_PAN_Initialise/user_code/reparam_code.c"
  }
  
  void orc_Mod_MAST_PAN_Initialise::init ()
  {
    //    std::cerr << "MAST_PAN_Initialise: init" << std::endl;
    
    //
    // if the action status is not ok (because of bad parameterisation
    // the code is not executed
    //
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_PAN_Initialise::init() action status = error\n");
      //      moduleSendEvent("MAST_PAN_Initialise_exc;");
      return;
    }
    
    // reset the counter
    index = 0;
    
    // reset the events
    MAST_PAN_Initialise_prec = NO_EVENT;
    MAST_PAN_Initialise_post = NO_EVENT;
    
    // reset the power and the mast states
    for (int i=0; i<MAX_STATE_SIZE; i++) {
      MastState[i] = 0.0;
    }
    
    // get the action Id
    rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
    // get the reference to the physical resource
    //    phrMast = ((orc_PhR_Mast *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()));
    
    
    //
    // get the Mast state
    //
    if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) MastState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    // get the parameters from the mast s/s
    if (targetMechanism == TARGET_MECHANISM_PAN) {
      // warmUpTimeout              = MastState[MAST_WARMUP_TIME_PAN_INDEX];
    }
    else if (targetMechanism == TARGET_MECHANISM_TILT) {
      // warmUpTimeout              = MastState[MAST_WARMUP_TIME_TILT_INDEX];
    }
    else if (targetMechanism == TARGET_MECHANISM_PAN_TILT) {
      // warmUpTimeout              = MastState[MAST_WARMUP_TIME_TILT_INDEX];
    }
    warmUpTimeout = 10.0; 
    
    
    // set action execution information
    MastState[MAST_ACTION_ID_INDEX]  = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    
    //
    // we don't check if the mast mode is OFF because it may
    // that mast has been initialised and not the ptu
    //
    
    //
    // Check that the MAST State is OFF in order to accept the
    // Initialisation Action
    //
    /*
      if (MastState[MAST_STATUS_INDEX] != MAST_OPER_MODE_OFF) {
      fprintf(stderr, "In MAST_PAN_Initialise::init() Mast not in MAST_OPER_MODE_OFF mode\n");
      MastState[ABORT_INDEX]       = ACTION_RET_ERROR;
      MastState[ABORT_ERROR_INDEX] = MAST_WRONG_STATE_ERROR;
      // set the actions status
      action_exec_status = ACTION_RET_ERROR;
      getModuleTaskPtr()->GetRobotTaskPtr()->setError(RT_EXEC_WRONG_MODE);
      
      phrMast->stateTransitionError(MastState[MAST_STATUS_INDEX],
      MAST_OPER_MODE_OFF,
      getModuleTaskPtr()->GetRobotTaskPtr()->GetMnemonic().c_str());
      theRobotProcedure->ExitOnInitialStateError();
      
      //  return;
      }
    */
    
    
    MastState[MAST_ACTION_ID_INDEX]   = rtId;
    MastState[MAST_ACTION_RET_INDEX]  = ACTION_RET_INITIALISING;
    MastState[MAST_STATUS_INDEX]      = MAST_OPER_MODE_PTU_INITIALISE;
    if (targetMechanism == TARGET_MECHANISM_PAN) {
      MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_INITIALISE;
    }
    else if (targetMechanism == TARGET_MECHANISM_TILT) {
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_INITIALISE;
    }
    else if (targetMechanism == TARGET_MECHANISM_PAN_TILT) {
      MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_INITIALISE;
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_INITIALISE;
    }

    //
    // reset the resources of the robot task
    //
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
    */

    //
    // set the mast state
    //
    if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE,
						MAX_STATE_SIZE, 0,
						  ( char * ) MastState ) == ERROR ) {
      // theRobotProcedure->
      //	ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //				 "MastState");
    }
    
    //
    // the preconditions are satisfied
    //
    MAST_PAN_Initialise_prec = SET_EVENT;
    //    moduleSendEvent("MAST_PAN_Initialise_prec;");
  }
  
  void orc_Mod_MAST_PAN_Initialise::compute ()
  {
    //   std::cerr << "-> MAST_PAN_Initialise: start compute" << std::endl;
    
    // if the action status is not ok the code is not executed
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_PAN_Initialise::init() action status = error\n");
      //      moduleSendEvent("MAST_PAN_Initialise_exc;");
      return;
    }
    
    //
    // get the Mast state
    //
    if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) MastState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    
    MastState[MAST_STATUS_INDEX]     = MAST_OPER_MODE_PTU_INITIALISE;
    if (targetMechanism == TARGET_MECHANISM_PAN) {
      MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_INITIALISE;
    }
    else if (targetMechanism == TARGET_MECHANISM_TILT) {
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_INITIALISE;
    }
    else if (targetMechanism == TARGET_MECHANISM_PAN_TILT) {
      MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_INITIALISE;
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_INITIALISE;
    }

    MastState[MAST_ACTION_ID_INDEX]  = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    //
    // in the case of timeout on the temperature
    //
    if (index >= (warmUpTimeout/0.2)) {
      
      // set the state
      MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_PTU_STNDBY;
      if (targetMechanism == TARGET_MECHANISM_PAN) {
	MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_STNDBY;
      }
      else if (targetMechanism == TARGET_MECHANISM_TILT) {
	MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_STNDBY;
      }
      else if (targetMechanism == TARGET_MECHANISM_PAN_TILT) {
	MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_STNDBY;
	MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_STNDBY;
      }
      MastState[MAST_ACTION_ID_INDEX]  = 0.0;
      MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
      //
      // send the post-condition
      //
      MAST_PAN_Initialise_post = SET_EVENT;
      //      moduleSendEvent("MAST_PAN_Initialise_post;");
      
      /*
      // the action returns error
      MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_ERROR;
      // the simulation shall be aborted and the error is indicated
      MastState[ABORT_INDEX]       = ACTION_RET_ERROR;
      MastState[ABORT_ERROR_INDEX] = MAST_WARMUP_TIMEOUT_ERROR;
      // set the actions status
      action_exec_status = ACTION_RET_ERROR;
      getModuleTaskPtr()->GetRobotTaskPtr()->setError(RT_EXEC_POST_TIMEOUT);
      moduleSendEvent("MAST_PAN_Initialise_exc;");
      */
    }
    
    //
    // update the resources of the robot task
    //
    /*
    double energy_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
      (MastState[MAST_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0);
    
    double memmass_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
      MastState[MAST_DATARATE_INDEX]*getSampleTime();
    
    double act_duration =
      getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
    
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

    //
    // set the mast state
    //
    if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) MastState ) == ERROR ) {
      //      theRobotProcedure->
      //	ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //				 "MastState");
    }
    
    index++;
    
    
  }

  void orc_Mod_MAST_PAN_Initialise::end ()
  {
    //  fprintf( stderr, "MAST_PAN_Initialise: End\n" );
    // reset the events
    MAST_PAN_Initialise_prec = NO_EVENT;
    MAST_PAN_Initialise_post = NO_EVENT;
    
    
  }
  
}

// End class orc_Mod_MAST_PAN_Initialise

