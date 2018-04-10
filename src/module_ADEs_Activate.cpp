#include "module_ADEs_Activate.h"
#include "prr.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  static double Natural_WUP_targetT = 0;

orc_Mod_ADEs_Activate::orc_Mod_ADEs_Activate (/*ModuleTask* mt,
						int indexclk*/)
//  : ModuleAlgo ("orc_Mod_ADEs_Activate", mt, indexclk)
{
  //  PRINT1("** orc_Mod_ADEs_Activate constructor")
}

orc_Mod_ADEs_Activate::~orc_Mod_ADEs_Activate ()
{
  //  PRINT1( "** orc_Mod_ADEs_Activate destructor" )
}

void orc_Mod_ADEs_Activate::param (char *params)
{

  //  fprintf (stderr, "ADEs_Activate:: param\n");
  /*
	int params_nbr =  sscanf(params, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",Mt_ptr->GetRobotTaskPtr()->taskParams[0], Mt_ptr->GetRobotTaskPtr()->taskParams[1], Mt_ptr->GetRobotTaskPtr()->taskParams[2], Mt_ptr->GetRobotTaskPtr()->taskParams[3], Mt_ptr->GetRobotTaskPtr()->taskParams[4], Mt_ptr->GetRobotTaskPtr()->taskParams[5], Mt_ptr->GetRobotTaskPtr()->taskParams[6], Mt_ptr->GetRobotTaskPtr()->taskParams[7], Mt_ptr->GetRobotTaskPtr()->taskParams[8], Mt_ptr->GetRobotTaskPtr()->taskParams[9], Mt_ptr->GetRobotTaskPtr()->taskParams[10], Mt_ptr->GetRobotTaskPtr()->taskParams[11], Mt_ptr->GetRobotTaskPtr()->taskParams[12], Mt_ptr->GetRobotTaskPtr()->taskParams[13], Mt_ptr->GetRobotTaskPtr()->taskParams[14], Mt_ptr->GetRobotTaskPtr()->taskParams[15], Mt_ptr->GetRobotTaskPtr()->taskParams[16], Mt_ptr->GetRobotTaskPtr()->taskParams[17], Mt_ptr->GetRobotTaskPtr()->taskParams[18]);

	sscanf(Mt_ptr->GetRobotTaskPtr()->taskParams[3], "%lf", &Natural_WUP_targetT);

	char start_task_event[80];
	sprintf(start_task_event, "ADEs_Activate_start;");

	moduleSendEvent(start_task_event);
  */

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
  }
  
  void orc_Mod_ADEs_Activate::end ()
  {
    //  fprintf( stderr, "ADEs_Activate:: End\n" );
    ADEs_Activate_prec = NO_EVENT;
    ADEs_Activate_post = NO_EVENT;
    
    
  }

}

// End class orc_Mod_ADEs_Activate

