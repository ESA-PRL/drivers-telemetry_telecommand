#ifndef ORC_MOD_RV_WakeUp_H
#define ORC_MOD_RV_WakeUp_H
  
#include "module.h"
  
#include "module_RV_WakeUp_Inc.h"
#include "module_DHS_LowPwr2Reduced.h"
#include "module_COMMS_SwitchOn.h"
#include "module_COMMS_LST2WH.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  //    call ActivateActionFromTask()("DHS_LowPwr2Reduced", "");
  //    call ActivateActionFromTask()("COMMS_SwitchOn", "MAIN");
  //    call ActivateActionFromTask()("COMMS_LST2WH", "MAIN");
  //    call ActivateActionFromTask()("COMMS_SwitchOn", "REDUNDANT");
  //    call ActivateActionFromTask()("COMMS_LST2WH", "REDUNDANT");

  class orc_Mod_RV_WakeUp : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;
    
    orc_Mod_DHS_LowPwr2Reduced DHS_LowPwr2Reduced;
    orc_Mod_COMMS_SwitchOn     COMMS_SwitchOn;
    orc_Mod_COMMS_LST2WH       COMMS_LST2WH;
    
    int DHS_LowPwr2Reduced_phase;
    int COMMS_SwitchOn_main_phase;
    int COMMS_SwitchOn_red_phase;
    int COMMS_LST2WH_main_phase;
    int COMMS_LST2WH_red_phase;
    
  public:
    orc_Mod_RV_WakeUp (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_RV_WakeUp ();
    
    // Output Event Ports declaration
    int RV_WakeUp_prec;
    int RV_WakeUp_post;
    
    
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

// End class  orc_Mod_RV_WakeUp

