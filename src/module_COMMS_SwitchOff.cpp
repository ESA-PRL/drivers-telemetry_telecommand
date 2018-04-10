
#include "module_COMMS_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

orc_Mod_COMMS_SwitchOff::orc_Mod_COMMS_SwitchOff (/*ModuleTask* mt,
						    int indexclk*/)
// : ModuleAlgo ("orc_Mod_COMMS_SwitchOff", mt, indexclk)
{
  //  PRINT1("** orc_Mod_COMMS_SwitchOff constructor")
}

orc_Mod_COMMS_SwitchOff::~orc_Mod_COMMS_SwitchOff ()
{
  //  PRINT1( "** orc_Mod_COMMS_SwitchOff destructor" )
}

void orc_Mod_COMMS_SwitchOff::param (char *params)
{

  // fprintf (stderr, "COMMS_SwitchOff:: param\n");


	if (1 != sscanf(params, "%s", unitid)) {
	  fprintf(stderr, "In COMMS_SwitchOff param failed\n");
	  //		theRobotProcedure->ExitOnParamValueError(
	  //				Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
		return;
	 }



}

void orc_Mod_COMMS_SwitchOff::reparam (char *params)
{
  //  fprintf( stderr, "COMMS_SwitchOff:: reparam\n" );
// #include   "COMMS_SwitchOff/user_code/reparam_code.c"
}

void orc_Mod_COMMS_SwitchOff::init ()
{
  //  std::cerr << "-> COMMS_SwitchOff: start init" << std::endl;

	// example code
	index = 0;

	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  CommsState[i] = 0.0;
	 }
	COMMS_SwitchOff_prec = NO_EVENT;
	COMMS_SwitchOff_post = NO_EVENT;

	// Get Action ID
	rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();


	if ( theRobotProcedure->GetParameters()->get( "CommsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) CommsState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"CommsState");
	 }

	if (!strcmp(unitid, "MAIN")) {
	  cmd_index = COMMS_MAIN_CMD_INDEX;
	  status_index = COMMS_MAIN_STATUS_INDEX;
	  final_state = ORC_COMMS_STATE_OFF;
	 }
	 else if (!strcmp(unitid, "REDUNDANT")) {
	   cmd_index = COMMS_REDUNDANT_CMD_INDEX;
	   status_index = COMMS_REDUNDANT_STATUS_INDEX;
	   final_state = ORC_COMMS_STATE_OFF;
	 }
	 else {
	   cmd_index = COMMS_MAIN_CMD_INDEX;
	   status_index = COMMS_MAIN_STATUS_INDEX;
	   final_state = ORC_COMMS_STATE_OFF;
	   //		theRobotProcedure->ExitOnParamValueError(
	   //				Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), unitid);
	 }

	cmd_id = ORC_TC_OFF;


	CommsState[COMMS_ACTION_ID_INDEX]  = rtId;
	CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	if ( theRobotProcedure->GetParameters()->set( "CommsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) CommsState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"CommsState");
	 }

	COMMS_SwitchOff_prec = SET_EVENT;
	//	moduleSendEvent("COMMS_SwitchOff_prec;");
	
}

void orc_Mod_COMMS_SwitchOff::compute ()
{
  //  std::cerr << "-> COMMS_SwitchOff: start compute" << std::endl;

	// Get Action ID
  rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();

	//
	// get the global state
	//
	if ( theRobotProcedure->GetParameters()->get( "CommsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) CommsState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"CommsState");
	 }

	// Set Action ID and Ret val
	CommsState[COMMS_ACTION_ID_INDEX]  = rtId;
	CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	// example code
	if (index > 10) {

	  CommsState[status_index]  = final_state;
	  
	  CommsState[COMMS_ACTION_ID_INDEX] = 0;
	  CommsState[COMMS_ACTION_RET_INDEX] = ACTION_RET_OK;

	  COMMS_SwitchOff_post = SET_EVENT;
	  //	  moduleSendEvent("COMMS_SwitchOff_post;");
	}

	/*
	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/
	//
	// set the global state
	//
	if ( theRobotProcedure->GetParameters()->set( "CommsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) CommsState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"CommsState");
	 }

	index ++;

}

void orc_Mod_COMMS_SwitchOff::end ()
{
  //  fprintf( stderr, "COMMS_SwitchOff:: End\n" );
	COMMS_SwitchOff_prec = NO_EVENT;
	COMMS_SwitchOff_post = NO_EVENT;


}

}

// End class orc_Mod_COMMS_SwitchOff

