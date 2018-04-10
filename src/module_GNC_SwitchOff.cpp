
#include "module_GNC_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_GNC_SwitchOff::orc_Mod_GNC_SwitchOff (/*ModuleTask* mt,
						int indexclk*/)
//  : ModuleAlgo ("orc_Mod_GNC_SwitchOff", mt, indexclk)
{
  //  PRINT1("** orc_Mod_GNC_SwitchOff constructor")
}

orc_Mod_GNC_SwitchOff::~orc_Mod_GNC_SwitchOff ()
{
  //  PRINT1( "** orc_Mod_GNC_SwitchOff destructor" )
}

void orc_Mod_GNC_SwitchOff::param (char *params)
{

  //  fprintf (stderr, "GNC_SwitchOff:: param\n");

	// the action status is ok
	action_exec_status = ACTION_RET_OK;

}

void orc_Mod_GNC_SwitchOff::reparam (char *params)
{
  //  fprintf( stderr, "GNC_SwitchOff:: reparam\n" );
  // #include   "GNC_SwitchOff/user_code/reparam_code.c"
}

void orc_Mod_GNC_SwitchOff::init ()
{
  //  std::cerr << "-> GNC_SwitchOff: start init" << std::endl;

	// if the action status is not ok the code is not executed
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In GNC_SwitchOff::init() action status = error\n");
	  return;
	 }

	// reset the counters
	index = 0;

	// reset the events
	GNC_SwitchOff_prec = NO_EVENT;
	GNC_SwitchOff_post = NO_EVENT;

	// reset the power and the gnc states
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  GNCState[i] = 0.0;
	 }

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	// get the reference to the GNC phr
	/*
	phr_GNC = (orc_PhR_GNC*)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ());
	if ( phr_GNC == NULL) {
	  std::cerr << " In GNC_SwitchOff GNC Physical Resource not identified" << std::endl;
	  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_ERROR;
	  GNCState[ABORT_INDEX]          = ACTION_RET_ERROR;
	  // set the actions status
	  action_exec_status = ACTION_RET_ERROR;
	  return;
	 }
	*/
	// get the action Id
	rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();


	//
	// check the state of the gnc; it shall be at stndby mode
	//
	if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) GNCState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }

	// set action execution information
	GNCState[GNC_ACTION_ID_INDEX]  = rtId;
	GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

	//
	// if the state of the GNC is not at OFF
	// we abort the simulation
	//

	current_time = 0.0;
	action_duration = 2.0; //((orc_PhR_GNC*)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()))->PARAM_GNC_OPER_MODE_INITIALISING_DURATION;

	// set action execution information
	GNCState[GNC_ACTION_ID_INDEX]  = rtId;
	GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;



	if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) GNCState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }

	//
	// the preconditions are satisfied
	//
	GNC_SwitchOff_prec = SET_EVENT;
	//	moduleSendEvent("GNC_SwitchOff_prec;");



}

void orc_Mod_GNC_SwitchOff::compute ()
{
  //  std::cerr << "-> GNC_SwitchOff: start compute" << std::endl;
	// if the action status is not ok the code is not executed
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In GNC_SwitchOff::compute() action status = error\n");
	  return;
	 }

	//
	// get the global state of the GNC
	//
	if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) GNCState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	}

	// set action execution information
	GNCState[GNC_ACTION_ID_INDEX]  = rtId;
	GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= (action_duration/0.2)) {
	  //if (current_time > action_duration) {

	  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_OFF;

	  // Set Action ID and Ret val
	  GNCState[GNC_ACTION_ID_INDEX] = 0;
	  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;

	  GNC_SwitchOff_post = SET_EVENT;
	  //	  moduleSendEvent("GNC_SwitchOff_post;");

	 }

	//
	// update the resources of the robot task
	//
	/*
	double energy_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
	  GNCState[GNC_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0;

	double memmass_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
	  GNCState[GNC_DATARATE_INDEX]*getSampleTime();

	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();

	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/




	//
	// set the global state
	//
	if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) GNCState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }


	index ++;
	current_time = current_time + 0.2; //getSampleTime();



}

void orc_Mod_GNC_SwitchOff::end ()
{
  //  fprintf( stderr, "GNC_SwitchOff:: End\n" );


	// reset the events

	GNC_SwitchOff_prec = NO_EVENT;
	GNC_SwitchOff_post = NO_EVENT;

}

}

// End class orc_Mod_GNC_SwitchOff

