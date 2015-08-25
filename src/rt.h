#ifndef ORC_RT_H
#define ORC_RT_H

/**
 * Include files
 */
#include "simplethread.h"
#include "linuxOrcc.h"
#include "utils.h"


class RobotTask : public SimpleThread
{
  
 protected:
  double State[MAX_STATE_SIZE];
  double ADEState[MAX_STATE_SIZE];
  double SAState[MAX_STATE_SIZE];
  double PanCamState[MAX_STATE_SIZE];
  double MastState[MAX_STATE_SIZE];
  double GNCState[MAX_STATE_SIZE];
  
  /** The Id of the Robot Task */
  int rtId;

  /** The name of the Robot Task */
  std::string rtName;

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
void computePanCam_Initialise(); 
void computePanCam_InitWACs(); 
void computePanCam_SwitchOn(); 
void computePanCam_WACAcqImage(); 
void computePanCam_WACGetImage(); 
void computePanCam_SwitchOff(); 
void computePanCam_PIUSwitchOff(); 
void computePANCAM_WAC_RRGB(); 
void computePanCam_FilterSel(); 
void computeMAST_DEP_Initialise(); 
void computeMAST_DEP_Deploy(); 
void computeMAST_PTU_Initialise(); 
void computeMAST_PTU_MoveTo(); 
void computeMAST_SwitchOff(); 
void computeBEMA_Deploy_1(); 
void computeBEMA_Deploy_2(); 
void computeGNC_Initialise(); 
void computeGNC_LLO(); 
void computeGNC_SwitchOff(); 
void computeRV_WakeUp(); 
void computeMMS_WaitAbsTime(); 
void computeRV_Prepare4Comms(); 
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
