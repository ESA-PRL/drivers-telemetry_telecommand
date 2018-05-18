#ifndef ORC_MOD_RV_PostComms_H
#define ORC_MOD_RV_PostComms_H
  
#include "module.h"
  
#include "module_RV_PostComms_Inc.h"
#include "module_COMMS_SwitchOff.h"
#include "module_DHS_Reduced2LowPwr.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  // call ActivateActionFromTask()("COMMS_SwitchOff", "MAIN");
  // call ActivateActionFromTask()("DHS_Reduced2LowPwr", "");
  // call ActivateActionFromTask()("COMMS_SwitchOff", "REDUNDANT");

  class orc_Mod_RV_PostComms : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;
    
    orc_Mod_COMMS_SwitchOff    COMMS_SwitchOff;
    orc_Mod_DHS_Reduced2LowPwr DHS_Reduced2LowPwr;
    
    int COMMS_SwitchOff_main_phase;
    int COMMS_SwitchOff_red_phase;
    int DHS_Reduced2LowPwr_phase;
    
  public:
    orc_Mod_RV_PostComms (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_RV_PostComms ();
    
    // Output Event Ports declaration
    int RV_PostComms_prec;
    int RV_PostComms_post;
    
    
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

// End class  orc_Mod_RV_PostComms

