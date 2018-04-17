#ifndef ORC_MOD_RV_SwitchOffTravel_H
#define ORC_MOD_RV_SwitchOffTravel_H
  
#include "module.h"
  
#include "module_RV_SwitchOffTravel_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

class orc_Mod_RV_SwitchOffTravel : public ModuleAlgo
{
 public:
	int index;
	double current_time;
	double duration;
	char taskid[124];
	public:
	char task_param[20][124];
	int rtId;


 public:
	orc_Mod_RV_SwitchOffTravel (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_RV_SwitchOffTravel ();

  // Output Event Ports declaration
  int RV_SwitchOffTravel_prec;
int RV_SwitchOffTravel_post;


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

// End class  orc_Mod_RV_SwitchOffTravel

