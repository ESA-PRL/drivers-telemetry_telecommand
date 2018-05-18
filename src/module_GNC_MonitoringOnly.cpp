
#include "module_GNC_MonitoringOnly.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_GNC_MonitoringOnly::orc_Mod_GNC_MonitoringOnly (/*ModuleTask* mt,
							  int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_GNC_MonitoringOnly", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_GNC_MonitoringOnly constructor")
}

orc_Mod_GNC_MonitoringOnly::~orc_Mod_GNC_MonitoringOnly ()
{
  //  PRINT1( "** orc_Mod_GNC_MonitoringOnly destructor" )
}

void orc_Mod_GNC_MonitoringOnly::param (char *params)
{

  // fprintf (stderr, "GNC_MonitoringOnly:: param\n");

    // the action status is ok
    action_exec_status = ACTION_RET_OK;

}

void orc_Mod_GNC_MonitoringOnly::reparam (char *params)
{
    fprintf( stderr, "GNC_MonitoringOnly:: reparam\n" );
    // #include   "GNC_MonitoringOnly/user_code/reparam_code.c"
}

void orc_Mod_GNC_MonitoringOnly::init ()
{
  //  std::cerr << "-> GNC_MonitoringOnly: start init" << std::endl;

	index = 0;
	GNC_MonitoringOnly_prec = NO_EVENT;
	GNC_MonitoringOnly_post = NO_EVENT;

	current_time = 0.0;

	// reset the wisdom and the gnc states
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  Local_State[i] = 0.0;
	 }


	if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) Local_State ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	}

	rtId = 61; // Mt_ptr->GetRobotTaskPtr()->GetId();

	action_duration = 2;

	current_time = 0.0;



	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) Local_State ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	GNC_MonitoringOnly_prec = SET_EVENT;
	//	moduleSendEvent("GNC_MonitoringOnly_prec;");




}

void orc_Mod_GNC_MonitoringOnly::compute ()
{
  //  std::cerr << "-> GNC_MonitoringOnly: start compute" << std::endl;

	index ++;

	if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) Local_State ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	}

	// Local_State[GNC_OPER_MODE_INDEX] = GNC_OPER_MODE_MONO;
	Local_State[GNC_ACTION_ID_INDEX]  = rtId;
	Local_State[GNC_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (current_time >= action_duration) {
	  Local_State[GNC_ACTION_ID_INDEX]  = 0;
	  Local_State[GNC_ACTION_RET_INDEX] = ACTION_RET_OK;
	  Local_State[GNC_OPER_MODE_INDEX]  = GNC_OPER_MODE_MONO;

	  GNC_MonitoringOnly_post = SET_EVENT;
	  //	  moduleSendEvent("GNC_MonitoringOnly_post;");
	 }

	current_time = current_time + 0.2; // getSampleTime();

	if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) Local_State ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"GNCState");
	 }


	/*
	double energy_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
	  Local_State[GNC_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0;

	double memmass_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
	  Local_State[GNC_DATARATE_INDEX]*getSampleTime();

	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();

	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/




}

void orc_Mod_GNC_MonitoringOnly::end ()
{
  // fprintf( stderr, "GNC_MonitoringOnly:: End\n" );


  GNC_MonitoringOnly_prec = NO_EVENT;
  GNC_MonitoringOnly_post = NO_EVENT;

}

}

// End class orc_Mod_GNC_MonitoringOnly

