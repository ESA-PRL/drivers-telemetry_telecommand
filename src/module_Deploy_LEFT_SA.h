#ifndef ORC_MOD_Deploy_LEFT_SA_H
#define ORC_MOD_Deploy_LEFT_SA_H

#include "module.h"

#include "module_Deploy_LEFT_SA_Inc.h"
#include "module_ADE_ReleaseHDRM.h"
#include "module_SA_LEFT_Primary_Initialise.h"
#include "module_SA_LEFT_Secondary_Initialise.h"
#include "module_SA_LEFT_Primary_MoveTo.h"
#include "module_SA_LEFT_Secondary_MoveTo.h"
#include "module_SA_LEFT_Primary_SwitchOff.h"
#include "module_SA_LEFT_Secondary_SwitchOff.h"
#include "module_GNC_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  //
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 4");
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 5");
  // call ActivateActionFromTask()("ADE_ReleaseHDRM", "0 6");
  // call ActivateActionFromTask()("SA_LEFT_Primary_Initialise", "");
  // ||
  // call ActivateActionFromTask()("SA_LEFT_Secondary_Initialise", "");
  // call ActivateActionFromTask()("SA_LEFT_Primary_MoveTo", "-10.0");
  // call ActivateActionFromTask()("SA_LEFT_Secondary_MoveTo", "20.0");
  // call ActivateActionFromTask()("SA_LEFT_Primary_MoveTo", "30.0");
  // call ActivateActionFromTask()("SA_LEFT_Primary_SwitchOff", "");
  // ||
  // call ActivateActionFromTask()("SA_LEFT_Secondary_SwitchOff", "");
  // call ActivateActionFromTask()("GNC_SwitchOff", "");
  //

  class orc_Mod_Deploy_LEFT_SA : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;


    orc_Mod_ADE_ReleaseHDRM              ADE_ReleaseHDRM;
    orc_Mod_SA_LEFT_Primary_Initialise   SA_LEFT_Primary_Initialise;
    orc_Mod_SA_LEFT_Secondary_Initialise SA_LEFT_Secondary_Initialise ;
    orc_Mod_SA_LEFT_Primary_MoveTo       SA_LEFT_Primary_MoveTo;
    orc_Mod_SA_LEFT_Secondary_MoveTo     SA_LEFT_Secondary_MoveTo;
    orc_Mod_SA_LEFT_Primary_SwitchOff    SA_LEFT_Primary_SwitchOff;
    orc_Mod_SA_LEFT_Secondary_SwitchOff  SA_LEFT_Secondary_SwitchOff;
    orc_Mod_GNC_SwitchOff                GNC_SwitchOff;
    
    int ADE_ReleaseHDRM_0_4_phase;
    int ADE_ReleaseHDRM_0_5_phase;
    int ADE_ReleaseHDRM_0_6_phase;
    int SA_LEFT_Primary_Initialise_phase;
    int SA_LEFT_Secondary_Initialise_phase;
    int SA_LEFT_Primary_MoveTo_phase;
    int SA_LEFT_Secondary_MoveTo_phase;
    int SA_LEFT_Primary_SwitchOff_phase;
    int SA_LEFT_Secondary_SwitchOff_phase;
    int GNC_SwitchOff_phase;

  public:
    orc_Mod_Deploy_LEFT_SA (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_Deploy_LEFT_SA ();
    
    // Output Event Ports declaration
    int Deploy_LEFT_SA_prec;
    int Deploy_LEFT_SA_post;
    
    
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

// End class  orc_Mod_Deploy_LEFT_SA 

