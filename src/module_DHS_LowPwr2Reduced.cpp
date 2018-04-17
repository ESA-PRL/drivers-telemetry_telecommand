
#include "module_DHS_LowPwr2Reduced.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_DHS_LowPwr2Reduced::orc_Mod_DHS_LowPwr2Reduced (/*ModuleTask* mt,
					int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_DHS_LowPwr2Reduced", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_DHS_LowPwr2Reduced constructor")
}

orc_Mod_DHS_LowPwr2Reduced::~orc_Mod_DHS_LowPwr2Reduced ()
{
  //  PRINT1( "** orc_Mod_DHS_LowPwr2Reduced destructor" )
}

void orc_Mod_DHS_LowPwr2Reduced::param (char *params)
{

  //  fprintf (stderr, "DHS_LowPwr2Reduced:: param\n");

}

void orc_Mod_DHS_LowPwr2Reduced::reparam (char *params)
{
  //  fprintf( stderr, "DHS_LowPwr2Reduced:: reparam\n" );
  //  #include   "DHS_LowPwr2Reduced/user_code/reparam_code.c"
}

void orc_Mod_DHS_LowPwr2Reduced::init ()
{
  //  std::cerr << "-> DHS_LowPwr2Reduced: start init" << std::endl;

	// example code
	index = 0;

	DHS_LowPwr2Reduced_prec = NO_EVENT;
	DHS_LowPwr2Reduced_post = NO_EVENT;

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
	DHS_LowPwr2Reduced_prec = SET_EVENT;
	//	moduleSendEvent("DHS_LowPwr2Reduced_prec;");

}

void orc_Mod_DHS_LowPwr2Reduced::compute ()
{
  //  std::cerr << "-> DHS_LowPwr2Reduced: start compute" << std::endl; 

	// Get Action ID
  rtId = 14; //Mt_ptr->GetRobotTaskPtr()->GetId();


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

	// Set Action ID and Ret val

	if (index >= 10) {
	  // Set Action ID and Ret val
	  DHSState[DHS_STATUS_INDEX] = DHS_OPER_MODE_REDUCED;
	  // Set Action ID and Ret val
	  DHSState[DHS_ACTION_ID_INDEX] = 0;
	  DHSState[DHS_ACTION_RET_INDEX] = ACTION_RET_OK;

	  DHS_LowPwr2Reduced_post = SET_EVENT;
	  //	  moduleSendEvent("DHS_LowPwr2Reduced_post;");
	}


	//
	// set the global state
	//
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

void orc_Mod_DHS_LowPwr2Reduced::end ()
{
  //  fprintf( stderr, "DHS_LowPwr2Reduced:: End\n" );
	DHS_LowPwr2Reduced_prec = NO_EVENT;
	DHS_LowPwr2Reduced_post = NO_EVENT;

}

}

// End class orc_Mod_DHS_LowPwr2Reduced  

