#include "module_SA_LEFT_Primary_MoveTo.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_SA_LEFT_Primary_MoveTo::orc_Mod_SA_LEFT_Primary_MoveTo (/*ModuleTask* mt,
								  int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_SA_LEFT_Primary_MoveTo", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_SA_LEFT_Primary_MoveTo constructor")
}

orc_Mod_SA_LEFT_Primary_MoveTo::~orc_Mod_SA_LEFT_Primary_MoveTo ()
{
  //  PRINT1( "** orc_Mod_SA_LEFT_Primary_MoveTo destructor" )
}

void orc_Mod_SA_LEFT_Primary_MoveTo::param (char *params)
{
    std::cerr << "SA_LEFT_Primary_MoveTo: param" << std::endl;
  if (1 != sscanf(params, "%lf", &tilt)) {
    //    theRobotProcedure->ExitOnParamValueError(
    //					     Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    return;
  }
  
  motionMode = 0;
  coordinatedMotion = 1;
}

void orc_Mod_SA_LEFT_Primary_MoveTo::reparam (char *params)
{
  //  fprintf( stderr, "SA_LEFT_Primary_MoveTo:: reparam\n" );
  // #include   "SA_LEFT_Primary_MoveTo/user_code/reparam_code.c"
}

void orc_Mod_SA_LEFT_Primary_MoveTo::init ()
{
    std::cerr << "-> SA_LEFT_Primary_MoveTo: start init" << std::endl;
  // reset the index
  index = 0;
  
  //
  // get the global state to initialise the local variable
  //
  if ( theRobotProcedure->GetParameters()->get( "SolarArrayState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) SolarArrayState ) == ERROR ) {
    //    theRobotProcedure->ExitOnMissingStateSymbol(
    //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
    //						"SolarArrayState");
  }

  //
  // check the preconditions
  //
  //	if ( SolarArrayState[SA_LEFT_PRIMARY_STATUS_INDEX] != SA_OPER_MODE_STNDBY ) {
  //  SolarArrayState[SA_ACTION_ID_INDEX]  = 0;
  //  SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_ERROR;
  //  SolarArrayState[ABORT_ERROR_INDEX]  = 3;
  //  SolarArrayState[ABORT_INDEX]  = rtId;
  //  fprintf(stderr, "In SA_LEFT_Primary_MoveTo::init() SA STATUS is not SA_OPER_MODE_STNDBY as expected\n");
  //  exit(1);
  //  return;
  //	 }

  rtId = 90;

  //
  // set the local variables
  //
  currentMovingJoint = 0;
  
  currentTime = 0.0; // sec
  for (int i = 0; i<SA_DOF; i++) {
    initPose[i] = SolarArrayState[SA_CURRENT_Q1_INDEX + i];
  }
  
  
  for (int i = 0; i<SA_DOF; i++) {
    currentPose[i] = initPose[i];
  }
  
  //
  // set the final pose wrt the motion mode
  //
  for (int i = 0; i<SA_DOF; i++) {
    finalPose[i] = currentPose[i];
  }
  finalPose[0] = tilt;
  
  
  //
  // Compute the duration of the motion with max speed
  //
  
  //
  // Units - meters/sec and deg/sec
  //
  trajDuration = 0.0;
  for (int i=0; i<SA_DOF; i++) {
    jointMaxSpeed[i] = 1.0; // ((orc_PhR_SolarArray *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()))->PARAM_SA_MAX_ROTATION_SPEED;
  }
  
  for (int i = 0; i<SA_DOF; i++) {
    
    jointTrajDuration[i] = (fabs (finalPose[i] - initPose[i]) ) / (jointMaxSpeed[i]);
    
    if (jointTrajDuration[i] > trajDuration) {
      trajDuration = jointTrajDuration[i];
    }
  }
  
  //
  // Publish the final desired position
  //
  for (int i = 0; i<SA_DOF; i++) {
    SolarArrayState[SA_DES_Q1_INDEX+i] = finalPose[i];
  }
  
  
  SolarArrayState[SA_TRAJ_DUR_INDEX]  = trajDuration;
  
  SolarArrayState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
  SolarArrayState[SA_ACTION_ID_INDEX]  = rtId;
  SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
  
  //
  // reset the resources of the robot task
  //
  /*
  getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
  getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
  getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
  */

  //
  // Set the state
  //
  if ( theRobotProcedure->GetParameters()->set( "SolarArrayState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) SolarArrayState ) == ERROR ) {
    //    theRobotProcedure->ExitOnMissingStateSymbol(
    //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
    //						"SolarArrayState");
  }
  
  //
  // Indicate that the preconditions are satisfied
  //
  SA_LEFT_Primary_MoveTo_prec = SET_EVENT;
  //  moduleSendEvent("SA_LEFT_Primary_MoveTo_prec;");
}
  
  void orc_Mod_SA_LEFT_Primary_MoveTo::compute ()
  {
    // std::cerr << "-> SA_LEFT_Primary_MoveTo: start compute" << std::endl;
    
    //
    // get the global state
    //
    if ( theRobotProcedure->GetParameters()->get( "SolarArrayState", DOUBLE,
						  MAX_STATE_SIZE, 0,
						  ( char * ) SolarArrayState ) == ERROR ) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //						  "SolarArrayState");
    }
    
    SolarArrayState[SA_ACTION_ID_INDEX]  = rtId;
    SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    //
    // during the trajectory duration
    //
    if (currentTime <= trajDuration) {
      
      // compute the interpolation polynom
      tFracDur = currentTime/trajDuration;
      rt = 10*tFracDur*tFracDur*tFracDur -
	15*tFracDur*tFracDur*tFracDur*tFracDur +
	6*tFracDur*tFracDur*tFracDur*tFracDur*tFracDur;
      
      // compute the desired joint position (deg)
      for (int i = 0; i<SA_DOF; i++) {
	currentPose[i] = initPose[i] + (rt) * (finalPose[i] - initPose[i]);
      }
      SolarArrayState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_MOVING;
      
      //	    setSAPosition(currentPose);
    }
    else {
      //
      // the duration of the trajectory ellapsed
      // indicate that the postcondition is satisfied
      //
      // Set Action ID and Ret val
      SolarArrayState[SA_ACTION_ID_INDEX]  = 0;
      SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      SA_LEFT_Primary_MoveTo_post = SET_EVENT;
      //moduleSendEvent("SA_LEFT_Primary_MoveTo_post;");
      //	    adeManagement.setPhaseADEDeactivate();
      // set the current pose at the final pose
      for (int i=0; i<SA_DOF; i++) {
	currentPose[i] = finalPose[i];
      }
      SolarArrayState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY;
    }
  
  

    /*
  double energy_cons =
    getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
  (SolarArrayState[SA_LEFT_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0);
  
  double memmass_cons =
    getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
  SolarArrayState[SA_LEFT_DATARATE_INDEX]*getSampleTime();
  
  double act_duration =
    getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
  
  
  getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
  getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
  getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

  //
  // set back to the mast state the computed values
  //
  
  SolarArrayState[SA_CURRENT_Q1_INDEX] = currentPose[0];
  SolarArrayState[SA_CURRENT_Q2_INDEX] = currentPose[1];
  SolarArrayState[SA_CURRENT_Q3_INDEX] = currentPose[2];
  SolarArrayState[SA_CURRENT_Q4_INDEX] = currentPose[3];
  
  SolarArrayState[SA_DES_Q1_INDEX] = finalPose[0];
  SolarArrayState[SA_DES_Q2_INDEX] = finalPose[1];
  SolarArrayState[SA_DES_Q3_INDEX] = finalPose[2];
  SolarArrayState[SA_DES_Q4_INDEX] = finalPose[3];
  
  
  //
  // update the global state
  //
  if ( theRobotProcedure->GetParameters()->set( "SolarArrayState", DOUBLE,
						MAX_STATE_SIZE, 0,
						( char * ) SolarArrayState ) == ERROR ) {
    //    theRobotProcedure->ExitOnMissingStateSymbol(
    //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
    //						"SolarArrayState");
  }
  
  
  
  index++;
  currentTime = currentTime + 0.2; // getSampleTime();
  
}

void orc_Mod_SA_LEFT_Primary_MoveTo::end ()
{
  fprintf( stderr, "SA_LEFT_Primary_MoveTo:: End\n" );
  SA_LEFT_Primary_MoveTo_prec = NO_EVENT;
  SA_LEFT_Primary_MoveTo_post = NO_EVENT;
  
  //	adeManagement.resetFlags();
  
  
}

}

// End class orc_Mod_SA_LEFT_Primary_MoveTo 

