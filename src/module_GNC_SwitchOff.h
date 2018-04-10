#ifndef ORC_MOD_GNC_SwitchOff_H
#define ORC_MOD_GNC_SwitchOff_H

//#include "module.h"

#include "module_GNC_SwitchOff_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  /**
   * \brief Implements the **GNC_SwitchOff** Action. 
   */
  class orc_Mod_GNC_SwitchOff // : public ModuleAlgo
{
 public:

	// counter for the move to logic
	int index;


	// the GNC state
	double GNCState[MAX_STATE_SIZE];

	// the action execution status
	int action_exec_status;

	double current_time;

	double action_duration;

	// the action id
	int rtId;

	// reference to the phr GNC
	// orc_PhR_GNC* phr_GNC;
 public:
	orc_Mod_GNC_SwitchOff (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_GNC_SwitchOff ();

 public:
  // Output Event Ports declaration
  int GNC_SwitchOff_prec;
int GNC_SwitchOff_post;


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

// End class  orc_Mod_GNC_SwitchOff

