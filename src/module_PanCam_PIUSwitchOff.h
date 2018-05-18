#ifndef ORC_MOD_PanCam_PIUSwitchOff_H
#define ORC_MOD_PanCam_PIUSwitchOff_H

#include "module.h"

#include "module_PanCam_PIUSwitchOff_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

 /**
   * \brief Implements the **PanCam_PIUSwitchOff** Action. To switch off PIU gracefully.
   */
  class orc_Mod_PanCam_PIUSwitchOff : public ModuleAlgo
  {
  public:
    
    // the action id
    int rtId;
    
    // a counter
    int index;
    
    // reference to the pancam state
    double PanCamState[MAX_STATE_SIZE];
    
    // the action execution status
    int action_exec_status;
    
    double duration;
    
  public:
    orc_Mod_PanCam_PIUSwitchOff (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_PanCam_PIUSwitchOff ();
    
  public:
    // Output Event Ports declaration
    int PanCam_PIUSwitchOff_prec;
    int PanCam_PIUSwitchOff_post;
    
    
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

// End class  orc_Mod_PanCam_WAC_L_SwitchOff

