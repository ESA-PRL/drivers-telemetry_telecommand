#include "rt.h"
#include "param.h"
#include "prr.h"


extern RobotProcedure*  theRobotProcedure;

int RobotTask::computeDeploy_LEFT_SA()
{
    std::cerr << rtName << std::endl;

    switch (deploy_left_sa_seq)
    {
        case 0:
            std::cerr << "SA LEFT: gnc monitoring" << std::endl;
            if(computeGNC_MonitoringOnly() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 1:
            std::cerr << "SA LEFT: release hdrm" << std::endl;
            if(computeADE_LEFT_ReleaseHDRM() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 2:
            std::cerr << "SA LEFT: initialise" << std::endl;
            if(computeSA_LEFT_Initialise() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 3:
            std::cerr << "SA LEFT: primary move to" << std::endl;
            if(computeSA_LEFT_PrimaryMoveTo() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 4:
            std::cerr << "SA LEFT: secondary move to" << std::endl;
            if(computeSA_LEFT_SecondaryMoveTo() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 5:
            std::cerr << "SA LEFT: switch off" << std::endl;
            if(computeSA_LEFT_SwitchOff() == 1)
            {
                post_cond = 0;
                deploy_left_sa_seq++;
            }
            break;
        case 6:
            std::cerr << "SA LEFT: gnc switch off" << std::endl;
            if(computeGNC_SwitchOff() == 1)
            {
                post_cond = 1;
                deploy_left_sa_seq = 0;
            }
            break;
        default:
            break;
    }
    return post_cond;
}

int RobotTask::computeDeploy_RIGHT_SA()
{
    std::cerr << rtName << std::endl;

    switch (deploy_right_sa_seq)
    {
        case 0:
            std::cerr << "SA RIGHT: gnc monitoring" << std::endl;
            if(computeGNC_MonitoringOnly() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 1:
            std::cerr << "SA RIGHT: release hdrm" << std::endl;
            if(computeADE_RIGHT_ReleaseHDRM() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 2:
            std::cerr << "SA RIGHT: initialise" << std::endl;
            if(computeSA_RIGHT_Initialise() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 3:
            std::cerr << "SA RIGHT: primary move to" << std::endl;
            if(computeSA_RIGHT_PrimaryMoveTo() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 4:
            std::cerr << "SA RIGHT: secondary move to" << std::endl;
            if(computeSA_RIGHT_SecondaryMoveTo() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 5:
            std::cerr << "SA RIGHT: switch off" << std::endl;
            if(computeSA_RIGHT_SwitchOff() == 1)
            {
                post_cond = 0;
                deploy_right_sa_seq++;
            }
            break;
        case 6:
            std::cerr << "SA RIGHT: gnc switch off" << std::endl;
            if(computeGNC_SwitchOff() == 1)
            {
                post_cond = 1;
                deploy_right_sa_seq = 0;
            }
            break;
        default:
            break;
    }
    return post_cond;
}

/**
 *
 */
int RobotTask::computeSA_LEFT_Initialise(){
  std::cerr << rtName << std::endl; 
  
  rtId = 800;
  double switchOnTime = 2.0; // sec

  if ( theRobotProcedure->GetParameters()->get( "SAState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  // Set Action ID and Ret val
  SAState[SA_ACTION_ID_INDEX]  = 801;
  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  
  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_INITIALISING;
  SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_INITIALISING;
  SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_INITIALISING;
  SAState[SA_ACTION_ID_INDEX]           = rtId;
  SAState[SA_ACTION_RET_INDEX]          = ACTION_RET_RUNNING;
  
  if (index >= (switchOnTime/(theRobotProcedure->Clock->GetBasePeriod()))) {
    SAState[SA_STATUS_INDEX]     = SA_OPER_MODE_STNDBY;
    SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;
    SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;
    SAState[SA_ACTION_ID_INDEX]  = 0;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
    post_cond = 1;
  }
  
  index++;

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}


/**
 *
 */
int RobotTask::computeSA_LEFT_PrimaryMoveTo(){
  std::cerr << rtName << std::endl; 

  rtId = 812;

  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  //
  // Parameterise
  //
  if (param_completed == 0){
    if (2 != sscanf(rtParams, "%d %lf", &tcRequestId, &tilt)) {
      post_cond = 1;
      return post_cond;
    }
    param_completed = 1;
  }

  //
  // Initialise
  //
  if (init_completed == 0) {
    saCurrentTime = 0.0; // sec
    for (int i = 0; i<SA_DOF; i++) {
      initSAPose[i] = SAState[SA_CURRENT_Q1_INDEX + i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      saCurrentPose[i] = initSAPose[i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      finalSAPose[i] = saCurrentPose[i];
    }
    finalSAPose[0] = tilt;
    saTrajDuration = 0.0;
    for (int i=0; i<SA_DOF; i++) {
      jointSAMaxSpeed[i] = SA_MAX_ROTATION_SPEED;
    }
    for (int i = 0; i<SA_DOF; i++) {
      jointSATrajDuration[i] = (fabs (finalSAPose[i] - initSAPose[i]) ) / (jointSAMaxSpeed[i]);

      if (jointSATrajDuration[i] > saTrajDuration) {
	saTrajDuration = jointSATrajDuration[i];
      }
    }
    for (int i = 0; i<SA_DOF; i++) {
      SAState[SA_DES_Q1_INDEX+i] = finalSAPose[i];
    }
    SAState[SA_TRAJ_DUR_INDEX]    = saTrajDuration;
    SAState[SA_STATUS_INDEX]      = SA_OPER_MODE_MOVING;
    SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
    SAState[SA_ACTION_ID_INDEX]  = rtId;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    saCurrentTime = 0.0;

    init_completed = 1;
  }

  //
  // Compute
  //
  if (compute_completed == 0){

	SAState[SA_ACTION_ID_INDEX]  = rtId;
	SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	if (saCurrentTime <= saTrajDuration) {
	  // compute the interpolation polynom
	  tFracDur = saCurrentTime/saTrajDuration;
	  rt = 10*tFracDur*tFracDur*tFracDur -
	    15*tFracDur*tFracDur*tFracDur*tFracDur +
	    6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
	  for (int i = 0; i<SA_DOF; i++) {
	    saCurrentPose[i] = initSAPose[i] + (rt) * (finalSAPose[i] - initSAPose[i]);
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_MOVING;
	  SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
	}
	else {
	  SAState[SA_ACTION_ID_INDEX]  = 0;
	  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
	  post_cond = 1;
	  for (int i=0; i<SA_DOF; i++) {
	    saCurrentPose[i] = finalSAPose[i];
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_STNDBY;
	  SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;

	  compute_completed = 1;
	}

	SAState[SA_CURRENT_Q1_INDEX] = saCurrentPose[0];
	SAState[SA_CURRENT_Q2_INDEX] = saCurrentPose[1];
	SAState[SA_CURRENT_Q3_INDEX] = saCurrentPose[2];
	SAState[SA_CURRENT_Q4_INDEX] = saCurrentPose[3];

	SAState[SA_DES_Q1_INDEX] = finalSAPose[0];
	SAState[SA_DES_Q2_INDEX] = finalSAPose[1];
	SAState[SA_DES_Q3_INDEX] = finalSAPose[2];
	SAState[SA_DES_Q4_INDEX] = finalSAPose[3];

	saCurrentTime = saCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }

  //
  // End
  //
  if (end_completed == 0) {

  }



  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

int RobotTask::computeSA_LEFT_SecondaryMoveTo(){
  std::cerr << rtName << std::endl; 

  rtId = 813;

  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  //
  // Parameterise
  //
  if (param_completed == 0){
    if (2 != sscanf(rtParams, "%d %lf", &tcRequestId, &tilt)) {
      post_cond = 1;
      return post_cond;
    }
    param_completed = 1;
  }

  //
  // Initialise
  //
  if (init_completed == 0) {
    saCurrentTime = 0.0; // sec
    for (int i = 0; i<SA_DOF; i++) {
      initSAPose[i] = SAState[SA_CURRENT_Q1_INDEX + i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      saCurrentPose[i] = initSAPose[i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      finalSAPose[i] = saCurrentPose[i];
    }
    finalSAPose[1] = tilt;
    saTrajDuration = 0.0;
    for (int i=0; i<SA_DOF; i++) {
      jointSAMaxSpeed[i] = SA_MAX_ROTATION_SPEED;
    }
    for (int i = 0; i<SA_DOF; i++) {
      jointSATrajDuration[i] = (fabs (finalSAPose[i] - initSAPose[i]) ) / (jointSAMaxSpeed[i]);

      if (jointSATrajDuration[i] > saTrajDuration) {
	saTrajDuration = jointSATrajDuration[i];
      }
    }
    for (int i = 0; i<SA_DOF; i++) {
      SAState[SA_DES_Q1_INDEX+i] = finalSAPose[i];
    }
    SAState[SA_TRAJ_DUR_INDEX]    = saTrajDuration;
    SAState[SA_STATUS_INDEX]      = SA_OPER_MODE_MOVING;
    SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
    SAState[SA_ACTION_ID_INDEX]  = rtId;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    saCurrentTime = 0.0;

    init_completed = 1;
  }

  //
  // Compute
  //
  if (compute_completed == 0){

	SAState[SA_ACTION_ID_INDEX]  = rtId;
	SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	if (saCurrentTime <= saTrajDuration) {
	  // compute the interpolation polynom
	  tFracDur = saCurrentTime/saTrajDuration;
	  rt = 10*tFracDur*tFracDur*tFracDur -
	    15*tFracDur*tFracDur*tFracDur*tFracDur +
	    6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
	  for (int i = 0; i<SA_DOF; i++) {
	    saCurrentPose[i] = initSAPose[i] + (rt) * (finalSAPose[i] - initSAPose[i]);
	    //std::cerr << saCurrentPose[i] << " " << initSAPose[i] << " " << finalSAPose[i] << std::endl;
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_MOVING;
	  SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
	}
	else {
	  SAState[SA_ACTION_ID_INDEX]  = 0;
	  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
	  post_cond = 1;
	  for (int i=0; i<SA_DOF; i++) {
	    saCurrentPose[i] = finalSAPose[i];
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_STNDBY;
	  SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;

	  compute_completed = 1;
	}

	SAState[SA_CURRENT_Q1_INDEX] = saCurrentPose[0];
	SAState[SA_CURRENT_Q2_INDEX] = saCurrentPose[1];
	SAState[SA_CURRENT_Q3_INDEX] = saCurrentPose[2];
	SAState[SA_CURRENT_Q4_INDEX] = saCurrentPose[3];

	SAState[SA_DES_Q1_INDEX] = finalSAPose[0];
	SAState[SA_DES_Q2_INDEX] = finalSAPose[1];
	SAState[SA_DES_Q3_INDEX] = finalSAPose[2];
	SAState[SA_DES_Q4_INDEX] = finalSAPose[3];

	saCurrentTime = saCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }

  //
  // End
  //
  if (end_completed == 0) {

  }

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

/**
 *
 */
int RobotTask::computeSA_LEFT_SwitchOff(){
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  rtId = 820;

  // Set Action ID and Ret val
  SAState[SA_ACTION_ID_INDEX]  = rtId;
  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

  if (index >= 10) {
    // Set Action ID and Ret val
    SAState[SA_ACTION_ID_INDEX]  = 0;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;

    SAState[SA_STATUS_INDEX] = SA_OPER_MODE_OFF;
    SAState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_OFF;
    SAState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_OFF;

    post_cond = 1;
    index = 0;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

/**
 *
 */
int RobotTask::computeSA_RIGHT_Initialise(){
  std::cerr << rtName << std::endl;

  rtId = 800;
  double switchOnTime = 2.0; // sec

  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  // Set Action ID and Ret val
  SAState[SA_ACTION_ID_INDEX]  = 801;
  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

  SAState[SA_STATUS_INDEX]               = SA_OPER_MODE_INITIALISING;
  SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_INITIALISING;
  SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_INITIALISING;
  SAState[SA_ACTION_ID_INDEX]            = rtId;
  SAState[SA_ACTION_RET_INDEX]           = ACTION_RET_RUNNING;

  if (index >= (switchOnTime/(theRobotProcedure->Clock->GetBasePeriod()))) {
    SAState[SA_STATUS_INDEX]     = SA_OPER_MODE_STNDBY;
    SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;
    SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;
    SAState[SA_ACTION_ID_INDEX]  = 0;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
    post_cond = 1;
    index = 0;
  }

  index++;
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

/**
 *
 */
int RobotTask::computeSA_RIGHT_PrimaryMoveTo(){ 
  std::cerr << rtName << std::endl; 
  
  rtId = 815;

  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  //
  // Parameterise
  //
  if (param_completed == 0){
    if (2 != sscanf(rtParams, "%d %lf", &tcRequestId, &tilt)) {
      post_cond = 1;
      return post_cond;
    }
    param_completed = 1;
  }

  //
  // Initialise
  //
  if (init_completed == 0) {
    saCurrentTime = 0.0; // sec
    for (int i = 0; i<SA_DOF; i++) {
      initSAPose[i] = SAState[SA_CURRENT_Q1_INDEX + i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      saCurrentPose[i] = initSAPose[i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      finalSAPose[i] = saCurrentPose[i];
    }
    finalSAPose[2] = tilt;
    saTrajDuration = 0.0;
    for (int i=0; i<SA_DOF; i++) {
      jointSAMaxSpeed[i] = SA_MAX_ROTATION_SPEED;
    }
    for (int i = 0; i<SA_DOF; i++) {
      jointSATrajDuration[i] = (fabs (finalSAPose[i] - initSAPose[i]) ) / (jointSAMaxSpeed[i]);

      if (jointSATrajDuration[i] > saTrajDuration) {
	saTrajDuration = jointSATrajDuration[i];
      }
    }
    for (int i = 0; i<SA_DOF; i++) {
      SAState[SA_DES_Q1_INDEX+i] = finalSAPose[i];
    }
    SAState[SA_TRAJ_DUR_INDEX]    = saTrajDuration;
    SAState[SA_STATUS_INDEX]      = SA_OPER_MODE_MOVING;
    SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
    SAState[SA_ACTION_ID_INDEX]  = rtId;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    saCurrentTime = 0.0;

    init_completed = 1;
  }

  //
  // Compute
  //
  if (compute_completed == 0){

	SAState[SA_ACTION_ID_INDEX]  = rtId;
	SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	if (saCurrentTime <= saTrajDuration) {
	  // compute the interpolation polynom
	  tFracDur = saCurrentTime/saTrajDuration;
	  rt = 10*tFracDur*tFracDur*tFracDur -
	    15*tFracDur*tFracDur*tFracDur*tFracDur +
	    6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
	  for (int i = 0; i<SA_DOF; i++) {
	    saCurrentPose[i] = initSAPose[i] + (rt) * (finalSAPose[i] - initSAPose[i]);
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_MOVING;
	  SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
	}
	else {
	  SAState[SA_ACTION_ID_INDEX]  = 0;
	  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
	  post_cond = 1;
	  for (int i=0; i<SA_DOF; i++) {
	    saCurrentPose[i] = finalSAPose[i];
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_STNDBY;
	  SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;

	  compute_completed = 1;
	}

	SAState[SA_CURRENT_Q1_INDEX] = saCurrentPose[0];
	SAState[SA_CURRENT_Q2_INDEX] = saCurrentPose[1];
	SAState[SA_CURRENT_Q3_INDEX] = saCurrentPose[2];
	SAState[SA_CURRENT_Q4_INDEX] = saCurrentPose[3];

	SAState[SA_DES_Q1_INDEX] = finalSAPose[0];
	SAState[SA_DES_Q2_INDEX] = finalSAPose[1];
	SAState[SA_DES_Q3_INDEX] = finalSAPose[2];
	SAState[SA_DES_Q4_INDEX] = finalSAPose[3];

	saCurrentTime = saCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }

  //
  // End
  //
  if (end_completed == 0) {

  }

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

/**
 *
 */
int RobotTask::computeSA_RIGHT_SecondaryMoveTo(){ 
  std::cerr << rtName << std::endl; 

  rtId = 817;

  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }


  //
  // Parameterise
  //
  if (param_completed == 0){
    if (2 != sscanf(rtParams, "%d %lf", &tcRequestId, &tilt)) {
      post_cond = 1;
      return post_cond;
    }
    param_completed = 1;
  }

  //
  // Initialise
  //
  if (init_completed == 0) {
    saCurrentTime = 0.0; // sec
    for (int i = 0; i<SA_DOF; i++) {
      initSAPose[i] = SAState[SA_CURRENT_Q1_INDEX + i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      saCurrentPose[i] = initSAPose[i];
    }
    for (int i = 0; i<SA_DOF; i++) {
      finalSAPose[i] = saCurrentPose[i];
    }
    finalSAPose[3] = tilt;
    saTrajDuration = 0.0;
    for (int i=0; i<SA_DOF; i++) {
      jointSAMaxSpeed[i] = SA_MAX_ROTATION_SPEED;
    }
    for (int i = 0; i<SA_DOF; i++) {
      jointSATrajDuration[i] = (fabs (finalSAPose[i] - initSAPose[i]) ) / (jointSAMaxSpeed[i]);

      if (jointSATrajDuration[i] > saTrajDuration) {
	saTrajDuration = jointSATrajDuration[i];
      }
    }
    for (int i = 0; i<SA_DOF; i++) {
      SAState[SA_DES_Q1_INDEX+i] = finalSAPose[i];
    }
    SAState[SA_TRAJ_DUR_INDEX]    = saTrajDuration;
    SAState[SA_STATUS_INDEX]      = SA_OPER_MODE_MOVING;
    SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
    SAState[SA_ACTION_ID_INDEX]  = rtId;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

    saCurrentTime = 0.0;

    init_completed = 1;
  }

  //
  // Compute
  //
  if (compute_completed == 0){

	SAState[SA_ACTION_ID_INDEX]  = rtId;
	SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	if (saCurrentTime <= saTrajDuration) {
	  // compute the interpolation polynom
	  tFracDur = saCurrentTime/saTrajDuration;
	  rt = 10*tFracDur*tFracDur*tFracDur -
	    15*tFracDur*tFracDur*tFracDur*tFracDur +
	    6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
	  for (int i = 0; i<SA_DOF; i++) {
	    saCurrentPose[i] = initSAPose[i] + (rt) * (finalSAPose[i] - initSAPose[i]);
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_MOVING;
	  SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
	}
	else {
	  SAState[SA_ACTION_ID_INDEX]  = 0;
	  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
	  post_cond = 1;
	  for (int i=0; i<SA_DOF; i++) {
	    saCurrentPose[i] = finalSAPose[i];
	  }
	  SAState[SA_STATUS_INDEX]              = SA_OPER_MODE_STNDBY;
	  SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;

	  compute_completed = 1;
	}

	SAState[SA_CURRENT_Q1_INDEX] = saCurrentPose[0];
	SAState[SA_CURRENT_Q2_INDEX] = saCurrentPose[1];
	SAState[SA_CURRENT_Q3_INDEX] = saCurrentPose[2];
	SAState[SA_CURRENT_Q4_INDEX] = saCurrentPose[3];

	SAState[SA_DES_Q1_INDEX] = finalSAPose[0];
	SAState[SA_DES_Q2_INDEX] = finalSAPose[1];
	SAState[SA_DES_Q3_INDEX] = finalSAPose[2];
	SAState[SA_DES_Q4_INDEX] = finalSAPose[3];

	saCurrentTime = saCurrentTime + theRobotProcedure->Clock->GetBasePeriod();
  }

  //
  // End
  //
  if (end_completed == 0) {

  }

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  return post_cond;
}

int RobotTask::computeSA_RIGHT_SwitchOff(){ 
std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  rtId = 820;
  
  // Set Action ID and Ret val
  SAState[SA_ACTION_ID_INDEX]  = rtId;
  SAState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  
  if (index >= 10) {
    // Set Action ID and Ret val
    SAState[SA_ACTION_ID_INDEX]  = 0;
    SAState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
    
    SAState[SA_STATUS_INDEX] = SA_OPER_MODE_OFF;
    SAState[SA_RIGHT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_OFF;
    SAState[SA_RIGHT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_OFF;

    post_cond = 1;
    index = 0;
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  return post_cond;
}

