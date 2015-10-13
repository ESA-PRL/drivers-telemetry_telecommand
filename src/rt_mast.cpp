#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"


extern RobotProcedure*  theRobotProcedure;

/**
 *
 *
 */
void RobotTask::computeMAST_DEP_Initialise(){ 
  std::cerr << rtName << std::endl; 
  rtId = 2;
  double warmUpTimeout = MAST_WARMUP_TIMEOUT;
  if ( theRobotProcedure->GetParameters()->get( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  //  theRobotProcedure->Clock()->GetTime();
  
  MastState[MAST_ACTION_ID_INDEX]  = rtId;
  MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
  MastState[MAST_STATUS_INDEX]     = MAST_OPER_MODE_DEP_INITIALISE;
  
  if (index >= (warmUpTimeout/theRobotProcedure->Clock->GetBasePeriod())) {
    
    // set the state
    MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_DEP_STNDBY;
    MastState[MAST_ACTION_ID_INDEX]  = 0.0;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;

    post_cond = 1;
  }

  index++;
  
  if ( theRobotProcedure->GetParameters()->set( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}


/**
 *
 *
 */
void RobotTask::computeMAST_DEP_Deploy(){ 
  
  std::cerr << rtName << std::endl; 
  
  rtId = 2;
  
  if ( theRobotProcedure->GetParameters()->get( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    finalMASTPose[0] = 0.0;
    finalMASTPose[1] = MastState[MAST_CURRENT_Q2_INDEX];
    finalMASTPose[2] = MastState[MAST_CURRENT_Q3_INDEX];
    param_completed = 1;
  }

  //
  // Initialise
  //
  if (init_completed == 0) {
    mastCurrentTime = 0.0; // sec
    for (int i = 0; i<MAST_DOF; i++) {
      initMASTPose[i] = MastState[MAST_CURRENT_Q1_INDEX + i];
    }
    for (int i = 0; i<MAST_DOF; i++) {
      mastCurrentPose[i] = initMASTPose[i];
    }
    for (int i = 0; i<MAST_DOF; i++) {
      finalMASTPose[i] = mastCurrentPose[i];
    }
    finalMASTPose[0] = 90.0;
    mastTrajDuration = 0.0;
    for (int i=0; i<MAST_DOF; i++) {
      jointMASTMaxSpeed[i] = MAST_MAX_ROTATION_SPEED;
    }
    for (int i = 0; i<MAST_DOF; i++) {
      jointMASTTrajDuration[i] = (fabs (finalMASTPose[i] - initMASTPose[i]) ) / (jointMASTMaxSpeed[i]);

      if (jointMASTTrajDuration[i] > mastTrajDuration) {
	mastTrajDuration = jointMASTTrajDuration[i];
      }
    }
    for (int i = 0; i<MAST_DOF; i++) {
      MastState[MAST_DES_Q1_INDEX+i] = finalMASTPose[i];
    }
    MastState[MAST_TRAJ_DUR_INDEX]    = mastTrajDuration;
    MastState[MAST_STATUS_INDEX]      = MAST_OPER_MODE_DEP_MOVING;
    MastState[MAST_ACTION_ID_INDEX]  = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    mastCurrentTime = 0.0;

    init_completed = 1;
  }

  //
  // Compute
  //
  if (compute_completed == 0){

	MastState[MAST_ACTION_ID_INDEX]  = rtId;
	MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	if (mastCurrentTime <= mastTrajDuration) {
	  // compute the interpolation polynom
	  tFracDur = mastCurrentTime/mastTrajDuration;
	  rt = 10*tFracDur*tFracDur*tFracDur -
	    15*tFracDur*tFracDur*tFracDur*tFracDur +
	    6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
	  for (int i = 0; i<MAST_DOF; i++) {
	    mastCurrentPose[i] = initMASTPose[i] + (rt) * (finalMASTPose[i] - initMASTPose[i]);
	  }
	  MastState[MAST_STATUS_INDEX]              = MAST_OPER_MODE_DEP_MOVING;
	}
	else {
	  MastState[MAST_ACTION_ID_INDEX]  = 0;
	  MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
	  post_cond = 1;
	  MastState[MAST_STATUS_INDEX]     = MAST_OPER_MODE_DEP_STNDBY;

	  compute_completed = 1;
	}

	MastState[MAST_CURRENT_Q1_INDEX] = mastCurrentPose[0];
	MastState[MAST_CURRENT_Q2_INDEX] = mastCurrentPose[1];
	MastState[MAST_CURRENT_Q3_INDEX] = mastCurrentPose[2];
	MastState[MAST_CURRENT_Q4_INDEX] = mastCurrentPose[3];

	MastState[MAST_DES_Q1_INDEX] = finalMASTPose[0];
	MastState[MAST_DES_Q2_INDEX] = finalMASTPose[1];
	MastState[MAST_DES_Q3_INDEX] = finalMASTPose[2];
	MastState[MAST_DES_Q4_INDEX] = finalMASTPose[3];

	mastCurrentTime = mastCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }

  //
  // End
  //
  if (end_completed == 0) {

  }

  
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeMAST_PTU_Initialise(){ 
  
  std::cerr << rtName << std::endl; 
  
  rtId = 813;
  
  if ( theRobotProcedure->GetParameters()->get( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }


  
  if ( theRobotProcedure->GetParameters()->set( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
/**
 *
 */
void RobotTask::computeMAST_PTU_MoveTo(){ 
  
  std::cerr << rtName << std::endl; 
  
  rtId = 813;
  
  if ( theRobotProcedure->GetParameters()->get( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  //
  // Parameterise
  //
  if (param_completed == 0){
    
    finalMASTPose[0] = MastState[MAST_CURRENT_Q1_INDEX];

    if (3 != sscanf(rtParams, "%d %lf %lf", &tcRequestId, &finalMASTPose[1], &finalMASTPose[2])) {
      post_cond = 1;
      param_completed = 1;
      return;
    }
  }
  
  // Initialise
  if (init_completed == 0) {
    
    mastCurrentTime = 0.0; // sec
    for (int i = 0; i < MAST_DOF; i++) {
      initMASTPose[i] = MastState[MAST_CURRENT_Q1_INDEX + i];
    }
    
    for (int i = 0; i < MAST_DOF; i++) {
      mastCurrentPose[i] = initMASTPose[i];
    }
    
    finalMASTPose[0] = initMASTPose[0] + finalMASTPose[0];
    finalMASTPose[1] = initMASTPose[1] + finalMASTPose[1];
    finalMASTPose[2] = initMASTPose[2] + finalMASTPose[2];
    
    mastTrajDuration = 0.0;
    for (int i = 0; i < MAST_DOF; i++) {
      jointMASTMaxSpeed[i] = MAST_MAX_ROTATION_SPEED;
    }

    mastTrajDuration = 1.0; // minimum duration
    for (int i = 0; i < MAST_DOF; i++) {
      jointMASTTrajDuration[i] = (fabs(finalMASTPose[i] - initMASTPose[i]))
	/ (jointMASTMaxSpeed[i]);
      if (jointMASTTrajDuration[i] > mastTrajDuration) {
	mastTrajDuration = jointMASTTrajDuration[i];
      }
    }
    for (int i = 0; i < MAST_DOF; i++) {
      MastState[MAST_DES_Q1_INDEX + i] = finalMASTPose[i];
    }
    
    MastState[MAST_TRAJ_DUR_INDEX] = mastTrajDuration;
    
    // set action execution information
    MastState[MAST_ACTION_ID_INDEX] = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_PTU_MOVING;
    
    init_completed = 1;
  }
  
  //
  // Compute
  //
  if (compute_completed == 0){
    
    if (mastCurrentTime <= mastTrajDuration) {
      tFracDur = mastCurrentTime / mastTrajDuration;
      rt = 10 * tFracDur * tFracDur * tFracDur
	- 15 * tFracDur * tFracDur * tFracDur * tFracDur
	+ 6 * tFracDur * tFracDur * tFracDur * tFracDur * tFracDur;
      
      // compute the desired joint position (deg)
      for (int i = 0; i < MAST_DOF; i++) {
	mastCurrentPose[i] = initMASTPose[i]
	  + (rt) * (finalMASTPose[i] - initMASTPose[i]);
      }
      
      for (int i = 0; i < MAST_DOF; i++) {
	MastState[MAST_CURRENT_Q1_INDEX + i] = mastCurrentPose[i];
	std::cerr << "mastCurrentPose[:" << i << "]:" << mastCurrentPose[i] << std::endl;
      }
      MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_PTU_MOVING;
    } 
    else {
      
      for (int i = 0; i < MAST_DOF; i++) {
	MastState[MAST_CURRENT_Q1_INDEX + i] = finalMASTPose[i];
      }
      
      MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_PTU_STNDBY;
      
      MastState[MAST_ACTION_ID_INDEX] = 0.0;
      MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      post_cond = 1;
      compute_completed = 1;
    }	
    
    mastCurrentTime = mastCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }
  
  //
  // End
  //
  if (end_completed == 0) {
    
  }
  
  if ( theRobotProcedure->GetParameters()->set( "MastState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}


void RobotTask::computeMAST_SwitchOff(){ 

  std::cerr << rtName << std::endl; 

  rtId = 2;

  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  double duration = 5.0; // sec
  
  MastState[MAST_ACTION_ID_INDEX]  = rtId;
  MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  
  if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
    MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_OFF;
    MastState[MAST_ACTION_ID_INDEX]  = rtId;
    MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
    
    post_cond = 1;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
