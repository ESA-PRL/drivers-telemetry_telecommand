#ifndef ORC_MOD_Deploy_Mast_H
#define ORC_MOD_Deploy_Mast_H
  
// #include "module.h"
  
#include "module_Deploy_Mast_Inc.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_Deploy_Mast //: public ModuleAlgo
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
	orc_Mod_Deploy_Mast (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_Deploy_Mast ();

  // Output Event Ports declaration
  int Deploy_Mast_prec;
int Deploy_Mast_post;


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

// End class  orc_Mod_Deploy_Mast

