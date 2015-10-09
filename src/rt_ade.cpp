#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"


extern RobotProcedure*  theRobotProcedure;


void RobotTask::computeADE_LEFT_Initialise(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    strcpy(ade_id, "left");
    
    if (!strcmp(ade_id, "left")) {
      ade_duration = ADE_LEFT_WARMUP_TIME;
    } else if (!strcmp(ade_id, "right")) {
      ade_duration = ADE_RIGHT_WARMUP_TIME;
    }
    param_completed = 1;
  }
  
  if (!strcmp(ade_id, "left")) {
    ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_WARMUP;
  } else if (!strcmp(ade_id, "right")) {
    ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
  }
  
  if (index >= ((ade_duration + 10.0)
		/ (theRobotProcedure->Clock->GetBasePeriod()))) {
    if (!strcmp(ade_id, "left")) {
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
    } else if (!strcmp(ade_id, "right")) {
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
    } 
    
    post_cond = 1;
    
    ADEState[ADE_ACTION_ID_INDEX] = 0;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
  } 
  else {
    
    if (index >= (ade_duration)
	/ (theRobotProcedure->Clock->GetBasePeriod())) {
      
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_INIT;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_INIT;
      } 
      
    } 
    else {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_WARMUP;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
      } 
    }
    
  }

  index++;
  
  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_LEFT_conf(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, target_mode)) {
      post_cond = 1;
      return;
    }
    if (!strcmp(target_mode, "STANDBY") || 
	!strcmp(target_mode, "OPERATIONAL") || 
	!strcmp(target_mode, "HDRM")) {
    } 
    else {
      post_cond = 1;
      return;
    }
    strcpy(ade_id, "left");
	
    param_completed = 1;
  }
  
  if (init_completed == 0) {
    if (!strcmp(target_mode, "STANDBY")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_STNDBY;
    } else if (!strcmp(target_mode, "OPERATIONAL")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_OP_MOTORS;
    } else if (!strcmp(target_mode, "HDRM")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_STNDBY_HDRM;
    } else {
      post_cond = 1;
      return;
    }
    init_completed = 1;
  }

  if (compute_completed == 0){
    
    // Set Action ID and Ret val
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index >= (ade_duration / theRobotProcedure->Clock->GetBasePeriod())) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = target_mode_id;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = target_mode_id;
      } 
      
      // Set Action ID and Ret val
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }
  }
  
  index++;
  
  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeADE_LEFT_ReleaseHDRM(){ 
  
  std::cerr << rtName << std::endl;
  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){

    strcpy(ade_id, "left");

    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, hdrm_id)) {
      post_cond = 1;
      return;
    }
    ade_duration = 10.0;
    
    target_mode_id = ADE_OPER_MODE_OP_HDRM;
    
    param_completed = 1;
  }
  
  if (init_completed == 0) {
    
    init_completed = 1;
  }
  
  if (compute_completed == 0){
    
    if (!strcmp(ade_id, "left")) {
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } else if (!strcmp(ade_id, "right")) {
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } 
    
    // Set Action ID and Ret val
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index >= (ade_duration / (theRobotProcedure->Clock->GetBasePeriod()))) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY_HDRM;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY_HDRM;
      }
      
      if (!strcmp(hdrm_id, "HDRM_SA_LEFT_1")) {
	ADEState[HDRM_SA_LEFT_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_LEFT_2")) {
	ADEState[HDRM_SA_LEFT_2_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_LEFT_3")) {
	ADEState[HDRM_SA_LEFT_3_STATUS_INDEX] = HDRM_ON;
      }

      // Set Action ID and Ret val
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      post_cond = 1;
    }
  }

  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  } 
}

/**
 *
 */
