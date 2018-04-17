#include "module_RV_Prepare4Night.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_RV_Prepare4Night::orc_Mod_RV_Prepare4Night (/*ModuleTask* mt,
							int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_RV_Prepare4Night", mt, indexclk*/)
  {
    //  PRINT1("** orc_Mod_RV_Prepare4Night constructor")
    COMMS_SwitchOff_main_phase = 0;
    COMMS_SwitchOff_red_phase  = 0;
    DHS_Reduced2LowPwr_phase   = 0;
  }
  
  orc_Mod_RV_Prepare4Night::~orc_Mod_RV_Prepare4Night ()
  {
    //  PRINT1( "** orc_Mod_RV_Prepare4Night destructor" )
  }
  
  void orc_Mod_RV_Prepare4Night::param (char *params)
  {
    
    fprintf (stderr, "RV_Prepare4Night:: param\n");
    
    
    char start_task_event[80];
    sprintf(start_task_event, "Task_RV_Prepare4Night_start;");
    
    //	moduleSendEvent(start_task_event);
    
    
  }
  
  void orc_Mod_RV_Prepare4Night::reparam (char *params)
  {
  }
  
  void orc_Mod_RV_Prepare4Night::init ()
  {
    std::cerr << "-> RV_Prepare4Night: start init" << std::endl;
    
    index = 0;
    
    RV_Prepare4Night_prec = NO_EVENT;
    RV_Prepare4Night_post = NO_EVENT;
    
    COMMS_SwitchOff_main_phase = 0;
    COMMS_SwitchOff_red_phase  = 0;
    DHS_Reduced2LowPwr_phase   = 0;
    
    RV_Prepare4Night_prec  = SET_EVENT;
    //	moduleSendEvent("RV_Prepare4Night_prec;");
    
    
  }
  
  void orc_Mod_RV_Prepare4Night::compute ()
  {
    if ( COMMS_SwitchOff_main_phase == 0) {
      std::cerr << "COMMS_SwitchOff (MAIN)" << std::endl;
      COMMS_SwitchOff.execute("MAIN"); 
      if (COMMS_SwitchOff.COMMS_SwitchOff_post == 1) {
	COMMS_SwitchOff.compute_completed = 1;
      }
      if (COMMS_SwitchOff.end_completed == 1) {
	COMMS_SwitchOff_main_phase = 1;
	COMMS_SwitchOff.reset();
      }
    }
    else if ( COMMS_SwitchOff_red_phase == 0) {
      std::cerr << "COMMS_SwitchOff (REDUNDANT)" << std::endl;
      COMMS_SwitchOff.execute("REDUNDANT"); 
      if (COMMS_SwitchOff.COMMS_SwitchOff_post == 1) {
	COMMS_SwitchOff.compute_completed = 1;
      }
      if (COMMS_SwitchOff.end_completed == 1) {
	COMMS_SwitchOff_red_phase = 1;
	COMMS_SwitchOff.reset();
      }
    }
    else if (DHS_Reduced2LowPwr_phase  == 0) {
      std::cerr << "DHS_Reduced2LowPwr" << std::endl;
      DHS_Reduced2LowPwr.execute(""); 
      if (DHS_Reduced2LowPwr.DHS_Reduced2LowPwr_post == 1) {
	DHS_Reduced2LowPwr.compute_completed = 1;
      }
      if (DHS_Reduced2LowPwr.end_completed == 1) {
	DHS_Reduced2LowPwr_phase = 1;
	DHS_Reduced2LowPwr.reset();
	RV_Prepare4Night_post = SET_EVENT;
      }
    }
    index ++;
    
  }
  
  void orc_Mod_RV_Prepare4Night::end ()
  {
    //  fprintf( stderr, "RV_Prepare4Night:: End\n" );
    RV_Prepare4Night_prec = NO_EVENT;
    RV_Prepare4Night_post = NO_EVENT;
    
    
  }
  
}

// End class orc_Mod_RV_Prepare4Night

