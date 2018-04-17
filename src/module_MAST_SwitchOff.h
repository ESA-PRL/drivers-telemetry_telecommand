#ifndef ORC_MOD_MAST_SwitchOff_H
#define ORC_MOD_MAST_SwitchOff_H

#include "module.h"
#include "module_MAST_SwitchOff_Inc.h"


/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_MAST_SwitchOff : public ModuleAlgo
{
 public:
  static const int TARGET_MECHANISM_DEP  = 0;
  static const int TARGET_MECHANISM_PAN  = 1;
  static const int TARGET_MECHANISM_TILT = 2;
  static const int TARGET_MECHANISM_PAN_TILT = 3;
  
  // example code
  int index;
  
  // duration of the activity
  double duration;
  
  // includes power system information
  double MastState[MAX_STATE_SIZE];
  
  // the Action id
  int rtId;
  
  // the action execution status
  int action_exec_status;
  
  int targetMechanism;
  
  // reference to the Mast PhR
  //  orc_PhR_Mast *phrMast;
  
 public:
  orc_Mod_MAST_SwitchOff (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_MAST_SwitchOff ();
  
  // Output Event Ports declaration
  int DMA_SwitchOff_prec;
  int DMA_SwitchOff_post;
  
  
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

// End class  orc_Mod_DMA_SwitchOff

