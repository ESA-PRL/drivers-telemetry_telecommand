#ifndef ORC_MOD_Deploy_Mast_H
#define ORC_MOD_Deploy_Mast_H

#include "module.h"
  
#include "module_Deploy_Mast_Inc.h"
#include "module_GNC_MonitoringOnly.h" 
#include "module_MAST_PAN_Initialise.h"
#include "module_MAST_PAN_MoveTo.h"
#include "module_MAST_PAN_SwitchOff.h"
#include "module_MAST_TILT_Initialise.h"
#include "module_MAST_TILT_MoveTo.h"
#include "module_MAST_TILT_SwitchOff.h"
#include "module_MAST_DEP_Initialise.h"
#include "module_MAST_DEP_MoveTo.h"
#include "module_MAST_DEP_SwitchOff.h"
#include "module_GNC_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_Deploy_Mast: public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;
    
    orc_Mod_GNC_MonitoringOnly GNC_MonitoringOnly; 
    orc_Mod_MAST_PAN_Initialise MAST_PAN_Initialise;
    orc_Mod_MAST_PAN_MoveTo MAST_PAN_MoveTo;
    orc_Mod_MAST_PAN_SwitchOff MAST_PAN_SwitchOff;
    orc_Mod_MAST_TILT_Initialise MAST_TILT_Initialise;
    orc_Mod_MAST_TILT_MoveTo MAST_TILT_MoveTo;
    orc_Mod_MAST_TILT_SwitchOff MAST_TILT_SwitchOff;
    orc_Mod_MAST_DEP_Initialise MAST_DEP_Initialise;
    orc_Mod_MAST_DEP_MoveTo MAST_DEP_MoveTo;
    orc_Mod_MAST_DEP_SwitchOff MAST_DEP_SwitchOff;
    orc_Mod_GNC_SwitchOff GNC_SwitchOff;


    int GNC_MonitoringOnly_phase; 
    int MAST_PAN_Initialise_phase;
    int MAST_PAN_MoveTo_phase;
    int MAST_PAN_SwitchOff_phase;
    int MAST_TILT_Initialise_phase;
    int MAST_TILT_MoveTo_phase;
    int MAST_TILT_SwitchOff_phase;
    int MAST_DEP_Initialise_phase;
    int MAST_DEP_MoveTo_phase;
    int MAST_DEP_SwitchOff_phase;
    int GNC_SwitchOff_phase;
  
  public:
    orc_Mod_Deploy_Mast (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_Deploy_Mast ();
    
    // Output Event Ports declaration
    int Deploy_Mast_prec;
    int Deploy_Mast_post;
    
    
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

// End class  orc_Mod_Deploy_Mast

