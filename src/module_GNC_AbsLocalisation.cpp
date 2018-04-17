
#include "module_GNC_AbsLocalisation.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_GNC_AbsLocalisation::orc_Mod_GNC_AbsLocalisation (/*ModuleTask* mt,
							    int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_GNC_AbsLocalisation", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_GNC_AbsLocalisation constructor")
}

orc_Mod_GNC_AbsLocalisation::~orc_Mod_GNC_AbsLocalisation ()
{
  //  PRINT1( "** orc_Mod_GNC_AbsLocalisation destructor" )
}

void orc_Mod_GNC_AbsLocalisation::param (char *params)
{

    fprintf (stderr, "GNC_AbsLocalisation:: param\n");

	// the action status is ok
	action_exec_status = ACTION_RET_OK;


}

void orc_Mod_GNC_AbsLocalisation::reparam (char *params)
{
  //  fprintf( stderr, "GNC_AbsLocalisation:: reparam\n" );
  // #include   "GNC_AbsLocalisation/user_code/reparam_code.c"
}

void orc_Mod_GNC_AbsLocalisation::init ()
{
    std::cerr << "-> GNC_AbsLocalisation: start init" << std::endl;

	// if the action status is not ok the code is not executed
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In GNC_AbsLocalisation::init() action status = error\n");
	  return;
	 }

	// reset the counters
	index = 0;

	// reset the events
	GNC_AbsLocalisation_prec = NO_EVENT;
	GNC_AbsLocalisation_post = NO_EVENT;

	// reset the wisdom and the gnc states
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

	/*
	// get the reference to the GNC phr
	phr_GNC = (orc_PhR_GNC*)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ());
	if ( phr_GNC == NULL) {
	  std::cerr << " In GNC_AbsLocalisation GNC Physical Resource not identified" << std::endl;
	  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_ERROR;
	  GNCState[ABORT_INDEX]          = ACTION_RET_ERROR;
	  // set the actions status
	  action_exec_status = ACTION_RET_ERROR;
	  return;
	 }
	*/

	// get the action Id
	rtId = 63; // Mt_ptr->GetRobotTaskPtr()->GetId();

	action_duration = 10.0; // ((orc_PhR_GNC*)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()))->PARAM_GNC_OPER_MODE_ABS_LOC_DURATION;

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

	/*
	if ( GNCState[GNC_OPER_MODE_INDEX]  != GNC_OPER_MODE_STNDBY ) {
	  std::cerr << "In GNC_AbsLocalisation::init() GNC mode = "
		    << GNCState[GNC_OPER_MODE_INDEX]
		    << " - expected GNC_OPER_MODE_STNDBY"
		    << std::endl;

	  phr_GNC->stateTransitionError(GNCState[GNC_OPER_MODE_INDEX],
			  	  	  	  	  	  	GNC_OPER_MODE_STNDBY,
									(char*)getModuleTaskPtr()->GetRobotTaskPtr()->GetMnemonic().c_str());
	  theRobotProcedure->ExitOnInitialStateError();
	 }
	*/


	// set action execution information
	GNCState[GNC_ACTION_ID_INDEX]  = rtId;
	GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
	GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_ABS_LOC;


	if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) GNCState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }

	// reset the msg char array
	//	memset(messageto3d, 0, sizeof(messageto3d));

	//
	// the preconditions are satisfied
	//
	GNC_AbsLocalisation_prec = SET_EVENT;
	//	moduleSendEvent("GNC_AbsLocalisation_prec;");



}

void orc_Mod_GNC_AbsLocalisation::compute ()
{
  // std::cerr << "-> GNC_AbsLocalisation: start compute" << std::endl;

	// if the action status is not ok the code is not executed
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In GNC_AbsLocalisation::compute() action status = error\n");
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

	if (index >= (action_duration/theRobotProcedure->GetClock()->GetBasePeriod())) {
	  //if (index < 10) {

	  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_STNDBY;

	  // Set Action ID and Ret val
	  GNCState[GNC_ACTION_ID_INDEX] = 0;
	  GNCState[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;

	  GNC_AbsLocalisation_post = SET_EVENT;
	  //	  moduleSendEvent("GNC_AbsLocalisation_post;");


	 }
	 else {

	  GNCState[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_ABS_LOC;
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




}

void orc_Mod_GNC_AbsLocalisation::end ()
{
  fprintf( stderr, "GNC_AbsLocalisation:: End\n" );

	// reset the events
	GNC_AbsLocalisation_prec = NO_EVENT;
	GNC_AbsLocalisation_post = NO_EVENT;

}

}

// End class orc_Mod_GNC_AbsLocalisation

