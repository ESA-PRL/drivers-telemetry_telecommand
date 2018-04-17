#ifndef ORC_MOD_DHS_Reduced2LowPwr_H
#define ORC_MOD_DHS_Reduced2LowPwr_H

#include "module.h"

#include "module_DHS_Reduced2LowPwr_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_DHS_Reduced2LowPwr : public ModuleAlgo
{
 public:
	int rtId;     //Action Id

	int index;

	// includes power system information
	double DHSState[MAX_STATE_SIZE];

	char target_mode[256];

	int target_mode_id;

	double duration;





 public:
	orc_Mod_DHS_Reduced2LowPwr (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_DHS_Reduced2LowPwr ();

  // Output Event Ports declaration
  int DHS_Reduced2LowPwr_prec;
  int DHS_Reduced2LowPwr_post;

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

// End class  orc_Mod_DHS_Reduced2LowPwr

