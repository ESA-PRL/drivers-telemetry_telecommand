
#include "module_DHS_Reduced2Nominal.h"
 
/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_DHS_Reduced2Nominal::orc_Mod_DHS_Reduced2Nominal (/*ModuleTask* mt,
							    int indexclk*/)
//  : ModuleAlgo ("orc_Mod_DHS_Reduced2Nominal", mt, indexclk)
{
  //  PRINT1("** orc_Mod_DHS_Reduced2Nominal constructor")
}

orc_Mod_DHS_Reduced2Nominal::~orc_Mod_DHS_Reduced2Nominal ()
{
  //  PRINT1( "** orc_Mod_DHS_Reduced2Nominal destructor" )
}

void orc_Mod_DHS_Reduced2Nominal::param (char *params)
{

  //  fprintf (stderr, "DHS_Reduced2Nominal:: param\n");


	strcpy(target_mode, "nominal");

}
 
void orc_Mod_DHS_Reduced2Nominal::reparam (char *params)
{
  //  fprintf( stderr, "DHS_Reduced2Nominal:: reparam\n" );
  //  #include   "DHS_Reduced2Nominal/user_code/reparam_code.c"
}

void orc_Mod_DHS_Reduced2Nominal::init ()
{
  //  std::cerr << "-> DHS_Reduced2Nominal: start init" << std::endl;

	// example code
	index = 0;

	DHS_Reduced2Nominal_prec = NO_EVENT;
	DHS_Reduced2Nominal_post = NO_EVENT;

	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  DHSState[i] = 0.0;
	 }

	//
	// get the global state
	//
	if ( theRobotProcedure->GetParameters()->get( "DhsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) DHSState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"DhsState");
	 }

	//
	// check the preconditions
	//


	//
	// Identify the duration function of the target mode.
	// The target modes are: reduced, nominal, highpower,
	// lowpower, recovery
	//
	if (!strcmp(target_mode, "reduced")) {
	  duration = 2.0; // sec CL20170109 WAS 1.0
	  target_mode_id = DHS_OPER_MODE_REDUCED;
	 }
	 else if (!strcmp(target_mode, "nominal")) {
	  duration = 2.0; // sec CL20170109 WAS 1.0
	  target_mode_id = DHS_OPER_MODE_NOMINAL;
	 }
	 else if (!strcmp(target_mode, "highpower")) {
	  duration = 2.0; // sec CL20170109 WAS 1.0
	  target_mode_id = DHS_OPER_MODE_HIGHPOWER;
	 }
	 else if (!strcmp(target_mode, "lowpower")) {
	  duration = 2.0; // sec CL20170109 WAS 1.0
	  target_mode_id = DHS_OPER_MODE_LOWPOWER;
	 }
	 else {

	   //			theRobotProcedure->ExitOnParamValueError(
	   //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), target_mode);
	   //
	 }

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	//
	// Indicate that the preconditions are satisfied
	//
	DHS_Reduced2Nominal_prec = SET_EVENT;
	//	moduleSendEvent("DHS_Reduced2Nominal_prec;");

}

void orc_Mod_DHS_Reduced2Nominal::compute ()
{
  //  std::cerr << "-> DHS_Reduced2Nominal: start compute" << std::endl;

	// Get Action ID
  rtId = 0; //Mt_ptr->GetRobotTaskPtr()->GetId();


	//
	// get the global state
	//
	if ( theRobotProcedure->GetParameters()->get( "DhsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) DHSState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"DhsState");
	}

	// Set Action ID and Ret val
	DHSState[DHS_ACTION_ID_INDEX]  = rtId;
	DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= (duration/0.2))
	{
	  DHSState[DHS_STATUS_INDEX] = target_mode_id;
	  // Set Action ID and Ret val
	  DHSState[DHS_ACTION_ID_INDEX] = 0;
	  DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;

	  DHS_Reduced2Nominal_post = SET_EVENT;
	  //	  moduleSendEvent("DHS_Reduced2Nominal_post;");
	}


	//
	// set the global state
	//
	if ( theRobotProcedure->GetParameters()->set( "DhsState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) DHSState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"DhsState");
	}

	/*
	double energy_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
	  (DHSState[DHS_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0);

	double memmass_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
	  DHSState[DHS_DATARATE_INDEX]*getSampleTime();

	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();

	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/

	index ++;


}

void orc_Mod_DHS_Reduced2Nominal::end ()
{
  //  fprintf( stderr, "DHS_Reduced2Nominal:: End\n" );
	DHS_Reduced2Nominal_prec = NO_EVENT;
	DHS_Reduced2Nominal_post = NO_EVENT;

}

}

// End class orc_Mod_DHS_Reduced2Nominal  

