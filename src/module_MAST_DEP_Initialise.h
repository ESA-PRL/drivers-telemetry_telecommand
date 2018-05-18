#ifndef ORC_MOD_MAST_DEP_Initialise_H
#define ORC_MOD_MAST_DEP_Initialise_H

#include "module.h"

#include "module_MAST_DEP_Initialise_Inc.h"



/** The model of the o/b controller */
namespace ControllerModelNamespace {

  /**
   * \brief Implements the **MAST_DEP_Initialise** Action to Warm up and switch ON of the Mast deployment actuator
   */
  class orc_Mod_MAST_DEP_Initialise : public ModuleAlgo
{
 public:

	// example code
	int index;

	// the pan cam state
	double MastState[MAX_STATE_SIZE];

	// the desired state to transit
	char desiredState[1024];


	// warmup timeout - duration of the activity
	double warmUpTimeout;

	// the action id
	int rtId;

	// the action execution status
	int action_exec_status;

	// reference to the Mast PhR
	// orc_PhR_Mast *phrMast;

	int actionId;

	void setActionId(int action_id) {

	  actionId = action_id;

	}


 public:
	orc_Mod_MAST_DEP_Initialise (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_MAST_DEP_Initialise ();

 public:
  // Output Event Ports declaration
  int MAST_DEP_Initialise_prec; 
  int MAST_DEP_Initialise_post; 
  

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

// End class  orc_Mod_DMA_DEP_Initialise

