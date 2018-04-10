#ifndef ORC_MOD_SA_RIGHT_Primary_Initialise_H
#define ORC_MOD_SA_RIGHT_Primary_Initialise_H
  
// #include "module.h"
  
#include "module_SA_RIGHT_Primary_Initialise_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

 /**
   * \brief Implements the **SA_RIGHT_PrimaryInitialise** Action. Warm up and switch ON of RIGHT Solar Arrays primary hinges motor.
   */
  class orc_Mod_SA_RIGHT_Primary_Initialise // : public ModuleAlgo
{
 public:
	int rtId;     // Action Id
	int index;

	double SolarArrayState[MAX_STATE_SIZE];
	// includes power system information
	double PowerState[MAX_STATE_SIZE];

	char sa_type[80]; //  primary / secondary
	char sa_position[80]; // left / right

	// voltage has been identified on the line
	double minOpVoltage;
	double switchOnTime;
	double timeout;
	double propDelay;

 public:
	orc_Mod_SA_RIGHT_Primary_Initialise (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_SA_RIGHT_Primary_Initialise ();

 public:
  // Output Event Ports declaration
  int SA_RIGHT_Primary_Initialise_prec;
int SA_RIGHT_Primary_Initialise_post;


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

// End class  orc_Mod_SA_RIGHT_Primary_Initialise

