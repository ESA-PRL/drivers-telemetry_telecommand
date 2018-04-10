#include "module_Deploy_RIGHT_SA.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_Deploy_RIGHT_SA::orc_Mod_Deploy_RIGHT_SA (/*ModuleTask* mt,
						    int indexclk*/)
//  : ModuleAlgo ("orc_Mod_Deploy_RIGHT_SA", mt, indexclk)
{
  //  PRINT1("** orc_Mod_Deploy_RIGHT_SA constructor")
}

orc_Mod_Deploy_RIGHT_SA::~orc_Mod_Deploy_RIGHT_SA ()
{
  //  PRINT1( "** orc_Mod_Deploy_RIGHT_SA destructor" )
}

void orc_Mod_Deploy_RIGHT_SA::param (char *params)
{

  //  fprintf (stderr, "Deploy_RIGHT_SA:: param\n");

  /*
	int params_nbr =  sscanf(params, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",Mt_ptr->GetRobotTaskPtr()->taskParams[0], Mt_ptr->GetRobotTaskPtr()->taskParams[1], Mt_ptr->GetRobotTaskPtr()->taskParams[2], Mt_ptr->GetRobotTaskPtr()->taskParams[3], Mt_ptr->GetRobotTaskPtr()->taskParams[4], Mt_ptr->GetRobotTaskPtr()->taskParams[5], Mt_ptr->GetRobotTaskPtr()->taskParams[6], Mt_ptr->GetRobotTaskPtr()->taskParams[7], Mt_ptr->GetRobotTaskPtr()->taskParams[8], Mt_ptr->GetRobotTaskPtr()->taskParams[9], Mt_ptr->GetRobotTaskPtr()->taskParams[10], Mt_ptr->GetRobotTaskPtr()->taskParams[11], Mt_ptr->GetRobotTaskPtr()->taskParams[12], Mt_ptr->GetRobotTaskPtr()->taskParams[13], Mt_ptr->GetRobotTaskPtr()->taskParams[14], Mt_ptr->GetRobotTaskPtr()->taskParams[15], Mt_ptr->GetRobotTaskPtr()->taskParams[16], Mt_ptr->GetRobotTaskPtr()->taskParams[17], Mt_ptr->GetRobotTaskPtr()->taskParams[18], Mt_ptr->GetRobotTaskPtr()->taskParams[19], Mt_ptr->GetRobotTaskPtr()->taskParams[20], Mt_ptr->GetRobotTaskPtr()->taskParams[21], Mt_ptr->GetRobotTaskPtr()->taskParams[22], Mt_ptr->GetRobotTaskPtr()->taskParams[23], Mt_ptr->GetRobotTaskPtr()->taskParams[24], Mt_ptr->GetRobotTaskPtr()->taskParams[25], Mt_ptr->GetRobotTaskPtr()->taskParams[26], Mt_ptr->GetRobotTaskPtr()->taskParams[27], Mt_ptr->GetRobotTaskPtr()->taskParams[28]);

	char start_task_event[80];
	sprintf(start_task_event, "Deploy_RIGHT_SA_start;");

	moduleSendEvent(start_task_event);
  */

}

void orc_Mod_Deploy_RIGHT_SA::reparam (char *params)
{
  //  fprintf( stderr, "Deploy_RIGHT_SA:: reparam\n" );
  // #include   "Deploy_RIGHT_SA/user_code/reparam_code.c"
}

void orc_Mod_Deploy_RIGHT_SA::init ()
{
  //  std::cerr << "-> Deploy_RIGHT_SA: start init" << std::endl;

	index = 0;

	Deploy_RIGHT_SA_prec = NO_EVENT;
	Deploy_RIGHT_SA_post = NO_EVENT;

	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/
	Deploy_RIGHT_SA_prec  = SET_EVENT;
	//	moduleSendEvent("Deploy_RIGHT_SA_prec;");


}

void orc_Mod_Deploy_RIGHT_SA::compute ()
{
  /*
  //  std::cerr << "-> Deploy_RIGHT_SA: start compute" << std::endl;
	if (Mt_ptr->GetRobotTaskPtr()->postCondExternal == SET_EVENT) {
	Mt_ptr->GetRobotTaskPtr()->postCondExternal = NO_EVENT;
	  moduleSendEvent("Deploy_RIGHT_SA_post;");
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

void orc_Mod_Deploy_RIGHT_SA::end ()
{
  //  fprintf( stderr, "Deploy_RIGHT_SA:: End\n" );
	Deploy_RIGHT_SA_prec = NO_EVENT;
	Deploy_RIGHT_SA_post = NO_EVENT;


}

}

// End class orc_Mod_Deploy_RIGHT_SA

