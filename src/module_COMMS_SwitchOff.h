#ifndef ORC_MOD_COMMS_SwitchOff_H
#define ORC_MOD_COMMS_SwitchOff_H

#include "module.h"

#include "module_COMMS_SwitchOff_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_COMMS_SwitchOff : public ModuleAlgo
  {
  public:
    int rtId;     //Action Id
    int index;
    
    // includes power system information
    double CommsState[MAX_STATE_SIZE];
    
    // the id of the line to be switched on
    char unitid[264];
    
    
    int cmd_index;
    
    int status_index;
    
    int final_state;
    
    int cmd_id;
    
    
  public:
    orc_Mod_COMMS_SwitchOff (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_COMMS_SwitchOff ();
    
    // Output Event Ports declaration
    int COMMS_SwitchOff_prec;
    int COMMS_SwitchOff_post;
    
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

// End class  orc_Mod_COMMS_SwitchOff

