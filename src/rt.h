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
  void waitEndActionExec ();

  /** Get the name of the Robot Task */
  std::string GetName ();

  /** Get the Id of the Robot Task */
  int GetId();

  int SetTcRequestId (int ); 

  int GetTcRequestId ();
 
  int SetParam (char*);
  
void computeADEs_Activate(); 
void computeADEs_DeActivate(); 
void computeADE_LEFT_Initialise(); 
void computeADE_LEFT_conf(); 
void computeADE_LEFT_ReleaseHDRM(); 
void computeADE_LEFT_SwitchOff(); 
void computeADE_RIGHT_Initialise(); 
void computeADE_RIGHT_conf(); 
void computeADE_RIGHT_ReleaseHDRM(); 
void computeADE_RIGHT_SwitchOff(); 
void computeSA_LEFT_Initialise(); 
void computeSA_LEFT_PrimaryMoveTo(); 
void computeSA_LEFT_SecondaryMoveTo(); 
void computeSA_LEFT_SwitchOff(); 
void computeSA_RIGHT_Initialise(); 
void computeSA_RIGHT_PrimaryMoveTo(); 
void computeSA_RIGHT_SecondaryMoveTo(); 
void computeSA_RIGHT_SwitchOff(); 
void computeDeploy_LEFT_SA();
void computeDeploy_RIGHT_SA();
void computePanCam_Initialise(); 
void computePanCam_InitWACs(); 
void computePanCam_SwitchOn(); 
void computePanCam_WACAcqImage(); 
void computePanCam_WACGetImage(); 
void computePanCam_SwitchOff(); 
void computePanCam_PIUSwitchOff(); 
void computePANCAM_WAC_RRGB(); 
void computePanCam_FilterSel(); 
void computeMAST_TILT_Initialise(); 
void computeDeploy_Mast(); 
void computeMAST_PAN_Initialise(); 
void computeMAST_PTU_MoveTo(); 
void computeMAST_TILT_SwitchOff(); 
void computeMAST_PAN_SwitchOff(); 
void computeBEMA_Deploy_1(); 
void computeBEMA_Deploy_2(); 
void computeGNC_Initialise(); 
void computeGNC_LLO(); 
void computeRelease_Umbilical();
void computeGNC_SwitchOff(); 
void computeGNC_MonitoringOnly();
void computeRV_WakeUp(); 
void computeMMS_WaitAbsTime(); 
void computeMMS_WaitRelTime(); 
void computeRV_Prepare4Comms(); 
void computeRV_SwitchOffMobility(); 
void computeRV_PostComms(); 
void computeDHS_Go2Nominal(); 
void computeRV_Prepare4Travel(); 
void computeRV_Prepare4Night(); 
void computeRV_Prepare4Dozing(); 

  // method used only for the continuous execution; in this
  // case it does not do anything
 private:
  virtual void* thread ();

};

#endif

