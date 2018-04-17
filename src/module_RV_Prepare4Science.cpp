#include "module_RV_Prepare4Science.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_RV_Prepare4Science::orc_Mod_RV_Prepare4Science (/*ModuleTask* mt,
							  int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_RV_Prepare4Science", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_RV_Prepare4Science constructor")
}

orc_Mod_RV_Prepare4Science::~orc_Mod_RV_Prepare4Science ()
{
  //  PRINT1( "** orc_Mod_RV_Prepare4Science destructor" )
}

void orc_Mod_RV_Prepare4Science::param (char *params)
{


	char start_task_event[80];
	sprintf(start_task_event, "Task_RV_Prepare4Science_start;");

	//	moduleSendEvent(start_task_event);


}

void orc_Mod_RV_Prepare4Science::reparam (char *params)
{
}

void orc_Mod_RV_Prepare4Science::init ()
{
  //  std::cerr << "-> RV_Prepare4Science: start init" << std::endl;

	index = 0;

	RV_Prepare4Science_prec = NO_EVENT;
	RV_Prepare4Science_post = NO_EVENT;

	RV_Prepare4Science_prec  = SET_EVENT;
	//	moduleSendEvent("RV_Prepare4Science_prec;");


}

void orc_Mod_RV_Prepare4Science::compute ()
{

	index ++;
}

void orc_Mod_RV_Prepare4Science::end ()
{
  //  fprintf( stderr, "RV_Prepare4Science:: End\n" );
	RV_Prepare4Science_prec = NO_EVENT;
	RV_Prepare4Science_post = NO_EVENT;


}

}

// End class orc_Mod_RV_Prepare4Science

