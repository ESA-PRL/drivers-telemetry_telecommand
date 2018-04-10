#ifndef ORC_MOD_Deploy_RIGHT_SA_H
#define ORC_MOD_Deploy_RIGHT_SA_H
  
// #include "module.h"
  
#include "module_Deploy_RIGHT_SA_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_Deploy_RIGHT_SA // : public ModuleAlgo
{
 public:
	int index;
	double current_time;
	double duration;
	char taskid[124];
	public:
	char task_param[30][124];
	int rtId;


 public:
	orc_Mod_Deploy_RIGHT_SA (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_Deploy_RIGHT_SA ();

  // Output Event Ports declaration
  int Deploy_RIGHT_SA_prec;
int Deploy_RIGHT_SA_post;


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

// End class  orc_Mod_Deploy_RIGHT_SA

