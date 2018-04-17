#include "module_ADEs_Activate.h"
#include "prr.h"

//
// KK implemented the parallel execution of ADE_SwitchOn(0) and ADE_SwitchOn(1)
// TODO durations
// TODO to manage the WARMUP - INIT - STNDBY phases
//
 
/** The model of the o/b controller */
namespace ControllerModelNamespace {


  static double Natural_WUP_targetT = 0;

orc_Mod_ADEs_Activate::orc_Mod_ADEs_Activate (/*ModuleTask* mt,
						int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_ADEs_Activate", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_ADEs_Activate constructor")
}

orc_Mod_ADEs_Activate::~orc_Mod_ADEs_Activate ()
{
  //  PRINT1( "** orc_Mod_ADEs_Activate destructor" )
}

void orc_Mod_ADEs_Activate::param (char *params)
{


}

void orc_Mod_ADEs_Activate::reparam (char *params)
{
  //  fprintf( stderr, "ADEs_Activate:: reparam\n" );
  // #include   "ADEs_Activate/user_code/reparam_code.c"
}

void orc_Mod_ADEs_Activate::init ()
{
  //  std::cerr << "-> ADEs_Activate: start init" << std::endl;

	index = 0;

	ADEs_Activate_prec = NO_EVENT;
	ADEs_Activate_post = NO_EVENT;

	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/
}
  void orc_Mod_ADEs_Activate::compute ()
  {
    /*
    if ( ((getLmdAirTemperature() - 273.15) > Natural_WUP_targetT) && 
	 (ADEs_Activate_prec == NO_EVENT)) {

      std::cerr << "LmdAirTemperature > Natural_WUP_targetT (" << getLmdAirTemperature() << ","
		<< Natural_WUP_targetT << ")" << std::endl;

      ADEs_Activate_prec  = SET_EVENT;
      moduleSendEvent("ADEs_Activate_prec;");

    }
    */
    /*
    if (Mt_ptr->GetRobotTaskPtr()->postCondExternal == SET_EVENT) {
      Mt_ptr->GetRobotTaskPtr()->postCondExternal = NO_EVENT;
      moduleSendEvent("ADEs_Activate_post;");
    }
    
    index ++;
    current_time = current_time + getSampleTime ();
    
    double energy_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons() +
      0.0*getSampleTime()/60.0/60.0;
    double memmass_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons() +
      0.0*getSampleTime();
    double act_duration =
      getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

    AdeState[ADE_STATUS_LEFT_INDEX]  = ADE_OPER_MODE_WARMUP;
    AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;

    if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }


    AdeState[ADE_STATUS_LEFT_INDEX]  = ADE_OPER_MODE_WARMUP;
    AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_WARMUP;
    
    if (index > 5) {
      AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_INIT;
      AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_INIT;
    }
    
    if (index > 10) {

      AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
      AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
      ADEs_Activate_post = SET_EVENT;

    }
    
    if (theRobotProcedure->GetParameters()->set("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }

    index ++;
  }
  
  void orc_Mod_ADEs_Activate::end ()
  {
    //  fprintf( stderr, "ADEs_Activate:: End\n" );
    ADEs_Activate_prec = NO_EVENT;
    ADEs_Activate_post = NO_EVENT;
    
    
  }

}

// End class orc_Mod_ADEs_Activate

