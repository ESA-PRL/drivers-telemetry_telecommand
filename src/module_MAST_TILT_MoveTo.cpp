#include "module_MAST_TILT_MoveTo.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_MAST_TILT_MoveTo::orc_Mod_MAST_TILT_MoveTo(/*ModuleTask* mt, 
						   // ModuleTask* mt_ade_left, 
						   // ModuleTask* mt_ade_right,
						   int indexclk*/) 
    :    ModuleAlgo(/*"orc_Mod_MAST_TILT_MoveTo", mt, indexclk*/) 
{
    // PRINT1("** orc_Mod_MAST_TILT_MoveTo constructor")
    //    adeManagement.setADELeftModuleTask(mt_ade_left);
    //    adeManagement.setADERightModuleTask(mt_ade_right);
  }
  
  orc_Mod_MAST_TILT_MoveTo::~orc_Mod_MAST_TILT_MoveTo() {
    // PRINT1( "** orc_Mod_MAST_TILT_MoveTo destructor" )
  }
  
  void orc_Mod_MAST_TILT_MoveTo::param(char *params) {
    fprintf( stderr, "MAST_TILT_MoveTo: param\n" );
    //
    // the action status is ok
    //
    action_exec_status = ACTION_RET_OK;
    
    //
    // get the Mast state
    //
    if (theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->
      //	ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //				 "MastState");
    }
    
    //
    // the Action accepts two types of parameterisation; one with six args
    // and a second one with four arguments
    //
    
    finalPose[0] = MastState[MAST_CURRENT_Q1_INDEX];
    finalPose[1] = MastState[MAST_CURRENT_Q2_INDEX];
    
    if (1 != sscanf(params, "%lf", &finalPose[2])) {
      
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      action_exec_status = ACTION_RET_ERROR;
      
      //      theRobotProcedure->
      //	ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //			      params);
      return;
    }
    
    // absolute motion
    motionMode = 0;

    //
    // set the mast state
    //
    if (theRobotProcedure->GetParameters()->set("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->
      //	ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //				 "MastState");
    }
    
  }
  
  void orc_Mod_MAST_TILT_MoveTo::reparam(char *params) {
    
  }

  void orc_Mod_MAST_TILT_MoveTo::init() {
    fprintf( stderr, "MAST_TILT_MoveTo: init\n" );
    // if the action status is not ok (because of bad parameterisation
    // the code is not executed
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_TILT_MoveTo::init() action status = error\n");
      return;
    }
    
    // reset the counter
    index = 0;
    
    // reset the events
    MAST_TILT_MoveTo_prec = NO_EVENT;
    MAST_TILT_MoveTo_post = NO_EVENT;
    
    // reset the power and the mast states
    for (int i = 0; i < MAX_STATE_SIZE; i++) {
      MastState[i] = 0.0;
    }
    
    //
    // reset the resources of the robot task
    //
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
    */    
    // get the action Id
    rtId = 31; // Mt_ptr->GetRobotTaskPtr()->GetId();

    // get the reference to the physical resource
    //    phrMast = ((orc_PhR_Mast *) (Mt_ptr->GetRobotTaskPtr()->GetPhR()));
    
    //
    // get the Mast state
    //
    if (theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //
    // Check that the MAST State is OFF in order to accept the
    // Initialisation Action
    //
    /*
      if (MastState[MAST_STATUS_INDEX] != MAST_OPER_MODE_PTU_STNDBY) {
      fprintf(stderr,
      "In DMA_Initialise::init() Mast not in MAST_OPER_MODE_PTU_STNDBY mode\n");
      
      phrMast->stateTransitionError(MastState[MAST_STATUS_INDEX],
      MAST_OPER_MODE_PTU_STNDBY,
      getModuleTaskPtr()->GetRobotTaskPtr()->GetMnemonic().c_str());
      theRobotProcedure->ExitOnInitialStateError();
      return;
      }
    */
    
    currentTime = 0.0; // sec
    for (int i = 0; i < MAST_DOF; i++) {
      initPose[i] = MastState[MAST_CURRENT_Q1_INDEX + i];
    }
    
    for (int i = 0; i < MAST_DOF; i++) {
      currentPose[i] = initPose[i];
    }
    
    if (motionMode == 0) {
      // finalPose[0] = finalPose[0];
      // finalPose[1] = finalPose[1];
      // finalPose[2] = finalPose[2];
    } 
    else {
      finalPose[0] = initPose[0] + finalPose[0];
      finalPose[1] = initPose[1] + finalPose[1];
      finalPose[2] = initPose[2] + finalPose[2];
    }  
    
    //
    // Compute the duration of the motion with max speed
    //
    
    //
    // Units - meters/sec and deg/sec
    //
    trajDuration = 0.0;
    for (int i = 0; i < MAST_DOF; i++) {
      jointMaxSpeed[i] = 1.0; // phrMast->PARAM_MAST_MAX_ROTATION_SPEED;
    }  
    
    for (int i = 0; i < MAST_DOF; i++) {
      jointTrajDuration[i] = 2 + (fabs(finalPose[i] - initPose[i]))
	/ (jointMaxSpeed[i]);
      
      if (jointTrajDuration[i] > trajDuration) {
	trajDuration = jointTrajDuration[i];
      }
    }
  
    //
    // Publish the final desired position
    //
    for (int i = 0; i < MAST_DOF; i++) {
      MastState[MAST_DES_Q1_INDEX + i] = finalPose[i];
    }
    
    MastState[MAST_TRAJ_DUR_INDEX] = trajDuration;
    
    // set action execution information
    MastState[MAST_ACTION_ID_INDEX]   = rtId;
    MastState[MAST_ACTION_RET_INDEX]  = ACTION_RET_INITIALISING;
    MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_MOVING;

    //
    // set the state
    //
    if (theRobotProcedure->GetParameters()->set("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //
    // Indicate that the preconditions are satisfied
    //
    MAST_TILT_MoveTo_prec = SET_EVENT;
    //    moduleSendEvent("MAST_TILT_MoveTo_prec;");
    
    //    adeManagement.resetFlags();
    
  }
  
  void orc_Mod_MAST_TILT_MoveTo::compute() {
    
    // if the action status is not ok the code is not executed
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_TILT_MoveTo::compute() action status = error\n");
      return;
    }
    /*
    if (adeManagement.ActivateADE() == 1) 
      return;
    
    if (adeManagement.DeactivateADE("MAST_TILT_MoveTo_post;") == 1) 
      return;
    */
    //
    // get the global state
    //
    if (theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    MastState[MAST_ACTION_ID_INDEX] = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
     
    //
    // during the trajectory duration
    //
    if (currentTime <= trajDuration) {
      
      // compute the interpolation polynom
      tFracDur = currentTime / trajDuration;
      rt = 10 * tFracDur * tFracDur * tFracDur
	- 15 * tFracDur * tFracDur * tFracDur * tFracDur
	+ 6 * tFracDur * tFracDur * tFracDur * tFracDur * tFracDur;
      
      // compute the desired joint position (deg)
      for (int i = 0; i < MAST_DOF; i++) {
	currentPose[i] = initPose[i]
	  + (rt) * (finalPose[i] - initPose[i]);
      }
      //			setMastPosition(currentPose);
      
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_MOVING;
    } 
    else {
      // set the current pose at the final pose
      for (int i = 0; i < MAST_DOF; i++) {
	currentPose[i] = finalPose[i];
      }
      
      MastState[MAST_ACTION_ID_INDEX]   = 0.0;
      MastState[MAST_ACTION_RET_INDEX]  = ACTION_RET_OK;
      MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_STNDBY;
      
      MAST_TILT_MoveTo_post = SET_EVENT;
      // moduleSendEvent("MAST_TILT_MoveTo_post;");
      //	  adeManagement.setPhaseADEDeactivate();
    }
    
    currentTime = currentTime + 0.2; // getSampleTime();
    
    //    phrMast->Set(currentPose);

    
    
    //
    // set back to the mast state the computed values
    //
    for (int i = 0; i < MAST_DOF; i++) {
      MastState[MAST_CURRENT_Q1_INDEX + i] = currentPose[i];
      MastState[MAST_DES_Q1_INDEX + i] = finalPose[i];
    }
    
    //
    // update the resources of the robot task
    //
    /*
    double energy_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons()
      + (MastState[MAST_POWER_CONS_INDEX] * getSampleTime() / 60.0
	 / 60.0);
    
    double memmass_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons()
      + MastState[MAST_DATARATE_INDEX] * getSampleTime();
    
    double act_duration = getModuleTaskPtr()->GetRobotTaskPtr()->getDuration()
      + getSampleTime();
    
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

    //
    // update the global state
    //
    if (theRobotProcedure->GetParameters()->set("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
  }
  
  void orc_Mod_MAST_TILT_MoveTo::end() {
    fprintf( stderr, "MAST_TILT_MoveTo: End\n" );
    
    // reset the events
    MAST_TILT_MoveTo_prec = NO_EVENT;
    MAST_TILT_MoveTo_post = NO_EVENT;
    
    //    adeManagement.resetFlags();
    
  }

}

// End class orc_Mod_MAST_TILT_MoveTo

