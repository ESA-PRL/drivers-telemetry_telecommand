#ifndef ORC_MOD_Release_Body_H
#define ORC_MOD_Release_Body_H

#include "module.h"

#include "prr.h"

// #include "Release_Body/user_code/module_Release_Body_Inc.h"

#include "module_GNC_MonitoringOnly.h"
#include "module_ADE_ReleaseHDRM.h"
#include "module_GNC_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  // GNC_MonitoringOnly
  // ADE_ReleaseHDRM(0, 18) - HDRM_Release(18,2,0,120,200,0)
  // ADE_ReleaseHDRM(0, 19) - HDRM_Release(19,2,0,120,200,0)
  // ADE_ReleaseHDRM(0, 20) - HDRM_Release(20,2,0,120,200,0)
  // GNC_SwitchOff
class orc_Mod_Release_Body : public ModuleAlgo
{
 public:

	// example code
	int index;

	double RoverState[MAX_STATE_SIZE];


	double current_time;

	// the action execution status
	int action_exec_status;

	// the action id
	int rtId;

	orc_Mod_GNC_MonitoringOnly GNC_MonitoringOnly;
	orc_Mod_ADE_ReleaseHDRM    ADE_ReleaseHDRM;
	orc_Mod_GNC_SwitchOff      GNC_SwitchOff;

	int GNC_MonitoringOnly_phase;
	int ADE_ReleaseHDRM_0_18_phase;
	int ADE_ReleaseHDRM_0_19_phase;
	int ADE_ReleaseHDRM_0_20_phase;
	int GNC_SwitchOff_phase;

 public:
	orc_Mod_Release_Body (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_Release_Body ();

  // Output Event Ports declaration
  int Release_Body_prec;
  int Release_Body_post;

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

// End class  orc_Mod_Release_Body

