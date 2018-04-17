#ifndef ORC_MOD_ADE_Operational2Standby_H
#define ORC_MOD_ADE_Operational2Standby_H

#include "module.h"
// #include "PhR_Ade.h"

#include "module_ADE_Operational2Standby_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_ADE_Operational2Standby : public ModuleAlgo
  {
  public:
    
    // example code
    int index;
    
    //     orc_PhR_Ade *phrAde;
    
    double AdeState[MAX_STATE_SIZE];

    char ade_id[256];
    
    char target_mode[256];
    
    int target_mode_id;
    
    double duration;
    
    // the action execution status
    int action_exec_status;
    
    // the action id
    int rtId;
    
  public:
    orc_Mod_ADE_Operational2Standby (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_ADE_Operational2Standby ();
    
    // Output Event Ports declaration
    int ADE_Operational2Standby_prec;
    int ADE_Operational2Standby_post;
    
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

// End class  orc_Mod_ADE_Operational2Standby

