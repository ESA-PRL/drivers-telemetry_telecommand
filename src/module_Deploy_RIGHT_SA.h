#ifndef ORC_MOD_Deploy_RIGHT_SA_H
#define ORC_MOD_Deploy_RIGHT_SA_H

#include "module.h"

#include "module_Deploy_RIGHT_SA_Inc.h"
#include "module_ADE_ReleaseHDRM.h"
#include "module_SA_RIGHT_Primary_Initialise.h"
#include "module_SA_RIGHT_Secondary_Initialise.h"
#include "module_SA_RIGHT_Primary_MoveTo.h"
#include "module_SA_RIGHT_Secondary_MoveTo.h"
#include "module_SA_RIGHT_Primary_SwitchOff.h"
#include "module_SA_RIGHT_Secondary_SwitchOff.h"
#include "module_GNC_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  //
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 7");
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 8");
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 9");
  // call ActivateActionFromTask()("SA_RIGHT_Primary_Initialise", "");
  // ||
  // call ActivateActionFromTask()("SA_RIGHT_Secondary_Initialise", "");
  // call ActivateActionFromTask()("SA_RIGHT_Primary_MoveTo", "-10.0");
  // call ActivateActionFromTask()("SA_RIGHT_Secondary_MoveTo", "20.0");
  // call ActivateActionFromTask()("SA_RIGHT_Primary_MoveTo", "30.0");
  // call ActivateActionFromTask()("SA_RIGHT_Primary_SwitchOff", "");
  // ||
  // call ActivateActionFromTask()("SA_RIGHT_Secondary_SwitchOff", "");
  // call ActivateActionFromTask()("GNC_SwitchOff", "");
  //

  class orc_Mod_Deploy_RIGHT_SA : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;


    orc_Mod_ADE_ReleaseHDRM               ADE_ReleaseHDRM;
    orc_Mod_SA_RIGHT_Primary_Initialise   SA_RIGHT_Primary_Initialise;
    orc_Mod_SA_RIGHT_Secondary_Initialise SA_RIGHT_Secondary_Initialise ;
    orc_Mod_SA_RIGHT_Primary_MoveTo       SA_RIGHT_Primary_MoveTo;
    orc_Mod_SA_RIGHT_Secondary_MoveTo     SA_RIGHT_Secondary_MoveTo;
    orc_Mod_SA_RIGHT_Primary_SwitchOff    SA_RIGHT_Primary_SwitchOff;
    orc_Mod_SA_RIGHT_Secondary_SwitchOff  SA_RIGHT_Secondary_SwitchOff;
    orc_Mod_GNC_SwitchOff                 GNC_SwitchOff;
    
    int ADE_ReleaseHDRM_0_7_phase;
    int ADE_ReleaseHDRM_0_8_phase;
    int ADE_ReleaseHDRM_0_9_phase;
    int SA_RIGHT_Primary_Initialise_phase;
    int SA_RIGHT_Secondary_Initialise_phase;
    int SA_RIGHT_Primary_MoveTo_phase;
    int SA_RIGHT_Secondary_MoveTo_phase;
    int SA_RIGHT_Primary_SwitchOff_phase;
    int SA_RIGHT_Secondary_SwitchOff_phase;
    int GNC_SwitchOff_phase;

  public:
    orc_Mod_Deploy_RIGHT_SA (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_Deploy_RIGHT_SA ();
    
    // Output Event Ports declaration
    int Deploy_RIGHT_SA_prec;
    int Deploy_RIGHT_SA_post;
    
    
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

// End class  orc_Mod_Deploy_RIGHT_SA 

