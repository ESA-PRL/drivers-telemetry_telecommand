
#include "module_PanCam_PIUSwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_PanCam_PIUSwitchOff::orc_Mod_PanCam_PIUSwitchOff (/*ModuleTask* mt,
							    int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_PanCam_WAC_L_SwitchOff", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_PanCam_WAC_L_SwitchOff constructor")
}

orc_Mod_PanCam_PIUSwitchOff::~orc_Mod_PanCam_PIUSwitchOff ()
{
  //  PRINT1( "** orc_Mod_PanCam_WAC_L_SwitchOff destructor" )
}

void orc_Mod_PanCam_PIUSwitchOff::param (char *params)
{

  fprintf (stderr, "PanCam_PIUSwitchOff:: param\n");
  
  /*
  int tmp1, tmp2;
  if (2 != sscanf(params, "%d %d", 
		  &tmp1,
		  &tmp2)) {
    std::cerr << "In PanCam_PIUSwitchOff param failed" << std::endl;
//    theRobotProcedure->ExitOnParamValueError(
//					     Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    return;
  }
  */
  //
  // the action status is ok
  //
  action_exec_status = ACTION_RET_OK;
  
  duration = 1.0;

}

void orc_Mod_PanCam_PIUSwitchOff::reparam (char *params)
{
  //  fprintf( stderr, "PanCam_WAC_L_SwitchOff:: reparam\n" );
  // #include   "PanCam_WAC_L_SwitchOff/user_code/reparam_code.c"
}

void orc_Mod_PanCam_PIUSwitchOff::init ()
{
  std::cerr << "-> PanCam_PIUSwitchOff: start init" << std::endl;
	//
	// if the action status is not ok (because of bad parameterisation
	// the code is not executed
	//
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In PanCam_PIUSwitchOff::init() action status = error\n");
	  //	  moduleSendEvent("PanCam_PIUSwitchOff_exc;");
	  return;
	 }

	//
	// reset the counter
	//
	index = 0;

	//
	// reset the events
	//
	PanCam_PIUSwitchOff_prec = NO_EVENT;
	PanCam_PIUSwitchOff_post = NO_EVENT;

	//
	// Reset the pancam state
	//
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  PanCamState[i] = 0.0;
	 }

	//
	// Get the Action id
	//
	rtId = 50; // Mt_ptr->GetRobotTaskPtr()->GetId();

	//
	// get the global state of the PanCam s/s to initialise the local variable
	//
	if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) PanCamState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"PanCamState");
	 }



	//
	// Set Action ID and Ret val
	//
	PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	PanCamState[PANCAM_OPER_MODE_INDEX]  = PANCAM_OPER_MODE_SWITCH_OFF;

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/


	//
	// set back the pancam state
	//
	if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) PanCamState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"PanCamState");
	 }


	//
	// Send the precondition event
	//
	PanCam_PIUSwitchOff_prec = SET_EVENT;
	//	moduleSendEvent("PanCam_PIUSwitchOff_prec;");

}

void orc_Mod_PanCam_PIUSwitchOff::compute ()
{
  //  std::cerr << "-> PanCam_WAC_L_SwitchOff: start compute" << std::endl;
	//
	// if the action status is not ok (because of bad parameterisation
	// the code is not executed
	//
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In PanCam_PIUSwitchOff::compute() action status = error\n");
	  //	  moduleSendEvent("PanCam_PIUSwitchOff_exc;");
	  return;
	 }

	//
	// Get the PanCam state
	//
	if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) PanCamState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"PanCamState");
	}

	//
	// Set Action ID and Ret val
	//
	PanCamState[PANCAM_ACTION_ID_INDEX]  = rtId;
	PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
	PanCamState[PANCAM_OPER_MODE_INDEX]  =  PANCAM_OPER_MODE_SWITCH_OFF;

	if (index >= (duration/theRobotProcedure->GetClock()->GetBasePeriod())) {
	//if (index == 10) {
	  PanCamState[PANCAM_OPER_MODE_INDEX] = PANCAM_OPER_MODE_OFF;
	  PanCamState[PANCAM_ACTION_ID_INDEX]  = 0;
	  PanCamState[PANCAM_ACTION_RET_INDEX] = ACTION_RET_OK;
	  //
	  // Send the post-condition
	  //
	  PanCam_PIUSwitchOff_post = SET_EVENT;
	  //	  moduleSendEvent("PanCam_PIUSwitchOff_post;");
	}

	//
	// update the resources of the robot task
	//
	/*
	double energy_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
	  PanCamState[PANCAM_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0;

	double memmass_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
	  PanCamState[PANCAM_DATARATE_INDEX]*getSampleTime();

	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();

	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/


	//
	// Set the PanCam state
	//
	if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) PanCamState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"PanCamState");
	}

	//
	// increase the counter
	//
	index ++;


}

void orc_Mod_PanCam_PIUSwitchOff::end ()
{
  fprintf( stderr, "PanCam_PIUSwitchOff:: End\n" );
	//
	// Reset the events
	//
	PanCam_PIUSwitchOff_prec = NO_EVENT;
	PanCam_PIUSwitchOff_post = NO_EVENT;


}

}

// End class orc_Mod_PanCam_WAC_L_SwitchOff

