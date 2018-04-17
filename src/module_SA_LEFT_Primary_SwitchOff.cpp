#include "module_SA_LEFT_Primary_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_SA_LEFT_Primary_SwitchOff::orc_Mod_SA_LEFT_Primary_SwitchOff (/*ModuleTask* mt,
									int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_SA_LEFT_Primary_SwitchOff", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_SA_LEFT_Primary_SwitchOff constructor")
}

orc_Mod_SA_LEFT_Primary_SwitchOff::~orc_Mod_SA_LEFT_Primary_SwitchOff ()
{
  //  PRINT1( "** orc_Mod_SA_LEFT_Primary_SwitchOff destructor" )
}

void orc_Mod_SA_LEFT_Primary_SwitchOff::param (char *params)
{

   fprintf (stderr, "SA_LEFT_Primary_SwitchOff:: param\n");
}

void orc_Mod_SA_LEFT_Primary_SwitchOff::reparam (char *params)
{
  //  fprintf( stderr, "SA_LEFT_Primary_SwitchOff:: reparam\n" );
 // #include   "SA_LEFT_Primary_SwitchOff/user_code/reparam_code.c"
}

void orc_Mod_SA_LEFT_Primary_SwitchOff::init ()
{
   std::cerr << "-> SA_LEFT_Primary_SwitchOff: start init" << std::endl;

	// example code
	index = 0;
	if ( theRobotProcedure->GetParameters()->get( "SolarArrayState", DOUBLE,
	                                              MAX_STATE_SIZE, 0,
	                                              ( char * ) SolarArrayState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"SolarArrayState");
	}


	// Get Action ID
	rtId = 89; //Mt_ptr->GetRobotTaskPtr()->GetId();
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

	if ( theRobotProcedure->GetParameters()->set( "SolarArrayState", DOUBLE,
	                                              MAX_STATE_SIZE, 0,
	                                              ( char * ) SolarArrayState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"SolarArrayState");
	}

	SA_LEFT_Primary_SwitchOff_post = NO_EVENT;
	SA_LEFT_Primary_SwitchOff_prec = SET_EVENT;

	//	moduleSendEvent("SA_LEFT_Primary_SwitchOff_prec;");

}

void orc_Mod_SA_LEFT_Primary_SwitchOff::compute ()
{
  //  std::cerr << "-> SA_LEFT_Primary_SwitchOff: start compute" << std::endl;
	if ( theRobotProcedure->GetParameters()->get( "SolarArrayState", DOUBLE,
	                                              MAX_STATE_SIZE, 0,
	                                              ( char * ) SolarArrayState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"SolarArrayState");
	}

	// Set Action ID and Ret val
	SolarArrayState[SA_ACTION_ID_INDEX]  = rtId;
	SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= 10) {
	  // Set Action ID and Ret val
	  SolarArrayState[SA_ACTION_ID_INDEX]  = 0;
	  SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;

	  SolarArrayState[SA_LEFT_PRIMARY_STATUS_INDEX] = SA_OPER_MODE_OFF;

	  SA_LEFT_Primary_SwitchOff_post = SET_EVENT;
	  //	  moduleSendEvent("SA_LEFT_Primary_SwitchOff_post;");
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

	if ( theRobotProcedure->GetParameters()->set( "SolarArrayState", DOUBLE,
	                                              MAX_STATE_SIZE, 0,
	                                              ( char * ) SolarArrayState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"SolarArrayState");
	}


	index ++;


}

void orc_Mod_SA_LEFT_Primary_SwitchOff::end ()
{
    fprintf( stderr, "SA_LEFT_Primary_SwitchOff:: End\n" );
	SA_LEFT_Primary_SwitchOff_prec = NO_EVENT;
	SA_LEFT_Primary_SwitchOff_post = NO_EVENT;


}

}

// End class orc_Mod_SA_LEFT_Primary_SwitchOff

