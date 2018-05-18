#include "module_RV_SwitchOffTravel.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_RV_SwitchOffTravel::orc_Mod_RV_SwitchOffTravel (/*ModuleTask* mt,
							  int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_RV_SwitchOffTravel", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_RV_SwitchOffTravel constructor")
}

orc_Mod_RV_SwitchOffTravel::~orc_Mod_RV_SwitchOffTravel ()
{
  //  PRINT1( "** orc_Mod_RV_SwitchOffTravel destructor" )
}

void orc_Mod_RV_SwitchOffTravel::param (char *params)
{

  //  fprintf (stderr, "RV_SwitchOffTravel:: param\n");


	char start_task_event[80];
	sprintf(start_task_event, "Task_RV_SwitchOffTravel_start;");

	//	moduleSendEvent(start_task_event);


}

void orc_Mod_RV_SwitchOffTravel::reparam (char *params)
{
}

void orc_Mod_RV_SwitchOffTravel::init ()
{
  //  std::cerr << "-> RV_SwitchOffTravel: start init" << std::endl;

	index = 0;

	RV_SwitchOffTravel_prec = NO_EVENT;
	RV_SwitchOffTravel_post = NO_EVENT;

	RV_SwitchOffTravel_prec  = SET_EVENT;
	//	moduleSendEvent("RV_SwitchOffTravel_prec;");


}

void orc_Mod_RV_SwitchOffTravel::compute ()
{

	index ++;


}

void orc_Mod_RV_SwitchOffTravel::end ()
{
  //  fprintf( stderr, "RV_SwitchOffTravel:: End\n" );
	RV_SwitchOffTravel_prec = NO_EVENT;
	RV_SwitchOffTravel_post = NO_EVENT;


}

}

// End class orc_Mod_RV_SwitchOffTravel

