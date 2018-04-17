#ifndef ORC_MOD_ADEs_DeActivate_H
#define ORC_MOD_ADEs_DeActivate_H
  
#include "module.h"
  
#include "module_ADEs_DeActivate_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_ADEs_DeActivate : public ModuleAlgo
{
 public:
	int index;
	double current_time;
	double duration;
	char taskid[124];
	public:
	char task_param[20][124];
	int rtId;

	double AdeState[MAX_STATE_SIZE]; // KK

 public:
	orc_Mod_ADEs_DeActivate (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_ADEs_DeActivate ();

  // Output Event Ports declaration
  int ADEs_DeActivate_prec;
int ADEs_DeActivate_post;


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

// End class  orc_Mod_ADEs_DeActivate 

