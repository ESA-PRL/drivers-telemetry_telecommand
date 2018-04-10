#ifndef ORC_MOD_SA_LEFT_Secondary_MoveTo_H
#define ORC_MOD_SA_LEFT_Secondary_MoveTo_H
  
// #include "module.h"
  
#include "module_SA_LEFT_Secondary_MoveTo_Inc.h"
// #include "ADEManagement.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {

 /**
   * \brief Implements the **SA_LEFT_Secondary_MoveTo** Action. Move LEFT Solar Arrays Secondary hinge motor.
   */
  class orc_Mod_SA_LEFT_Secondary_MoveTo // : public ModuleAlgo
{
 public:
	int rtId;     // Action Id
	int index;

	double tilt;

	// the SA state
	double SolarArrayState[MAX_STATE_SIZE];

	/** The motion mode between absolute (0) and relative (1) */
	int motionMode;
	int coordinatedMotion;

	/** */
	int currentMovingJoint;

	/** The initial joint position */
	double initPose[SA_DOF];

	/** The final joint position */
	double finalPose[SA_DOF];

	/** The joint speeds used to compute the traj duration */
	double jointTrajDuration[SA_DOF];
	double jointMaxSpeed[SA_DOF];

	/** The current time from 0 to the duration of the trajectory */
	double currentTime;

	/** The duration of the trajectory */
	double trajDuration;

	/** The current joint position in rad  */
	double currentPose[SA_DOF];

	/** The ratio of the elapsed time with the total trajectory duration;
	    used to compute the trajectory profile */
	double tFracDur;

	/** The trajectory interpolation polynom */
	double rt;

	//	ADEManagement adeManagement;

 public:
  orc_Mod_SA_LEFT_Secondary_MoveTo (/*ModuleTask* mt, 
				      int indexclk*/);
  virtual ~orc_Mod_SA_LEFT_Secondary_MoveTo ();

  // Output Event Ports declaration
  int SA_LEFT_Secondary_MoveTo_prec;
int SA_LEFT_Secondary_MoveTo_post;


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

// End class  orc_Mod_SA_LEFT_Secondary_MoveTo 

