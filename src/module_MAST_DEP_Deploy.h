#ifndef ORC_MOD_MAST_DEP_Deploy_H
#define ORC_MOD_MAST_DEP_Deploy_H

#include "module_MAST_DEP_Deploy_Inc.h"
//#include "module.h"


/** The model of the o/b controller */
namespace ControllerModelNamespace {

class orc_Mod_MAST_DEP_Deploy// : public ModuleAlgo
{
 public:


  // example code
	int index;

	// the Mast state
	double MastState[100];

    double maxRate;

	/** The motion mode between absolute (0) and relative (1) */
	int motionMode;
	int coordinatedMotion;

	/** */
	int currentMovingJoint;

	/** The initial joint position */
	double initPose[MAST_DOF];

	/** The final joint position */
	double finalPose[MAST_DOF];

	/** The joint speeds used to compute the traj duration */
	double jointTrajDuration[MAST_DOF];
	double jointMaxSpeed[MAST_DOF];

	/** The current time from 0 to the duration of the trajectory */
	double currentTime;

	/** The duration of the trajectory */
	double trajDuration;

	/** The current joint position in rad  */
	double currentPose[MAST_DOF];

	/** The ratio of the elapsed time with the total trajectory duration;
	    used to compute the trajectory profile */
	double tFracDur;

	/** The trajectory interpolation polynom */
	double rt;

	// the action id
	int rtId;

	// the action execution status
	int action_exec_status;

	// reference to the Mast PhR
	//orc_PhR_Mast *phrMast;

	int actionId;

//	ADEManagement adeManagement;

	void setActionId(int action_id) {
	  actionId = action_id;
	}


 public:
//  orc_Mod_MAST_DEP_Deploy (ModuleTask* mt, 
//			   ModuleTask* mt_ade_left, 
//			   ModuleTask* mt_ade_right, 
//			   int indexclk);
  orc_Mod_MAST_DEP_Deploy ();
  virtual ~orc_Mod_MAST_DEP_Deploy ();

  // Output Event Ports declaration
  int DMA_DEP_Deploy_prec;
  int DMA_DEP_Deploy_post;


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

// End class  orc_Mod_DMA_DEP_Deploy

