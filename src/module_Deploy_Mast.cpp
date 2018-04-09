#include "module_Deploy_Mast.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_Deploy_Mast::orc_Mod_Deploy_Mast (/*ModuleTask* mt,
					    int indexclk*/)
//  : ModuleAlgo ("orc_Mod_Deploy_Mast", mt, indexclk)
{
  //  PRINT1("** orc_Mod_Deploy_Mast constructor")
}

orc_Mod_Deploy_Mast::~orc_Mod_Deploy_Mast ()
{
  //  PRINT1( "** orc_Mod_Deploy_Mast destructor" )
}

void orc_Mod_Deploy_Mast::param (char *params)
{

  //  fprintf (stderr, "Deploy_Mast:: param\n");
  /*
	int params_nbr =  sscanf(params, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",Mt_ptr->GetRobotTaskPtr()->taskParams[0], Mt_ptr->GetRobotTaskPtr()->taskParams[1], Mt_ptr->GetRobotTaskPtr()->taskParams[2], Mt_ptr->GetRobotTaskPtr()->taskParams[3], Mt_ptr->GetRobotTaskPtr()->taskParams[4], Mt_ptr->GetRobotTaskPtr()->taskParams[5], Mt_ptr->GetRobotTaskPtr()->taskParams[6], Mt_ptr->GetRobotTaskPtr()->taskParams[7], Mt_ptr->GetRobotTaskPtr()->taskParams[8], Mt_ptr->GetRobotTaskPtr()->taskParams[9], Mt_ptr->GetRobotTaskPtr()->taskParams[10], Mt_ptr->GetRobotTaskPtr()->taskParams[11], Mt_ptr->GetRobotTaskPtr()->taskParams[12], Mt_ptr->GetRobotTaskPtr()->taskParams[13], Mt_ptr->GetRobotTaskPtr()->taskParams[14], Mt_ptr->GetRobotTaskPtr()->taskParams[15], Mt_ptr->GetRobotTaskPtr()->taskParams[16], Mt_ptr->GetRobotTaskPtr()->taskParams[17], Mt_ptr->GetRobotTaskPtr()->taskParams[18]);

	char start_task_event[80];
	sprintf(start_task_event, "Task_Deploy_Mast_start;");
  */
	//	moduleSendEvent(start_task_event);


}

void orc_Mod_Deploy_Mast::reparam (char *params)
{
  //  fprintf( stderr, "Deploy_Mast:: reparam\n" );
 // #include   "Deploy_Mast/user_code/reparam_code.c"
}

void orc_Mod_Deploy_Mast::init ()
{
  //  std::cerr << "-> Deploy_Mast: start init" << std::endl;

	index = 0;

	Deploy_Mast_prec = NO_EVENT;
	Deploy_Mast_post = NO_EVENT;
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/
	Deploy_Mast_prec  = SET_EVENT;
	// moduleSendEvent("Deploy_Mast_prec;");


}

void orc_Mod_Deploy_Mast::compute ()
{
  /*
  // std::cerr << "-> Deploy_Mast: start compute" << std::endl;
	if (Mt_ptr->GetRobotTaskPtr()->postCondExternal == SET_EVENT) {
	Mt_ptr->GetRobotTaskPtr()->postCondExternal = NO_EVENT;
	  moduleSendEvent("Deploy_Mast_post;");
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

void orc_Mod_Deploy_Mast::end ()
{
  //  fprintf( stderr, "Deploy_Mast:: End\n" );
	Deploy_Mast_prec = NO_EVENT;
	Deploy_Mast_post = NO_EVENT;

}

}

// End class orc_Mod_Deploy_Mast

