#ifndef ORC_MOD_Release_Umbilical_H
#define ORC_MOD_Release_Umbilical_H

#include "module.h"
//#include "PhR_Rover.h"

#include "module_Release_Umbilical_Inc.h"

#include "module_GNC_MonitoringOnly.h"
#include "module_ADE_ReleaseHDRM.h"
#include "module_GNC_SwitchOff.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  // GNC_MonitoringOnly
  // HDRM_Release(10,4,0,120,200,0) 
  // HDRM_Release(11,4,0,120,200,0)
  // GNC_SwitchOff
class orc_Mod_Release_Umbilical : public ModuleAlgo
{
 public:

	// example code
	int index;

	//	orc_PhR_Rover *phrRover;
 
	double RoverState[MAX_STATE_SIZE];

	// the action execution status
	int action_exec_status;

	// the action id
	int rtId;

	orc_Mod_GNC_MonitoringOnly GNC_MonitoringOnly;
	orc_Mod_ADE_ReleaseHDRM    ADE_ReleaseHDRM;
	orc_Mod_GNC_SwitchOff      GNC_SwitchOff;

	int GNC_MonitoringOnly_phase;
	int ADE_ReleaseHDRM_0_10_phase;
	int ADE_ReleaseHDRM_0_11_phase;
	int GNC_SwitchOff_phase;

 public:
	orc_Mod_Release_Umbilical (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_Release_Umbilical ();

  // Output Event Ports declaration
  int Release_Umbilical_prec;
  int Release_Umbilical_post;

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

// End class  orc_Mod_Release_Umbilical

