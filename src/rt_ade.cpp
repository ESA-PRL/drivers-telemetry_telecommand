#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

#define ADE_LEFT_Initialise_ID 2100
#define ADE_RIGHT_Initialise_ID 2101
#define ADE_LEFT_conf_ID 2102
#define ADE_RIGHT_conf_ID 2103
#define ADE_LEFT_ReleaseHDRM_ID 2104
#define ADE_RIGHT_ReleaseHDRM_ID 2105
#define ADE_LEFT_SwitchOff_ID 2106
#define ADE_RIGHT_SwitchOff_ID 2107

extern RobotProcedure*  theRobotProcedure;

int RobotTask::computeADEs_Activate(){
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_WARMUP;
  ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
  ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  ADEState[ADE_ACTION_ID_INDEX]  = 1.0;
  if (index == 2) {
    ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
    ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
    ADEState[ADE_ACTION_ID_INDEX]  = 0.0;
    post_cond = 1;
    index = 0;
  }
  index++;
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeADEs_DeActivate(){
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
  ADEState[ADE_ACTION_ID_INDEX]  = 1.0;
  if (index == 2) {
    ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
    ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
    ADEState[ADE_ACTION_ID_INDEX]  = 0.0;
    post_cond = 1;
    index = 0;
  }
  index++;
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

int RobotTask::computeADE_LEFT_Initialise(){ 
  std::cerr << rtName << std::endl; 

  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  rtId = ADE_LEFT_Initialise_ID; 

  if (param_completed == 0){
    strcpy(ade_id, "left");
    
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

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
int RobotTask::computeADE_LEFT_conf(){ 

  std::cerr << rtName << std::endl; 
  rtId= ADE_LEFT_conf_ID;
  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){
    
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, target_mode)) {
      post_cond = 1;
      return post_cond;
    }
    if (!strcmp(target_mode, "STANDBY") || 
	!strcmp(target_mode, "OPERATIONAL") || 
	!strcmp(target_mode, "HDRM")) {
    } 
    else {
      post_cond = 1;
      return post_cond;
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
      return post_cond;
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
int RobotTask::computeADE_LEFT_ReleaseHDRM(){
  
  std::cerr << rtName << std::endl;
  rtId = ADE_LEFT_ReleaseHDRM_ID;
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
      return post_cond;
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

      if (!strcmp(hdrm_id, "HDRM_BODY_1")) {
	ADEState[HDRM_BODY_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_BODY_2")) {
	ADEState[HDRM_BODY_2_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_BODY_3")) {
	ADEState[HDRM_BODY_3_STATUS_INDEX] = HDRM_ON;
      }      
      else if (!strcmp(hdrm_id, "HDRM_DRILL_1")) {
	ADEState[HDRM_DRILL_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_DRILL_2")) {
	ADEState[HDRM_DRILL_2_STATUS_INDEX] = HDRM_ON;
      }      
      else if (!strcmp(hdrm_id, "HDRM_MAST")) {
	ADEState[HDRM_MAST_STATUS_INDEX] = HDRM_ON;
      }      
      else if (!strcmp(hdrm_id, "HDRM_SA_LEFT_1")) {
	ADEState[HDRM_SA_LEFT_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_LEFT_2")) {
	ADEState[HDRM_SA_LEFT_2_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_SA_LEFT_3")) {
	ADEState[HDRM_SA_LEFT_3_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_UMBILICAL_1")) {
	ADEState[HDRM_UMBILICAL_1_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_UMBILICAL_2")) {
	ADEState[HDRM_UMBILICAL_2_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_FL")) {
	ADEState[HDRM_WHEEL_FL_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_FR")) {
	ADEState[HDRM_WHEEL_FR_STATUS_INDEX] = HDRM_ON;
      }      
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_ML")) {
	ADEState[HDRM_WHEEL_ML_STATUS_INDEX] = HDRM_ON;
      }      
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_MR")) {
	ADEState[HDRM_WHEEL_MR_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_RL")) {
	ADEState[HDRM_WHEEL_RL_STATUS_INDEX] = HDRM_ON;
      }
      else if (!strcmp(hdrm_id, "HDRM_WHEEL_RR")) {
	ADEState[HDRM_WHEEL_RR_STATUS_INDEX] = HDRM_ON;
      }

      // Set Action ID and Ret val
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      post_cond = 1;
    }

    index++;
  }

  if ( theRobotProcedure->GetParameters()->set( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  } 
  return post_cond;
}

/**
 *
 */
int RobotTask::computeADE_LEFT_SwitchOff(){ 

  std::cerr << rtName << std::endl; 
  rtId=ADE_LEFT_SwitchOff_ID;
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
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
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
int RobotTask::computeADE_RIGHT_Initialise(){ 
 
  std::cerr << rtName << std::endl; 
  rtId = ADE_RIGHT_Initialise_ID;
  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
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
int RobotTask::computeADE_RIGHT_conf(){ 

  std::cerr << rtName << std::endl; 
  rtId = ADE_RIGHT_conf_ID;
  if ( theRobotProcedure->GetParameters()->get( "ADEState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, target_mode)) {
      post_cond = 1;
      return post_cond;
    }
    if (!strcmp(target_mode, "STANDBY") || !strcmp(target_mode, "OPERATIONAL")
	|| !strcmp(target_mode, "HDRM")) {
    } 
    else {
      post_cond = 1;
      return post_cond;
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
      return post_cond;
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
int RobotTask::computeADE_RIGHT_ReleaseHDRM(){ 

  std::cerr << rtName << std::endl; 
  rtId = ADE_RIGHT_ReleaseHDRM_ID;
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
      return post_cond;
    }

    ade_duration = 10.0;
    
    param_completed = 1;
  }

  if (init_completed == 0) {
    
    init_completed = 1;
  }

  if (compute_completed == 0){
    ADEState[ADE_ACTION_ID_INDEX] = rtId;
    ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
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

    index++;
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
int RobotTask::computeADE_RIGHT_SwitchOff(){ 

  std::cerr << rtName << std::endl; 
  rtId= ADE_RIGHT_SwitchOff_ID;
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

    if (index > 5) {
      if (!strcmp(ade_id, "left")) {
	ADEState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
      } else if (!strcmp(ade_id, "right")) {
	ADEState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      } 
      ADEState[ADE_ACTION_ID_INDEX] = 0;
      ADEState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
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
