#ifndef ORC_MOD_RV_SwitchOffMobility_H
#define ORC_MOD_RV_SwitchOffMobility_H

#include "module.h"

#include "prr.h"
#include "module_RV_SwitchOffMobility_Inc.h"

#include "module_GNC_SwitchOff.h"
#include "module_ADE_SwitchOff.h"
#include "module_DHS_HighPwr2Reduced.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_RV_SwitchOffMobility : public ModuleAlgo
  {
  public:
    
    int index;
    
    
    double RoverState[MAX_STATE_SIZE];
    
    double current_time;
    double duration;
    char taskid[124];

    orc_Mod_GNC_SwitchOff       GNC_SwitchOff;
    orc_Mod_ADE_SwitchOff       ADE_SwitchOff;
    orc_Mod_DHS_HighPwr2Reduced DHS_HighPwr2Reduced;

    int GNC_SwitchOff_phase;
    int ADE_SwitchOff_phase;
    int DHS_HighPwr2Reduced_phase;

  public:
    char task_param[20][124];

    // the action execution status
    int action_exec_status;
    
    // the action id
    int rtId;
    
  public:
    orc_Mod_RV_SwitchOffMobility (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_RV_SwitchOffMobility ();
    
    // Output Event Ports declaration
    int RV_SwitchOffMobility_prec;
    int RV_SwitchOffMobility_post;
    
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

// End class  orc_Mod_RV_SwitchOffMobility

