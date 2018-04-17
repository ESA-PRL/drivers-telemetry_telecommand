#ifndef ORC_RT_H
#define ORC_RT_H

/**
 * Include files
 */
#include "simplethread.h"
#include "linuxOrcc.h"
#include "utils.h"
#include "ctrl_state.h"

#include "module_includes.h"

//using namespace ControllerModelNamespace;

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

  //
  // MAST s/s (missing MAST_PAN_MoveTo & MAST_TILT_MoveTo)
  //
  int computeDeploy_Mast();
  int computeMAST_DEP_Initialise();
  int computeMAST_DEP_MoveTo();
  int computeMAST_DEP_SwitchOff();
  int computeMAST_PAN_Initialise();
  int computeMAST_PAN_MoveTo();
  int computeMAST_PAN_SwitchOff();
  int computeMAST_PTU_MoveTo();
  int computeMAST_TILT_Initialise();
  int computeMAST_TILT_MoveTo();
  int computeMAST_TILT_SwitchOff();

  //
  // DHS s/s 
  //
  int computeDHS_HighPwr2Reduced();
  int computeDHS_LowPwr2Reduced();
  int computeDHS_Nominal2Reduced();
  int computeDHS_Reduced2HighPwr();
  int computeDHS_Reduced2LowPwr();
  int computeDHS_Reduced2Nominal();

  //
  // COMMS s/s 
  //
  int computeCOMMS_SwitchOn();
  int computeCOMMS_LST2WH();
  int computeCOMMS_WH2LST();
  int computeCOMMS_SwitchOff();

  //
  // SA s/s 
  //
  int computeDeploy_LEFT_SA();
  int computeDeploy_RIGHT_SA();
  int computeSA_LEFT_Primary_Initialise();
  int computeSA_LEFT_Primary_MoveTo();
  int computeSA_LEFT_Primary_SwitchOff();
  int computeSA_LEFT_Secondary_Initialise();
  int computeSA_LEFT_Secondary_MoveTo();
  int computeSA_LEFT_Secondary_SwitchOff();
  int computeSA_RIGHT_Primary_Initialise();
  int computeSA_RIGHT_Primary_MoveTo();
  int computeSA_RIGHT_Primary_SwitchOff();
  int computeSA_RIGHT_Secondary_Initialise();
  int computeSA_RIGHT_Secondary_MoveTo();
  int computeSA_RIGHT_Secondary_SwitchOff();

  //
  // ADE s/s 
  //
  int computeADEs_Activate();
  int computeADEs_DeActivate();
  int computeADE_Operational2Standby();
  int computeADE_Standby2Operational();
  int computeADE_SwitchOn();
  int computeADE_SwitchOff();
  int computeADE_ReleaseHDRM();
  int computeHDRM_Release();

  //
  // GNC s/s 
  //
  int computeGNC_Initialise();
  int computeGNC_MonitoringOnly();
  int computeGNC_SwitchOff();
  int computeGNC_AbsLocalisation();

  // PANCAM s/s KK reorganised for egress
  int computePanCam_Initialise();
  int computePanCam_PIUSwitchOff();
  //  int computePanCam_InitWACs();
  //  int computePanCam_SwitchOn();
  //  int computePanCam_WACAcqImage();
  //  int computePanCam_WACGetImage();
  //  int computePanCam_SwitchOff();
  //  int computePANCAM_WAC_RRGB();
  //  int computePanCam_FilterSel();

  // RV s/s 
  int computeRV_WakeUp();
  int computeRV_Prepare4Comms();
  int computeRV_SwitchOffMobility();
  int computeRV_PostComms();
  int computeRV_Prepare4Travel();
  int computeRV_Prepare4Night();
  int computeRV_Prepare4Dozing();
  int computeRV_Prepare4Science();
  int computeRelease_Body();
  int computeRelease_Umbilical();

  int computeBEMA_Deploy_1();
  int computeBEMA_Deploy_2();

  //
  // MMS s/s
  //
  int computeMMS_WaitAbsTime();
  int computeMMS_WaitRelTime();

  // method used only for the continuous execution; in this
  // case it does not do anything
 private:
  virtual void* thread ();
  int deploy_left_sa_seq;
  int deploy_right_sa_seq;

  //
  // MAST s/s
  //
  ControllerModelNamespace::orc_Mod_Deploy_Mast          Deploy_Mast; 
  ControllerModelNamespace::orc_Mod_MAST_DEP_Initialise  MAST_DEP_Initialise; 
  ControllerModelNamespace::orc_Mod_MAST_DEP_MoveTo      MAST_DEP_MoveTo; 
  ControllerModelNamespace::orc_Mod_MAST_DEP_SwitchOff   MAST_DEP_SwitchOff; 
  ControllerModelNamespace::orc_Mod_MAST_PAN_Initialise  MAST_PAN_Initialise; 
  ControllerModelNamespace::orc_Mod_MAST_PAN_MoveTo      MAST_PAN_MoveTo; 
  ControllerModelNamespace::orc_Mod_MAST_PAN_SwitchOff   MAST_PAN_SwitchOff; 
  ControllerModelNamespace::orc_Mod_MAST_PTU_MoveTo      MAST_PTU_MoveTo; 
  ControllerModelNamespace::orc_Mod_MAST_TILT_Initialise MAST_TILT_Initialise; 
  ControllerModelNamespace::orc_Mod_MAST_TILT_MoveTo     MAST_TILT_MoveTo; 
  ControllerModelNamespace::orc_Mod_MAST_TILT_SwitchOff  MAST_TILT_SwitchOff; 

  //
  // DHS s/s
  //
  ControllerModelNamespace::orc_Mod_DHS_HighPwr2Reduced DHS_HighPwr2Reduced; 
  ControllerModelNamespace::orc_Mod_DHS_LowPwr2Reduced  DHS_LowPwr2Reduced; 
  ControllerModelNamespace::orc_Mod_DHS_Nominal2Reduced DHS_Nominal2Reduced; 
  ControllerModelNamespace::orc_Mod_DHS_Reduced2HighPwr DHS_Reduced2HighPwr; 
  ControllerModelNamespace::orc_Mod_DHS_Reduced2LowPwr  DHS_Reduced2LowPwr; 
  ControllerModelNamespace::orc_Mod_DHS_Reduced2Nominal DHS_Reduced2Nominal; 
  
  //
  // COMMS s/s
  //
  ControllerModelNamespace::orc_Mod_COMMS_SwitchOn  COMMS_SwitchOn; 
  ControllerModelNamespace::orc_Mod_COMMS_LST2WH    COMMS_LST2WH; 
  ControllerModelNamespace::orc_Mod_COMMS_WH2LST    COMMS_WH2LST; 
  ControllerModelNamespace::orc_Mod_COMMS_SwitchOff COMMS_SwitchOff; 

  //
  // SA s/s 
  //
  ControllerModelNamespace::orc_Mod_Deploy_LEFT_SA                Deploy_LEFT_SA; 
  ControllerModelNamespace::orc_Mod_Deploy_RIGHT_SA               Deploy_RIGHT_SA; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Primary_Initialise    SA_LEFT_Primary_Initialise; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Primary_MoveTo        SA_LEFT_Primary_MoveTo; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Primary_SwitchOff     SA_LEFT_Primary_SwitchOff; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Secondary_Initialise  SA_LEFT_Secondary_Initialise; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Secondary_MoveTo      SA_LEFT_Secondary_MoveTo; 
  ControllerModelNamespace::orc_Mod_SA_LEFT_Secondary_SwitchOff   SA_LEFT_Secondary_SwitchOff; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Primary_Initialise   SA_RIGHT_Primary_Initialise; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Primary_MoveTo       SA_RIGHT_Primary_MoveTo; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Primary_SwitchOff    SA_RIGHT_Primary_SwitchOff; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Secondary_Initialise SA_RIGHT_Secondary_Initialise; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Secondary_MoveTo     SA_RIGHT_Secondary_MoveTo; 
  ControllerModelNamespace::orc_Mod_SA_RIGHT_Secondary_SwitchOff  SA_RIGHT_Secondary_SwitchOff; 

  //
  // ADE s/s 
  //
  ControllerModelNamespace::orc_Mod_ADE_Operational2Standby ADE_Operational2Standby; 
  ControllerModelNamespace::orc_Mod_ADE_Standby2Operational ADE_Standby2Operational; 
  ControllerModelNamespace::orc_Mod_ADE_SwitchOn            ADE_SwitchOn; 
  ControllerModelNamespace::orc_Mod_ADE_SwitchOff           ADE_SwitchOff; 
  ControllerModelNamespace::orc_Mod_ADEs_Activate           ADEs_Activate; 
  ControllerModelNamespace::orc_Mod_ADEs_DeActivate         ADEs_DeActivate; 
  ControllerModelNamespace::orc_Mod_ADE_ReleaseHDRM         ADE_ReleaseHDRM; 
  ControllerModelNamespace::orc_Mod_HDRM_Release            HDRM_Release; 

  //
  // GNC s/s
  //
  ControllerModelNamespace::orc_Mod_GNC_Initialise      GNC_Initialise; 
  ControllerModelNamespace::orc_Mod_GNC_MonitoringOnly  GNC_MonitoringOnly; 
  ControllerModelNamespace::orc_Mod_GNC_SwitchOff       GNC_SwitchOff; 
  ControllerModelNamespace::orc_Mod_GNC_AbsLocalisation GNC_AbsLocalisation; 

  //
  // PANCAM s/s KK 
  //
  ControllerModelNamespace::orc_Mod_PanCam_Initialise   PanCam_Initialise;   
  ControllerModelNamespace::orc_Mod_PanCam_PIUSwitchOff PanCam_PIUSwitchOff;

  //
  // PANCAM s/s KK 
  //
  ControllerModelNamespace::orc_Mod_RV_PostComms         RV_PostComms; 
  ControllerModelNamespace::orc_Mod_RV_Prepare4Comms     RV_Prepare4Comms; 
  ControllerModelNamespace::orc_Mod_RV_Prepare4Dozing    RV_Prepare4Dozing; 
  ControllerModelNamespace::orc_Mod_RV_Prepare4Night     RV_Prepare4Night; 
  ControllerModelNamespace::orc_Mod_RV_Prepare4Science   RV_Prepare4Science; 
  ControllerModelNamespace::orc_Mod_RV_Prepare4Travel    RV_Prepare4Travel; 
  ControllerModelNamespace::orc_Mod_RV_SwitchOffMobility RV_SwitchOffMobility; 
  ControllerModelNamespace::orc_Mod_RV_WakeUp            RV_WakeUp;
  ControllerModelNamespace::orc_Mod_Release_Body         Release_Body;
  ControllerModelNamespace::orc_Mod_Release_Umbilical    Release_Umbilical;

  //
  // MMS s/s KK 
  // 
  ControllerModelNamespace::orc_Mod_MMS_WaitRelTime         MMS_WaitRelTime; 
  ControllerModelNamespace::orc_Mod_MMS_WaitAbsTime         MMS_WaitAbsTime; 
};

#endif

