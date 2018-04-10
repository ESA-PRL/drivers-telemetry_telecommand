#ifndef ORC_MOD_GNC_MonitoringOnly_H
#define ORC_MOD_GNC_MonitoringOnly_H

//#include "module.h"

#include "module_GNC_MonitoringOnly_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  /**
   * \brief Implements the GNC_MonitoringOnly Action. 
   * Switches the GNC in the Monitoring Only State
   */
  class orc_Mod_GNC_MonitoringOnly // : public ModuleAlgo
{
 public:


	// counter for the move to logic
	int index;


	// the GNC state
	double Local_State[100];


	// the action execution status
	int action_exec_status;

	// the action id
	int rtId;

	double current_time;

	double action_duration;

	// reference to the phr GNC
	// orc_PhR_GNC* phr_GNC;


 public:
	orc_Mod_GNC_MonitoringOnly (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_GNC_MonitoringOnly ();

 public:
  // Output Event Ports declaration
  int GNC_MonitoringOnly_prec;
  int GNC_MonitoringOnly_post;


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

// End class  orc_Mod_GNC_MonitoringOnly

