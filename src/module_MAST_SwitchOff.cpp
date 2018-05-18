
#include "module_MAST_SwitchOff.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


//orc_Mod_MAST_SwitchOff::orc_Mod_MAST_SwitchOff (ModuleTask* mt,
//					int indexclk)
//  : ModuleAlgo ("orc_Mod_DMA_SwitchOff", mt, indexclk)
  orc_Mod_MAST_SwitchOff::orc_Mod_MAST_SwitchOff (): ModuleAlgo ()
{
  //  PRINT1("** orc_Mod_DMA_SwitchOff constructor")
}

orc_Mod_MAST_SwitchOff::~orc_Mod_MAST_SwitchOff ()
{
  //  PRINT1( "** orc_Mod_DMA_SwitchOff destructor" )
}

void orc_Mod_MAST_SwitchOff::param (char *params)
{

  //  fprintf (stderr, "DMA_SwitchOff: param\n");

    if (1 != sscanf(params, "%d", &targetMechanism)) {
      
      MastState[ABORT_INDEX] = ACTION_RET_ERROR;
      //      MastState[ABORT_ERROR_INDEX] = MAST_PARAMETERISATION_ERROR;
      //      getModuleTaskPtr()->GetRobotTaskPtr()->setError(RT_EXEC_WRONG_PARAMS);
      
      //      theRobotProcedure->
      //	ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //			      params);
      return;
    }

    // the action status is ok
    action_exec_status = ACTION_RET_OK;
    //    getModuleTaskPtr()->GetRobotTaskPtr()->setError(RT_EXEC_NO_ERROR);

}

void orc_Mod_MAST_SwitchOff::reparam (char *params)
{
  //  fprintf( stderr, "DMA_SwitchOff: reparam\n" );
  // #include   "DMA_SwitchOff/user_code/reparam_code.c"
}

void orc_Mod_MAST_SwitchOff::init ()
{
  // std::cerr << "DMA_SwitchOff: init" << std::endl;

	// reset the counter
	index = 0;

	// reset the events
	DMA_SwitchOff_prec = NO_EVENT;
	DMA_SwitchOff_post = NO_EVENT;

	// reset the mast state
	for (int i=0; i<MAX_STATE_SIZE; i++) {
	  MastState[i] = 0.0;
	 }

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	// get the action Id
	rtId = 33; // Mt_ptr->GetRobotTaskPtr()->GetId();

	// get the duration of the Activity
	//	phrMast = ((orc_PhR_Mast *)(Mt_ptr->GetRobotTaskPtr () -> GetPhR ()));
	duration = 1.0;
	/*
	 * Get the MastState variable
	 */
	if ( theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						     MAX_STATE_SIZE, 0,
						     ( char * ) MastState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"MastState");
	 }

	MastState[MAST_ACTION_ID_INDEX]  = rtId;
	MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;

	//
	// set the mast state
	//
	if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) MastState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"MastState");
	 }

	// consider the pre-conditions satisfied
	DMA_SwitchOff_prec = SET_EVENT;
	//	moduleSendEvent("DMA_SwitchOff_prec;");

}

void orc_Mod_MAST_SwitchOff::compute ()
{
  //  std::cerr << "-> DMA_SwitchOff: start compute" << std::endl;
	/*
	 * Get the MastState variable
	 */
	if ( theRobotProcedure->GetParameters()->get("MastState", DOUBLE,
						     MAX_STATE_SIZE, 0,
						     ( char * ) MastState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"MastState");
	 }

	MastState[MAST_ACTION_ID_INDEX]  = rtId;
	MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= (duration/0.2)) {
	  //	  MastState[MAST_STATUS_INDEX] = MAST_OPER_MODE_OFF; KK
	  
	  if (targetMechanism == TARGET_MECHANISM_DEP) {
	    MastState[MAST_DEP_STATUS_INDEX]  = MAST_OPER_MODE_DEP_OFF;
	  }
	  else if (targetMechanism == TARGET_MECHANISM_PAN) {
	    MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_OFF;
	  }
	  else if (targetMechanism == TARGET_MECHANISM_TILT) {
	    MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_OFF;
	  }
	  else if (targetMechanism == TARGET_MECHANISM_PAN_TILT) {
	    MastState[MAST_PAN_STATUS_INDEX]  = MAST_OPER_MODE_PAN_OFF;
	    MastState[MAST_TILT_STATUS_INDEX] = MAST_OPER_MODE_TILT_OFF;
	  }
	  
	  DMA_SwitchOff_post = SET_EVENT;
	  //	  moduleSendEvent("DMA_SwitchOff_post;");
	  MastState[MAST_ACTION_ID_INDEX]  = rtId;
	  MastState[MAST_ACTION_RET_INDEX] = ACTION_RET_OK;
	 }

	//
	// update the resources of the robot task
	//
	/*
	double energy_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
	  (MastState[MAST_POWER_CONS_INDEX]*getSampleTime()/60.0/60.0);

	double memmass_cons =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
	  MastState[MAST_DATARATE_INDEX]*getSampleTime();

	double act_duration =
	  getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();

	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
	*/
	//
	// set the mast state
	//
	if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE,
						      MAX_STATE_SIZE, 0,
						      ( char * ) MastState ) == ERROR ) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //						Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						"MastState");
	 }

	index ++;




}

void orc_Mod_MAST_SwitchOff::end ()
{
  //  fprintf( stderr, "DMA_SwitchOff: End\n" );

	// reset the events
	DMA_SwitchOff_prec = NO_EVENT;
	DMA_SwitchOff_post = NO_EVENT;


}

}

// End class orc_Mod_DMA_SwitchOff

