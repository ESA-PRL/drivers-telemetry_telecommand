#include "module_ADEs_DeActivate.h"

//
// KK implemented the parallel execution of ADE_SwitchOff(0) and ADE_SwitchOff(1)
// TODO durations
// TODO to manage the WARMUP - INIT - STNDBY phases
//

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_ADEs_DeActivate::orc_Mod_ADEs_DeActivate (/*ModuleTask* mt,
						    int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_ADEs_DeActivate", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_ADEs_DeActivate constructor")
}

orc_Mod_ADEs_DeActivate::~orc_Mod_ADEs_DeActivate ()
{
  //  PRINT1( "** orc_Mod_ADEs_DeActivate destructor" )
}

void orc_Mod_ADEs_DeActivate::param (char *params)
{

  fprintf (stderr, "ADEs_DeActivate:: param\n");
  
}

void orc_Mod_ADEs_DeActivate::reparam (char *params)
{
  //  fprintf( stderr, "ADEs_DeActivate:: reparam\n" );
  // #include   "ADEs_DeActivate/user_code/reparam_code.c"
}


void orc_Mod_ADEs_DeActivate::init ()
{
  std::cerr << "-> ADEs_DeActivate: start init" << std::endl;

	index = 0;

	ADEs_DeActivate_prec = NO_EVENT;
	ADEs_DeActivate_post = NO_EVENT;
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/
	ADEs_DeActivate_prec  = SET_EVENT;
	// moduleSendEvent("ADEs_DeActivate_prec;");


}

void orc_Mod_ADEs_DeActivate::compute ()
{
  //  std::cerr << "-> ADEs_DeActivate: start compute" << std::endl;
  /*
	if (Mt_ptr->GetRobotTaskPtr()->postCondExternal == SET_EVENT) {
	Mt_ptr->GetRobotTaskPtr()->postCondExternal = NO_EVENT;
	  moduleSendEvent("ADEs_DeActivate_post;");
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
    
    if (index > 10) {

      AdeState[ADE_STATUS_LEFT_INDEX]  = ADE_OPER_MODE_OFF;
      AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      ADEs_DeActivate_post = SET_EVENT;

    }
    
    if (theRobotProcedure->GetParameters()->set("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }

    index ++;
}

void orc_Mod_ADEs_DeActivate::end ()
{
  fprintf( stderr, "ADEs_DeActivate:: End\n" );
  ADEs_DeActivate_prec = NO_EVENT;
  ADEs_DeActivate_post = NO_EVENT;


}

}

// End class orc_Mod_ADEs_DeActivate

