#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"


extern RobotProcedure*  theRobotProcedure;


/**
 *
 */
void RobotTask::computePanCam_Initialise(){
  std::cerr << rtName << std::endl; 

  rtId = 900;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    warmUpTimeout = PANCAM_WARMUP_TIMEOUT;
    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }
  if (compute_completed == 0){

    PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_INITIALISING;
    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index >= (warmUpTimeout/theRobotProcedure->Clock->GetBasePeriod())) {
      PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_STNDBY;
      // Set Action ID and Ret val
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      // send the post-condition
      post_cond = 1;
      
    }
    
    index++;
    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_InitWACs(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, cameraid)) {
      fprintf(stderr, "In  PanCam_InitWACs param failed\n");
      post_cond = 1;
      return;
    }
	
    if (!strcmp(cameraid,"WAC_R")) {
      status_index = PANCAM_WAC_R_MODE_INDEX;
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
    }
    else if (!strcmp(cameraid,"WAC_L")) {
      status_index = PANCAM_WAC_L_MODE_INDEX;
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
    }
    warmUpTimeout = 10.0;
    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }

  PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
  PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

  if (compute_completed == 0){
    if (index >= (warmUpTimeout/theRobotProcedure->Clock->GetBasePeriod())) {
      PanCamState[status_index] = final_status;
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }

    index++;
    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_SwitchOn(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    
    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, cameraid)) {
      fprintf(stderr, "In  PanCam_SwitchOn param failed\n");
      post_cond = 1;
      return;
    }
	
    if (!strcmp(cameraid,"WAC_R")) {
      status_index = PANCAM_WAC_R_MODE_INDEX;
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
    }
    else if (!strcmp(cameraid,"WAC_L")) {
      status_index = PANCAM_WAC_L_MODE_INDEX;
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
    }
    else if (!strcmp(cameraid,"HRC")) {
      status_index = PANCAM_HRC_MODE_INDEX;
      final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
    }
    
    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }
  if (compute_completed == 0){

    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

    if (index == 10) {

      PanCamState[status_index] = final_status;
      // Set Action ID and Ret val
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }
    
    index++;
  }
  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_WACAcqImage(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (param_completed == 0){

    if (4 != sscanf(rtParams, "%d %s %s %s", &tcRequestId, cameraid, exposure_time_str, exposure_mode)) {

      fprintf(stderr, "In PanCam_AcquireImage::param() parameterisation error\n");
      post_cond = 1;
      return;
    }

    if (!strcmp(cameraid,"WAC_R")) {
      status_index = PANCAM_WAC_R_MODE_INDEX;
      
      if (!strcmp(exposure_mode, "AutoExposure")) {
	final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
	duration = 1.631; // pancamPhR->PARAM_PANCAM_WAC_ACQUIRING_IMAGE_TIME;
      }
      else {
	final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
	duration = 0.2; // pancamPhR->PARAM_PANCAM_WAC_ACQUIRING_IMAGE_TIME;
      }
    }
    else if (!strcmp(cameraid,"WAC_L")) {
      status_index = PANCAM_WAC_L_MODE_INDEX;
      
      if (!strcmp(exposure_mode, "AutoExposure")) {
	final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
	duration = 1.631;
      }
      else {
	final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
	duration = 0.2;
      }
    }
    else if (!strcmp(cameraid,"HRC")) {
      
      status_index = PANCAM_HRC_MODE_INDEX;
      
      if (!strcmp(exposure_mode, "AutoExposure")) {
	
	if (!strcmp(exposure_time_str,"AF")) {
	  final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
	  duration = 61.297;
	}
	else {
	  final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
	  duration = 36.297;
	}
      }
      else {
	if (!strcmp(exposure_time_str,"AF")) {
	  final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
	  duration = 43.897;
	}
	else {
	  final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
	  duration = 18.897;
	}
      }
    }
    
    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }
  if (compute_completed == 0){

    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    PanCamState[PANCAM_OPER_MODE_INDEX] = PANCAM_OPER_MODE_OPERATING;
    PanCamState[status_index] = current_status;

    if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
      
      PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_STNDBY;
      PanCamState[status_index] = final_status;
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }

    index++;
    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_WACGetImage(){ 
  
  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if (param_completed == 0){

    if (3 != sscanf(rtParams, "%d %s %s", &tcRequestId, cameraid, compression_level)) {
      post_cond = 1;
      return;
    }
    param_completed = 1;
  }
  if (init_completed == 0){

    if (!strcmp(cameraid,"WAC_R")) {
      status_index = PANCAM_WAC_R_MODE_INDEX;
      if (!strcmp(compression_level, "Lossless")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSLESS;
      }
      else if (!strcmp(compression_level, "Lossy")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSY;
      }
      else if (!strcmp(compression_level, "Thumbnail")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_THUMBNAIL;
      }
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
      duration = PANCAM_WAC_GETTING_IMAGE_TIME;
    }
    else if (!strcmp(cameraid,"WAC_L")) {
      status_index = PANCAM_WAC_L_MODE_INDEX;
      if (!strcmp(compression_level, "Lossless")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSLESS;
      }
      else if (!strcmp(compression_level, "Lossy")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSY;
      }
      else if (!strcmp(compression_level, "Thumbnail")) {
	current_status = PANCAM_OPER_MODE_WAC_GETTING_IMAGE_THUMBNAIL;
      }
      final_status =  PANCAM_OPER_MODE_WAC_STANDBY;
      duration = PANCAM_WAC_GETTING_IMAGE_TIME;
    }
    else if (!strcmp(cameraid,"HRC")) {
      status_index = PANCAM_HRC_MODE_INDEX;
      current_status = PANCAM_OPER_MODE_HRC_GETTING_IMAGE;
      final_status =  PANCAM_OPER_MODE_HRC_STANDBY;
      duration = PANCAM_HRC_GETTING_IMAGE_TIME;
    }

    init_completed = 1;
  }
  if (compute_completed == 0){

    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    PanCamState[PANCAM_OPER_MODE_INDEX] = PANCAM_OPER_MODE_OPERATING;
    PanCamState[status_index] = current_status;

    if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
      
      PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_STNDBY;
      PanCamState[status_index] = final_status;
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }

    index ++;

    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_SwitchOff(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){

    if (2 != sscanf(rtParams, "%d %s", &tcRequestId, cameraid)) {
      
      post_cond = 1;
      return;
    }

    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }
  if (compute_completed == 0){
    
    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index == 10 ) {
      
      if (!strcmp(cameraid,"WAC_L")) {
	PanCamState[PANCAM_WAC_L_MODE_INDEX] = PANCAM_OPER_MODE_WAC_OFF;
	PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
	post_cond = 1;
      }
      else if (!strcmp(cameraid,"WAC_R")) {
	PanCamState[PANCAM_WAC_R_MODE_INDEX] = PANCAM_OPER_MODE_WAC_OFF;
	PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
	post_cond = 1;
      }
      else if (!strcmp(cameraid,"HRC")) {
	PanCamState[PANCAM_HRC_MODE_INDEX] = PANCAM_OPER_MODE_HRC_OFF;
	PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
	post_cond = 1;
      }
      else if (!strcmp(cameraid,"ALL")) {
	PanCamState[PANCAM_WAC_L_MODE_INDEX] = PANCAM_OPER_MODE_WAC_OFF;
	PanCamState[PANCAM_WAC_R_MODE_INDEX] = PANCAM_OPER_MODE_WAC_OFF;
	PanCamState[PANCAM_HRC_MODE_INDEX]   = PANCAM_OPER_MODE_HRC_OFF;
	PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_OFF;
	PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
	post_cond = 1;
      }
      else {
	PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_ERROR;
	post_cond = 1;
      }
    }
    
    index++;
    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_PIUSwitchOff(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;
  
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    duration = 2.0;
    param_completed = 1;
  }
  if (init_completed == 0){
    
    init_completed = 1;
  }
  if (compute_completed == 0){

    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    PanCamState[PANCAM_OPER_MODE_INDEX] =  PANCAM_OPER_MODE_SWITCHING_OFF;

    if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
      PanCamState[PANCAM_OPER_MODE_INDEX] = PANCAM_OPER_MODE_OFF;
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }

 index++;


    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }

  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePANCAM_WAC_RRGB(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if (param_completed == 0){

    param_completed = 1;
  }
  if (init_completed == 0){

    init_completed = 1;
  }
  if (compute_completed == 0){

    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

/**
 *
 */
void RobotTask::computePanCam_FilterSel(){ 

  std::cerr << rtName << std::endl; 

  rtId = 901;

  if ( theRobotProcedure->GetParameters()->get( "PanCamState", 
						DOUBLE, 
						MAX_STATE_SIZE, 0, 
						( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }

  if (param_completed == 0){
    if (3 != sscanf(rtParams, "%d %s %d", &tcRequestId, cameraid, &filterid)) {
      post_cond = 1;
      return;
    }
    param_completed = 1;
  }

  if (init_completed == 0){

    if (!strcmp(cameraid,"WAC_R")) {
      status_index = PANCAM_WAC_R_MODE_INDEX;
      previous_status = PanCamState[status_index];
      current_filterid = PanCamState[PANCAM_WAC_R_FILTER_POSE_INDEX];
    }
    else if (!strcmp(cameraid,"WAC_L")) {
      status_index = PANCAM_WAC_L_MODE_INDEX;
      previous_status = PanCamState[status_index];
      current_filterid = PanCamState[PANCAM_WAC_L_FILTER_POSE_INDEX];
    }
    
    PanCamState[status_index] = PANCAM_OPER_MODE_WAC_FILTER_SELECTION;
    duration = fabs(current_filterid - filterid) * 1.0; // one second per filter position
    
    if (!strcmp(cameraid,"WAC_L")) {
      PanCamState[PANCAM_WAC_L_FILTER_POSE_INDEX] = filterid;
    }
    else if (!strcmp(cameraid,"WAC_R")) {
      PanCamState[PANCAM_WAC_R_FILTER_POSE_INDEX] = filterid;
    }
    
    init_completed = 1;
  }

  if (compute_completed == 0){
    
    PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
    PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    PanCamState[PANCAM_OPER_MODE_INDEX] = PANCAM_OPER_MODE_OPERATING;
    PanCamState[status_index] = PANCAM_OPER_MODE_WAC_FILTER_SELECTION;
    
    if (index >= (duration/theRobotProcedure->Clock->GetBasePeriod())) {
      
      PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_STNDBY;
      PanCamState[status_index] = previous_status;
      PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
      PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
      post_cond = 1;
    }
    
    index++;
    // compute_completed = 1;
  }
  if (end_completed == 0){

    end_completed = 1;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
