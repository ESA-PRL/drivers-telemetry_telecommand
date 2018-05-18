#ifndef ORC_MOD_GNC_AbsLocalisation_H
#define ORC_MOD_GNC_AbsLocalisation_H

#include "module.h"

#include "module_GNC_AbsLocalisation_Inc.h"

class orc_ProcRoverCtrl;

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  /**
   * \brief Implements the **GNC_AbsLocalisation** Action. Absolute gravity update (absolute Roll and Pitch estimation based on IMU-accelerometers measures). No heading estimation (absolute Yaw not estimated).
   */
class orc_Mod_GNC_AbsLocalisation : public ModuleAlgo
{
 public:


	// counter for the move to logic
	int index;

	// the GNC state
	double GNCState[MAX_STATE_SIZE];

	// the action execution status
	int action_exec_status;

	// the action id
	int rtId;

	double action_duration;

	// reference to the phr GNC
	//	orc_PhR_GNC* phr_GNC;



 public:
	orc_Mod_GNC_AbsLocalisation (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_GNC_AbsLocalisation ();

 public:
  // Output Event Ports declaration
  int GNC_AbsLocalisation_prec;
  int GNC_AbsLocalisation_post;


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

// End class  orc_Mod_GNC_AbsLocalisation

