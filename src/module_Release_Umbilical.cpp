#include "module_Release_Umbilical.h"
#include "prr.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


orc_Mod_Release_Umbilical::orc_Mod_Release_Umbilical (/*ModuleTask* mt,
							int indexclk*/)
  : ModuleAlgo (/*"orc_Mod_Release_Umbilical", mt, indexclk*/)
{
  //  PRINT1("** orc_Mod_Release_Umbilical constructor")
  GNC_MonitoringOnly_phase = 0;
  ADE_ReleaseHDRM_0_10_phase = 0;
  ADE_ReleaseHDRM_0_11_phase = 0;
  GNC_SwitchOff_phase = 0;
}

orc_Mod_Release_Umbilical::~orc_Mod_Release_Umbilical ()
{
  //  PRINT1( "** orc_Mod_Release_Umbilical destructor" )
}

void orc_Mod_Release_Umbilical::param (char *params)
{

  fprintf (stderr, "Release_Umbilical:: param\n");


	//
	// the action status is ok
	//
	action_exec_status = ACTION_RET_OK;


}

void orc_Mod_Release_Umbilical::reparam (char *params)
{
  //  fprintf( stderr, "Release_Umbilical:: reparam\n" );
  // #include   "Release_Umbilical/user_code/reparam_code.c"
}

void orc_Mod_Release_Umbilical::init ()
{
  std::cerr << "-> Release_Umbilical: start init" << std::endl;
	//
	// if the action status is not ok (because of bad parameterisation
	// the code is not executed
	//
	if (action_exec_status != ACTION_RET_OK) {
	  fprintf(stderr, "In Release_Umbilical::init() action status = error\n");
	  //	  moduleSendEvent("Release_Umbilical_exc;");
	  return;
	 }


	// reset the counter
	index = 0;

	//
	// reset the events
	//
	Release_Umbilical_prec = NO_EVENT;
	Release_Umbilical_post = NO_EVENT;


	//
	// Get Action ID
	//
	rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();

	//
	// reset the resources of the robot task
	//
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

	//
	// set action execution information
	//

	//
	// the preconditions are satisfied
	//
	Release_Umbilical_prec = SET_EVENT;
	//	moduleSendEvent("Release_Umbilical_prec;");

}

  // GNC_MonitoringOnly
  // HDRM_Release(10,4,0,120,200,0) 
  // HDRM_Release(11,4,0,120,200,0)
  // GNC_SwitchOff
void orc_Mod_Release_Umbilical::compute ()
{

    if ( GNC_MonitoringOnly_phase == 0) {
      std::cerr << "GNC_MonitoringOnly" << std::endl;
      GNC_MonitoringOnly.execute(""); 
      if (GNC_MonitoringOnly.GNC_MonitoringOnly_post == 1) {
	GNC_MonitoringOnly.compute_completed = 1;
      }
      if (GNC_MonitoringOnly.end_completed == 1) {
	GNC_MonitoringOnly.reset();
	GNC_MonitoringOnly_phase = 1;
      }
    }
    else if ( ADE_ReleaseHDRM_0_10_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM" << std::endl;
      ADE_ReleaseHDRM.execute("0 10"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_10_phase = 1;
      }
    }
    else if ( ADE_ReleaseHDRM_0_11_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM" << std::endl;
      ADE_ReleaseHDRM.execute("0 11"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_11_phase = 1;
      }
    }
    else if ( GNC_SwitchOff_phase == 0) {
      std::cerr << "GNC_SwitchOff ()" << std::endl;
      GNC_SwitchOff.execute(""); 
      if (GNC_SwitchOff.GNC_SwitchOff_post == 1) {
	GNC_SwitchOff.compute_completed = 1;
      }
      if (GNC_SwitchOff.end_completed == 1) {
	GNC_SwitchOff_phase = 1;
	GNC_SwitchOff.reset();
	Release_Umbilical_post = 1;
      }
    }
    index++;


}

void orc_Mod_Release_Umbilical::end ()
{
  fprintf( stderr, "Release_Umbilical:: End\n" );
	Release_Umbilical_prec = NO_EVENT;
	Release_Umbilical_post = NO_EVENT;

  GNC_MonitoringOnly_phase = 0;
  ADE_ReleaseHDRM_0_10_phase = 0;
  ADE_ReleaseHDRM_0_11_phase = 0;
  GNC_SwitchOff_phase = 0;

}

}

// End class orc_Mod_Release_Umbilical

