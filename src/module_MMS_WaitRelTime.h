#ifndef ORC_MOD_MMS_WaitRelTime_H
#define ORC_MOD_MMS_WaitRelTime_H

#include "module.h"
//#include "PhR_System.h"

#include "module_MMS_WaitRelTime_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_MMS_WaitRelTime : public ModuleAlgo
  {
  public:
    
    // example code
    int index;
    
    int waitMode;
    
    double waitTime;
    
    double curr_time;
    
    double final_time;
    
    //    orc_PhR_System *phrSystem;
    
    double SystemState[MAX_STATE_SIZE];
    
    // the action execution status
    int action_exec_status;
    
    // the action id
    int rtId;
    
  public:
    orc_Mod_MMS_WaitRelTime (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_MMS_WaitRelTime ();
    
    // Output Event Ports declaration
    int MMS_WaitRelTime_prec;
    int MMS_WaitRelTime_post;
    
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

// End class  orc_Mod_MMS_WaitRelTime

