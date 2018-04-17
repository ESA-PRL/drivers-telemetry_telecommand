#ifndef ORC_MOD_MMS_WaitAbsTime_H
#define ORC_MOD_MMS_WaitAbsTime_H

#include "module.h"

//#include "MMS_WaitAbsTime/user_code/module_MMS_WaitAbsTime_Inc.h"
#include "prr.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

class orc_Mod_MMS_WaitAbsTime : public ModuleAlgo
{
 public:
  
  int index;

  double waitTime;

  int waitMode;
  
  char wait_time_str[80];
  
  double curr_time;
  
  double final_time;
  
  int seconds;
  
  //  orc_PhR_System *phrSystem;
  
  double SystemState[MAX_STATE_SIZE];
  
  // the action execution status
  int action_exec_status;
  
  // the action id
  int rtId;
  
 public:
  orc_Mod_MMS_WaitAbsTime (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_MMS_WaitAbsTime ();
  
  // Output Event Ports declaration
  int MMS_WaitAbsTime_prec;
  int MMS_WaitAbsTime_post;

  char moduleParams[1024];

  // Methods of computation
  void init ();
  void param (char *);
  void reparam (char *);
  void compute ();
  void end ();
};

}

#endif

// End class  orc_Mod_MMS_WaitAbsTime

