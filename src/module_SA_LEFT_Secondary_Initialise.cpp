#include "module_SA_LEFT_Secondary_Initialise.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_SA_LEFT_Secondary_Initialise::orc_Mod_SA_LEFT_Secondary_Initialise (/*ModuleTask* mt,
									      int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_SA_LEFT_Secondary_Initialise", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_SA_LEFT_Secondary_Initialise constructor")
}

orc_Mod_SA_LEFT_Secondary_Initialise::~orc_Mod_SA_LEFT_Secondary_Initialise ()
{
  //  PRINT1( "** orc_Mod_SA_LEFT_Secondary_Initialise destructor" )
}

void orc_Mod_SA_LEFT_Secondary_Initialise::param (char *params)
{

   fprintf (stderr, "SA_LEFT_Secondary_Initialise:: param\n");
  //  fprintf (stderr, "SA_Left_PrimaryInit:: param\n");
  if (2 != sscanf(params, "%lf %lf", &timeout, &propDelay)) {
    fprintf(stderr, "In orc_Mod_SA_LEFT_Secondary_Initialise param failed\n");
    
    //    theRobotProcedure->ExitOnParamValueError(
    //					     Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), params);
    return;
  }
}

void orc_Mod_SA_LEFT_Secondary_Initialise::reparam (char *params)
{
  //  fprintf( stderr, "SA_LEFT_Secondary_Initialise:: reparam\n" );
 // #include   "SA_LEFT_Secondary_Initialise/user_code/reparam_code.c"
}

void orc_Mod_SA_LEFT_Secondary_Initialise::init ()
{
  std::cerr << "-> SA_LEFT_Secondary_Initialise: init" << std::endl;

	// example code
	index = 0;

	SA_LEFT_Secondary_Initialise_prec = NO_EVENT;
	SA_LEFT_Secondary_Initialise_post = NO_EVENT;
	//
	// get the global state to initialise the local variable
	//
	if ( theRobotProcedure->GetParameters()->get( "SolarArrayState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) SolarArrayState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"SolarArrayState");
	}

	// Get Action ID
	rtId = 88; //Mt_ptr->GetRobotTaskPtr()->GetId();

	SolarArrayState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_INIT; 
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
	  fprintf(stderr, "In SA_LEFT_Secondary_Initialise::init() SolarArrayState not found\n");
	}



	// Get Switch off time
	//switchOnTime = ((orc_PhR_SolarArray *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()))->PARAM_SA_WARMUP_TIME;
	switchOnTime = propDelay + SolarArrayState[SA_SEC_LEFT_WARMUP_TIME_INDEX];

	SA_LEFT_Secondary_Initialise_prec = SET_EVENT;
	//	moduleSendEvent("SA_LEFT_Secondary_Initialise_prec;");



}

void orc_Mod_SA_LEFT_Secondary_Initialise::compute ()
{
  //  std::cerr << "-> SA_LEFT_Secondary_Initialise: start compute" << std::endl;
	//
	// get the global state to initialise the local variable
	//
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


	// Check power availability if not trigger error
	if(false /*
	    (PowerState[ORC_POWER_SADE_RIGHT_N_LINE_INDEX] < minOpVoltage &&
	     PowerState[ORC_POWER_SADE_RIGHT_R_LINE_INDEX] < minOpVoltage) ||
	    (PowerState[ORC_POWER_SADE_LEFT_N_LINE_INDEX] < minOpVoltage &&
	     PowerState[ORC_POWER_SADE_LEFT_R_LINE_INDEX] < minOpVoltage) ||
	    (PowerState[ORC_HEATER_SADE_N_LINE_INDEX] < minOpVoltage &&
	    PowerState[ORC_HEATER_SADE_R_LINE_INDEX] < minOpVoltage) */)
	{

		// trigger errors
			// Set Action ID and Ret val
	  SolarArrayState[SA_ACTION_ID_INDEX]  = 0;
	  SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_ERROR;
	  SolarArrayState[ABORT_INDEX]  = rtId;
	  SolarArrayState[ABORT_ERROR_INDEX]  = 1;

	  fprintf(stderr, "In SA_LEFT_Secondary_Initialise::compute() no power available for operation!\n");

	  // send the post-condition
	  SA_LEFT_Secondary_Initialise_post = SET_EVENT;
	  //	  moduleSendEvent("SA_LEFT_Secondary_Initialise_post;");
	  // save the state
	  if ( theRobotProcedure->GetParameters()->set( "SolarArrayState", DOUBLE,
							MAX_STATE_SIZE, 0,
							( char * ) SolarArrayState ) == ERROR ) {
	    fprintf(stderr, "In SA_LEFT_Secondary_Initialise::compute() SolarArrayState not found\n");
	  }
	  // return
	  return;
	 }


	SolarArrayState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_INIT; 
	SolarArrayState[SA_ACTION_ID_INDEX]  = rtId;
	SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= switchOnTime/0.2) {
	  SolarArrayState[SA_LEFT_SECONDARY_STATUS_INDEX] = SA_OPER_MODE_STNDBY; 
	  // Set Action ID and Ret val
	  SolarArrayState[SA_ACTION_ID_INDEX]  = 0;
	  SolarArrayState[SA_ACTION_RET_INDEX] = ACTION_RET_OK;

	  // send the post-condition
	  SA_LEFT_Secondary_Initialise_post = SET_EVENT;
	  //	  moduleSendEvent("SA_LEFT_Secondary_Initialise_post;");
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

void orc_Mod_SA_LEFT_Secondary_Initialise::end ()
{
   fprintf( stderr, "SA_LEFT_Secondary_Initialise:: End\n" );
	SA_LEFT_Secondary_Initialise_prec = NO_EVENT;
	SA_LEFT_Secondary_Initialise_post = NO_EVENT;



}

}

// End class orc_Mod_SA_LEFT_Secondary_Initialise

