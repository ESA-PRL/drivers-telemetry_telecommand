#ifndef ORC_RT_H
#define ORC_RT_H

/**
 * Include files
 */
#include "simplethread.h"
#include "linuxOrcc.h"
#include "utils.h"
#include "ctrl_state.h"


class RobotTask : public SimpleThread
{
 protected:
  double State[MAX_STATE_SIZE];
  double ADEState[MAX_STATE_SIZE];
  double SAState[MAX_STATE_SIZE];
  double PanCamState[MAX_STATE_SIZE];
  double MastState[MAX_STATE_SIZE];
  double GNCState[MAX_STATE_SIZE];
  double TTCState[MAX_STATE_SIZE];
  double DHSState[MAX_STATE_SIZE];
  
  /** The Id of the Robot Task */
  int rtId;

  /** The name of the Robot Task */
  std::string rtName;

  // PANCAM
  double warmUpTimeout;
  int status_index;
  int current_status;
  int previous_status;
  int final_status;
  char cameraid[80]; 
  char exposure_time_str[80]; 
  char exposure_mode[80];
  double duration;
  char compression_level[80];
  int filterid;
  double current_filterid;

  // ADE
  char ade_id[80];
  char target_mode[80];
  char hdrm_id[80];
  int target_mode_id;
  double ade_duration;

  double current_time;
  
  int index;
  int param_completed;
  int init_completed;
  int compute_completed;
  int end_completed;

  // SA MoveTo
  double tilt;

  double initSAPose[SA_DOF];
  double finalSAPose[SA_DOF];
  double jointSATrajDuration[SA_DOF];
  double jointSAMaxSpeed[SA_DOF];
  double saCurrentTime;
  double saTrajDuration;
  double saCurrentPose[SA_DOF];


  double initMASTPose[MAST_DOF];
  double finalMASTPose[MAST_DOF];
  double jointMASTTrajDuration[MAST_DOF];
  double jointMASTMaxSpeed[MAST_DOF];
  double mastCurrentTime;
  double mastTrajDuration;
  double mastCurrentPose[MAST_DOF];

  // all trajectories
  double tFracDur;
  double rt;

  // RVR durations
  double rvr_duration;
  double dhs_go2_duration;
  double comms_switchon_duration;
  double comms_conf_duration;

 protected:	

  /** The semaphore used to block the execution until the end */
  ORCSEM_ID waitEndActionSem;
  
  /** The id of the thread that controls the Modules Tasks of the Robot Task */
  ORCTHR_ID ctrlId;   	
  
  int tcRequestId;
  
  char rtParams[1024];

 public:
  
  RobotTask (std::string name);
  virtual ~RobotTask ();
  
  int post_cond;

  /** Launch the threads that correspond to the Module Tasks */
  int Control ();  
  
  /** Blocks until the waitEndActionSem is deblocked */
  int waitEndActionExec ();

  /** Get the name of the Robot Task */
  std::string GetName ();

  /** Get the Id of the Robot Task */
  int GetId();

  int SetTcRequestId (int ); 

  int GetTcRequestId ();
 
  int SetParam (char*);
  
int computeADEs_Activate(); 
int computeADEs_DeActivate(); 
int computeADE_LEFT_Initialise(); 
int computeADE_LEFT_conf(); 
int computeADE_LEFT_ReleaseHDRM(); 
int computeADE_LEFT_SwitchOff(); 
int computeADE_RIGHT_Initialise(); 
int computeADE_RIGHT_conf(); 
int computeADE_RIGHT_ReleaseHDRM(); 
int computeADE_RIGHT_SwitchOff(); 
int computeSA_LEFT_Initialise(); 
int computeSA_LEFT_PrimaryMoveTo(); 
int computeSA_LEFT_SecondaryMoveTo(); 
int computeSA_LEFT_SwitchOff(); 
int computeSA_RIGHT_Initialise(); 
int computeSA_RIGHT_PrimaryMoveTo(); 
int computeSA_RIGHT_SecondaryMoveTo(); 
int computeSA_RIGHT_SwitchOff(); 
int computeDeploy_LEFT_SA();
int computeDeploy_RIGHT_SA();
int computePanCam_Initialise(); 
int computePanCam_InitWACs(); 
int computePanCam_SwitchOn(); 
int computePanCam_WACAcqImage(); 
int computePanCam_WACGetImage(); 
int computePanCam_SwitchOff(); 
int computePanCam_PIUSwitchOff(); 
int computePANCAM_WAC_RRGB(); 
int computePanCam_FilterSel(); 
int computeMAST_TILT_Initialise(); 
int computeDeploy_Mast(); 
int computeMAST_PAN_Initialise(); 
int computeMAST_PTU_MoveTo(); 
int computeMAST_TILT_SwitchOff(); 
int computeMAST_PAN_SwitchOff(); 
int computeBEMA_Deploy_1(); 
int computeBEMA_Deploy_2(); 
int computeGNC_Initialise(); 
int computeRelease_Umbilical();
int computeGNC_SwitchOff(); 
int computeGNC_MonitoringOnly();
int computeRV_WakeUp(); 
int computeMMS_WaitAbsTime(); 
int computeMMS_WaitRelTime(); 
int computeRV_Prepare4Comms(); 
int computeRV_SwitchOffMobility(); 
int computeRV_PostComms(); 
int computeDHS_Go2Nominal(); 
int computeRV_Prepare4Travel(); 
int computeRV_Prepare4Night(); 
int computeRV_Prepare4Dozing(); 

  // method used only for the continuous execution; in this
  // case it does not do anything
 private:
  virtual void* thread ();
  int deploy_left_sa_seq;
  int deploy_right_sa_seq;

};

#endif

