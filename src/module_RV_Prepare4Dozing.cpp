#include "module_RV_Prepare4Dozing.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_RV_Prepare4Dozing::orc_Mod_RV_Prepare4Dozing (/*ModuleTask* mt,
							int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_RV_Prepare4Dozing", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_RV_Prepare4Dozing constructor")
}

orc_Mod_RV_Prepare4Dozing::~orc_Mod_RV_Prepare4Dozing ()
{
  //  PRINT1( "** orc_Mod_RV_Prepare4Dozing destructor" )
}

void orc_Mod_RV_Prepare4Dozing::param (char *params)
{

  //  fprintf (stderr, "RV_Prepare4Dozing:: param\n");


	char start_task_event[80];
	sprintf(start_task_event, "Task_RV_Prepare4Dozing_start;");

	//	moduleSendEvent(start_task_event);


}

void orc_Mod_RV_Prepare4Dozing::reparam (char *params)
{
}

void orc_Mod_RV_Prepare4Dozing::init ()
{
  //  std::cerr << "-> RV_Prepare4Dozing: start init" << std::endl;

	index = 0;

	RV_Prepare4Dozing_prec = NO_EVENT;
	RV_Prepare4Dozing_post = NO_EVENT;

	RV_Prepare4Dozing_prec  = SET_EVENT;
	//	moduleSendEvent("RV_Prepare4Dozing_prec;");


}

void orc_Mod_RV_Prepare4Dozing::compute ()
{

	index ++;
}

void orc_Mod_RV_Prepare4Dozing::end ()
{
  //  fprintf( stderr, "RV_Prepare4Dozing:: End\n" );
	RV_Prepare4Dozing_prec = NO_EVENT;
	RV_Prepare4Dozing_post = NO_EVENT;


}

}

// End class orc_Mod_RV_Prepare4Dozing

