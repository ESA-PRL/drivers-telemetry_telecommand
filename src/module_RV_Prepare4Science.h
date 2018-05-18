#ifndef ORC_MOD_RV_Prepare4Science_H
#define ORC_MOD_RV_Prepare4Science_H
  
#include "module.h"
  
#include "module_RV_Prepare4Science_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

class orc_Mod_RV_Prepare4Science : public ModuleAlgo
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
	orc_Mod_RV_Prepare4Science (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_RV_Prepare4Science ();

  // Output Event Ports declaration
  int RV_Prepare4Science_prec;
int RV_Prepare4Science_post;


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

// End class  orc_Mod_RV_Prepare4Science

