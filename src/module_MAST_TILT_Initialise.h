#ifndef ORC_MOD_MAST_TILT_Initialise_H
#define ORC_MOD_MAST_TILT_Initialise_H

#include "module_MAST_TILT_Initialise_Inc.h"
//#include "module.h"


/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  /**
   * \brief Implements the **MAST_TILT_Initialise** Action to Warm up and switch ON of the Mast tilt actuator
   */
  class orc_Mod_MAST_TILT_Initialise // : public ModuleAlgo
  {
  public:
    static const int TARGET_MECHANISM_PAN  = 1;
    static const int TARGET_MECHANISM_TILT = 2;
    static const int TARGET_MECHANISM_PAN_TILT = 3;

    // example code
    int index;
    
    // the pan cam state
    double MastState[MAX_STATE_SIZE];
    
    
    // warmup timeout - duration of the activity
    double warmUpTimeout;
    
    // the action id
    int rtId;
    
    // the action execution status
    int action_exec_status;
    
    int targetMechanism;
    
    // reference to the Mast PhR
    //    orc_PhR_Mast *phrMast;
    
    int actionId;
    
    
    
  public:
    orc_Mod_MAST_TILT_Initialise (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_MAST_TILT_Initialise ();
    
  public:
    // Output Event Ports declaration
    int MAST_TILT_Initialise_prec;
    int MAST_TILT_Initialise_post;
    
    
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

// End class  orc_Mod_MAST_TILT_Initialise

