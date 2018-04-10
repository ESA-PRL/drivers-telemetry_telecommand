#ifndef ORC_MOD_SA_RIGHT_Primary_SwitchOff_H
#define ORC_MOD_SA_RIGHT_Primary_SwitchOff_H
  
// #include "module.h"
  
#include "module_SA_RIGHT_Primary_SwitchOff_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

 /**
   * \brief Implements the **SA_RIGHT_PrimarySwitchOff** Action. Switch OFF of RIGHT Solar Arrays primary hinges motor.
   */
  class orc_Mod_SA_RIGHT_Primary_SwitchOff // : public ModuleAlgo
{
 public:
	int rtId;     // Action Id
	int index;

	double SolarArrayState[MAX_STATE_SIZE];

 public:
	orc_Mod_SA_RIGHT_Primary_SwitchOff (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_SA_RIGHT_Primary_SwitchOff ();

 public:
  // Output Event Ports declaration
  int SA_RIGHT_Primary_SwitchOff_prec;
int SA_RIGHT_Primary_SwitchOff_post;


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

// End class  orc_Mod_SA_RIGHT_Primary_SwitchOff   

