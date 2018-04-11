#include "module_MAST_PTU_MoveTo.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  
  orc_Mod_MAST_PTU_MoveTo::orc_Mod_MAST_PTU_MoveTo(/*ModuleTask* mt, 
						     int indexclk*/) 
  //:    ModuleAlgo("orc_Mod_MAST_PTU_MoveTo", mt, indexclk) 
{
  }
  
  orc_Mod_MAST_PTU_MoveTo::~orc_Mod_MAST_PTU_MoveTo() {

  }
  
  void orc_Mod_MAST_PTU_MoveTo::param(char *params) {
    // std::cerr << "-> MAST_PTU_MoveTo: start param 1:" << std::endl;
    //
    // the action status is ok
    //
    action_exec_status = ACTION_RET_OK;
    
    //
    // get the Mast state
    //
    if (theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //  theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //
    // the Action accepts two types of parameterisation; one with six args
    // and a second one with four arguments
    //
    
    finalPose[0] = MastState[MAST_CURRENT_Q1_INDEX];
    
    strcpy(target, "ptu");
    motionMode = 0;
    coordinatedMotion = 1;
    
    if (2 != sscanf(params, "%lf %lf", &finalPose[1], &finalPose[2])) {
      
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      action_exec_status = ACTION_RET_ERROR;
      
      // theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
      return;
      
    }
    
    //
    // show in the standard output the parameters
    //
    /*
      fprintf(stderr, "In Mast_MoveTo::param() %s %d %d %lf %lf  %lf\n",
      target, motionMode, coordinatedMotion,
      finalPose[0], finalPose[1], finalPose[2]);
    */
    //
    // check if the parameters are correctly defined
    //
    if (strcmp(target, "mast") != 0 && strcmp(target, "ptu") != 0) {
      fprintf(stderr, "In MAST_PTU_MoveTo param failed - unknown target mode\n");
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      action_exec_status = ACTION_RET_ERROR;
      //      theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    }
    if (motionMode != 0 && motionMode != 1) {
      fprintf(stderr, "In MAST_PTU_MoveTo param failed - wrong motion mode\n");
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      action_exec_status = ACTION_RET_ERROR;
      //      theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    }
    if (coordinatedMotion != 0 && coordinatedMotion != 1) {
      fprintf(stderr,
	      "In MAST_PTU_MoveTo param failed - wrong coordinated motion mode\n");
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      action_exec_status = ACTION_RET_ERROR;
      //      theRobotProcedure->ExitOnParamValueError(
      //					       Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    }
    
    //
    // set the mast state
    //
    if (theRobotProcedure->GetParameters()->set("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //	setMastPosition(finalPose);
  }
  
  void orc_Mod_MAST_PTU_MoveTo::reparam(char *params) {
    
  }

  void orc_Mod_MAST_PTU_MoveTo::init() {
    //    std::cerr << "-> MAST_PTU_MoveTo: start init:" << currentTime << " " << trajDuration << std::endl;
    // if the action status is not ok (because of bad parameterisation
    // the code is not executed
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_PTU_MoveTo::init() action status = error\n");
      return;
    }
    
    // reset the counter
    index = 0;
    
    // reset the events
    MAST_PTU_MoveTo_prec = NO_EVENT;
    MAST_PTU_MoveTo_post = NO_EVENT;
    
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
    
    // get the action Id
    rtId = Mt_ptr->GetRobotTaskPtr()->GetId();
    */
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
    
    //
    // set the local variables
    //
    currentMovingJoint = 0;
    
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
    
    // MastState[MAST_TRAJ_DUR_INDEX] = trajDuration;
    
    // set action execution information
    MastState[MAST_ACTION_ID_INDEX] = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    if ( MastState[MAST_PAN_STATUS_INDEX] == MAST_OPER_MODE_PAN_OFF) {
      current_pan_mode = MAST_OPER_MODE_PAN_OFF;
    }
    else if (MastState[MAST_PAN_STATUS_INDEX] == MAST_OPER_MODE_PAN_STNDBY) {
      current_pan_mode = MAST_OPER_MODE_PAN_STNDBY;
    }
    if ( MastState[MAST_TILT_STATUS_INDEX] == MAST_OPER_MODE_TILT_OFF) {
      current_tilt_mode = MAST_OPER_MODE_TILT_OFF;
    }
    else if (MastState[MAST_TILT_STATUS_INDEX] == MAST_OPER_MODE_TILT_STNDBY) {
      current_tilt_mode = MAST_OPER_MODE_TILT_STNDBY;
    }

    //
    // set the state
    //
    if (theRobotProcedure->GetParameters()->set("MastState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) MastState) == ERROR) {
      // theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "MastState");
    }
    
    //
    // Indicate that the preconditions are satisfied
    //
    MAST_PTU_MoveTo_prec = SET_EVENT;
    //    moduleSendEvent("MAST_PTU_MoveTo_prec;");
    
  }
  
  void orc_Mod_MAST_PTU_MoveTo::compute() {
        //    std::cerr << "-> MAST_PTU_MoveTo: start compute:" << currentTime << " " << trajDuration << std::endl;

    // if the action status is not ok the code is not executed
    if (action_exec_status != ACTION_RET_OK) {
      fprintf(stderr, "In MAST_PTU_MoveTo::compute() action status = error\n");
      return;
    }
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
     
    if (coordinatedMotion == 1) {
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
	
	MastState[MAST_PAN_STATUS_INDEX] = MAST_OPER_MODE_PAN_MOVING;
	MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_MOVING;
      } 
      else {
	// set the current pose at the final pose
	for (int i = 0; i < MAST_DOF; i++) {
	  currentPose[i] = finalPose[i];
	}
	
	MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_STNDBY;
	MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_STNDBY;
	
	MastState[MAST_ACTION_ID_INDEX]  = 0.0;
	MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
	
	MAST_PTU_MoveTo_post = SET_EVENT;
	// moduleSendEvent("MAST_PTU_MoveTo_post;");
	
      }
    }
    
    else {
      if (currentTime <= (jointTrajDuration[currentMovingJoint])) {
	// compute the interpolation polynom
	if (jointTrajDuration[currentMovingJoint] > 0) {
	  tFracDur = currentTime / jointTrajDuration[currentMovingJoint];
	  rt = 10 * tFracDur * tFracDur * tFracDur
	    - 15 * tFracDur * tFracDur * tFracDur * tFracDur
	    + 6 * tFracDur * tFracDur * tFracDur * tFracDur * tFracDur;
	  
	  //rt = tFracDur;
	  
	  // compute the desired joint position (deg)
	  
	  currentPose[currentMovingJoint] = 
	    initPose[currentMovingJoint] + (rt) * (finalPose[currentMovingJoint] - initPose[currentMovingJoint]);
	}
	if (currentMovingJoint == 1) {
	  MastState[MAST_PAN_STATUS_INDEX] = MAST_OPER_MODE_PAN_MOVING;
	  MastState[MAST_TILT_STATUS_INDEX] = current_tilt_mode;
	}
	else if (currentMovingJoint == 2) {
	  MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_MOVING;
	  MastState[MAST_PAN_STATUS_INDEX] = current_pan_mode;
	}
	
      } 
      else {

	if (currentMovingJoint == MAST_DOF - 1) {
	  //
	  // indicate that the postcondition is satisfied
	  //
	  MAST_PTU_MoveTo_post = SET_EVENT;
	  // moduleSendEvent("MAST_PTU_MoveTo_post;");
	  //	  adeManagement.setPhaseADEDeactivate();
	  // set the current pose at the final pose
	  for (int i = 0; i < MAST_DOF; i++) {
	    currentPose[i] = finalPose[i];
	  }
	  	   
	  if ( current_pan_mode == MAST_OPER_MODE_PAN_OFF) {
	    MastState[MAST_PAN_STATUS_INDEX] = MAST_OPER_MODE_PAN_OFF;
	  }
	  else {
	    MastState[MAST_PAN_STATUS_INDEX] = MAST_OPER_MODE_PAN_STNDBY;
	  }
	  if ( current_pan_mode == MAST_OPER_MODE_TILT_OFF) {
	    MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_OFF;
	  }
	  else {
	    MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_STNDBY;
	  };
	  
	  MastState[MAST_ACTION_ID_INDEX]  = 0.0;
	  MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
	  
	  MAST_PTU_MoveTo_prec = SET_EVENT;
	  // moduleSendEvent("MAST_PTU_MoveTo_prec;");
	} 
	else {
	  
	  currentMovingJoint++;
	  currentTime = currentTime + 0.2; //getSampleTime();
	  
	}
	//currentTime = 0.0;
      }
      
    }
    
    currentTime = currentTime + 0.2; //getSampleTime();
    
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
    /*
    printf("%lf %lf %lf %d\n",
	   MastState[MAST_CURRENT_Q1_INDEX],
	   MastState[MAST_CURRENT_Q2_INDEX],
	   MastState[MAST_CURRENT_Q3_INDEX], 
	   currentMovingJoint);
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
  
  void orc_Mod_MAST_PTU_MoveTo::end() {
    //  fprintf( stderr, "MAST_PTU_MoveTo: End\n" );
    
    // reset the events
    MAST_PTU_MoveTo_prec = NO_EVENT;
    MAST_PTU_MoveTo_post = NO_EVENT;
    
    //    adeManagement.resetFlags();
    
  }

}

// End class orc_Mod_MAST_PTU_MoveTo

