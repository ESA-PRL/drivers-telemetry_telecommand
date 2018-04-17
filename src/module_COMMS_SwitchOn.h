#ifndef ORC_MOD_COMMS_SwitchOn_H
#define ORC_MOD_COMMS_SwitchOn_H

#include "module.h"
// #include "PhR_Comms.h"

#include "module_COMMS_SwitchOn_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_COMMS_SwitchOn : public ModuleAlgo
{
 public:

  int index;
  
  // orc_PhR_Comms *phrComms;
  
  double CommsState[MAX_STATE_SIZE];
  
  char unitid[264];

  int cmd_index;
  
  int status_index;
  
  int final_state;
  
  double duration;
  
  double current_time;
  
  int cmd_id;

  // the action execution status
  int action_exec_status;
  
  // the action id
  int rtId;
  
 public:
  orc_Mod_COMMS_SwitchOn (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_COMMS_SwitchOn ();
  
  // Output Event Ports declaration
  int COMMS_SwitchOn_prec;
  int COMMS_SwitchOn_post;

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

// End class  orc_Mod_COMMS_SwitchOn

