#ifndef ORC_MOD_ADE_Standby2Operational_H
#define ORC_MOD_ADE_Standby2Operational_H

#include "module.h"
//#include "PhR_Ade.h"

#include "module_ADE_Standby2Operational_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_ADE_Standby2Operational : public ModuleAlgo
  {
  public:
    
    // example code
    int index;
    
    //    orc_PhR_Ade *phrAde;
    
    double AdeState[MAX_STATE_SIZE];
    
    // the action execution status
    int action_exec_status;

    char ade_id[256];
    
    char target_mode[256];
    
    int target_mode_id;
    
    double duration;
    
    // the action id
    int rtId;
    
  public:
    orc_Mod_ADE_Standby2Operational (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_ADE_Standby2Operational ();
    
    // Output Event Ports declaration
    int ADE_Standby2Operational_prec;
    int ADE_Standby2Operational_post;
    
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

// End class  orc_Mod_ADE_Standby2Operational