void RobotTask::computeADE_LEFT_SwitchOff(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    strcpy(ade_id, "left");
    param_completed = 1;
  }
  
  if (init_completed == 0){
    init_completed = 1;
  }
  
  if (compute_completed == 0){
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    if (index > 5) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      } 
      post_cond = 1;
    }
    index ++;
  }
  
  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeADE_RIGHT_Initialise(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    
    strcpy(ade_id, "right");
    
    if (!strcmp(ade_id, "left")) {
      ade_duration = ADE_LEFT_WARMUP_TIME;
    } else if (!strcmp(ade_id, "right")) {
      ade_duration = ADE_RIGHT_WARMUP_TIME;
    }
    param_completed = 1;
  }
  
  if (!strcmp(ade_id, "left")) {
    ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_WARMUP;
  } else if (!strcmp(ade_id, "right")) {
    ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
  }

  if (index >= ((ade_duration + 10.0)
	  / (theRobotProcedure->Clock->GetBasePeriod()))) {
    if (!strcmp(ade_id, "left")) {
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
    } else if (!strcmp(ade_id, "right")) {
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
    } 
    
    post_cond = 1;
    
    ADEState[ADE_ACTION_ID_INDEX] = 0;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
  } else {
    
    if (index >= (ade_duration)
	/ (theRobotProcedure->Clock->GetBasePeriod())) {
      
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_INIT;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_INIT;
      } 
      
    } else {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_WARMUP;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
      } 
    }
    
  }

  index++;

  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeADE_RIGHT_conf(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, target_mode)) {
      post_cond = 1;
      return;
    }
    if (!strcmp(target_mode, "STANDBY") || !strcmp(target_mode, "OPERATIONAL")
	|| !strcmp(target_mode, "HDRM")) {
    } 
    else {
      post_cond = 1;
      return;
    }
    strcpy(ade_id, "right");
	
    param_completed = 1;
  }
  
  if (init_completed == 0) {
    if (!strcmp(target_mode, "STANDBY")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_STNDBY;
    } else if (!strcmp(target_mode, "OPERATIONAL")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_OP_MOTORS;
    } else if (!strcmp(target_mode, "HDRM")) {
      ade_duration = 5.0; // sec
      target_mode_id = ADE_OPER_MODE_STNDBY_HDRM;
    } else {
      post_cond = 1;
      return;
    }
    init_completed = 1;
  }

  if (compute_completed == 0){

    // Set Action ID and Ret val
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index >= (ade_duration / theRobotProcedure->Clock->GetBasePeriod())) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = target_mode_id;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = target_mode_id;
      } 
      
      // Set Action ID and Ret val
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }

  }
  
  index++;


  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeADE_RIGHT_ReleaseHDRM(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){

    strcpy(ade_id, "right");

    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, hdrm_id)) {
      post_cond = 1;
      return;
    }

    ade_duration = 10.0;
    
    param_completed = 1;
  }

  if (init_completed == 0) {
    
    init_completed = 1;
  }

  if (compute_completed == 0){
    
    if (!strcmp(ade_id, "left")) {
      ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } else if (!strcmp(ade_id, "right")) {
      ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } 
    
    // Set Action ID and Ret val
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index
	>= (ade_duration / (theRobotProcedure->Clock->GetBasePeriod()))) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY_HDRM;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY_HDRM;
      }
      
      if (!strcmp(hdrm_id, "HDRM_SA_RIGHT_1")) {
	ADEState[HDRM_SA_RIGHT_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_RIGHT_2")) {
	ADEState[HDRM_SA_RIGHT_2_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_RIGHT_3")) {
	ADEState[HDRM_SA_RIGHT_3_STATUS_INDEX] = HDRM_ON;
      }

      // Set Action ID and Ret val
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      post_cond = 1;
    }
  }

  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computeADE_RIGHT_SwitchOff(){ 

  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    strcpy(ade_id, "right");
    param_completed = 1;
  }
  
  if (init_completed == 0){
    init_completed = 1;
  }
  
  if (compute_completed == 0){
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

    std::cerr << index << std::endl;

    if (index > 5) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      } 
      post_cond = 1;
    }
    index ++;
  }
  
  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

