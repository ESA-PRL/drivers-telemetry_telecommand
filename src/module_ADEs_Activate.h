#ifndef ORC_MOD_ADEs_Activate_H
#define ORC_MOD_ADEs_Activate_H
  
#include "module.h"
  
#include "module_ADEs_Activate_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_ADEs_Activate : public ModuleAlgo
{
 public:
	int index;

	double AdeState[MAX_STATE_SIZE]; // KK

	double current_time;
	double duration;
	char taskid[124];
	public:
	char task_param[20][124];
	int rtId;


 public:
	orc_Mod_ADEs_Activate (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_ADEs_Activate ();

  // Output Event Ports declaration
  int ADEs_Activate_prec;
int ADEs_Activate_post;


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

// End class  orc_Mod_ADEs_Activate

