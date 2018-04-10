#ifndef ORC_MOD_SA_RIGHT_Secondary_SwitchOff_H
#define ORC_MOD_SA_RIGHT_Secondary_SwitchOff_H

// #include "module.h"
// #include "PhR_SolarArray.h"

#include "module_SA_RIGHT_Secondary_SwitchOff_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_SA_RIGHT_Secondary_SwitchOff // : public ModuleAlgo
{
 public:

	// example code
	int index;

	// orc_PhR_SolarArray *phrSolarArray;
 
    double SolarArrayState[MAX_STATE_SIZE];

	// the action execution status
	int action_exec_status;

	// the action id
	int rtId;

 public:
	orc_Mod_SA_RIGHT_Secondary_SwitchOff (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_SA_RIGHT_Secondary_SwitchOff ();

  // Output Event Ports declaration
  int SA_RIGHT_Secondary_SwitchOff_prec;
  int SA_RIGHT_Secondary_SwitchOff_post;

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

// End class  orc_Mod_SA_RIGHT_Secondary_SwitchOff

