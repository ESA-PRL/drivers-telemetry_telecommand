#ifndef ORC_MOD_ADE_ReleaseHDRM_H
#define ORC_MOD_ADE_ReleaseHDRM_H

#include "module.h"

#include "module_ADE_ReleaseHDRM_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

class orc_Mod_ADE_ReleaseHDRM : public ModuleAlgo
{
 public:
	int rtId;

	int index;

	double AdeState[MAX_STATE_SIZE];

	int adeId;

	int hdrmId;

	double current_time;

	double duration;

	//	orc_PhR_Ade* PhR_Ade;

 public:
	orc_Mod_ADE_ReleaseHDRM (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_ADE_ReleaseHDRM ();

  // Output Event Ports declaration
  int ADE_ReleaseHDRM_prec;
  int ADE_ReleaseHDRM_post;


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

// End class  orc_Mod_ADE_ReleaseHDRM

