#ifndef ORC_MOD_MAST_PAN_MoveTo_H
#define ORC_MOD_MAST_PAN_MoveTo_H

#include "module.h"

#include "module_MAST_PAN_MoveTo_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

  class orc_Mod_MAST_PAN_MoveTo : public ModuleAlgo
  {
  public:
    
    /** A counter */
    int index;
    
    /** To get and set the mast state */
    double MastState[MAX_STATE_SIZE];
    
    /** The motion mode between absolute (0) and relative (1) */
    int motionMode;
    
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
    //    orc_PhR_Mast *phrMast;
    
    // 
    int actionId;
    
    //	ADEManagement adeManagement;
    
    void setActionId(int action_id) {
      actionId = action_id;
    }
    
    
  public:
    orc_Mod_MAST_PAN_MoveTo (/*ModuleTask* mt,  
			       int indexclk*/);
    virtual ~orc_Mod_MAST_PAN_MoveTo ();
    
    // Output Event Ports declaration
    int MAST_PAN_MoveTo_prec; 
    int MAST_PAN_MoveTo_post;
    
    
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

// End class  orc_Mod_MAST_PAN_MoveTo

