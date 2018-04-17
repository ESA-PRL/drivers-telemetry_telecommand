#include "module_RV_Prepare4Comms.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  orc_Mod_RV_Prepare4Comms::orc_Mod_RV_Prepare4Comms (/*ModuleTask* mt,
							int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_RV_Prepare4Comms", mt, indexclk*/)
  {
    //  PRINT1("** orc_Mod_RV_Prepare4Comms constructor")
    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    DHS_LowPwr2Reduced_phase  = 0;
  }
  
  orc_Mod_RV_Prepare4Comms::~orc_Mod_RV_Prepare4Comms ()
  {
    //  PRINT1( "** orc_Mod_RV_Prepare4Comms destructor" )
  }
  
  void orc_Mod_RV_Prepare4Comms::param (char *params)
  {
    
    //  fprintf (stderr, "RV_Prepare4Comms:: param\n");
    
    char start_task_event[80];
    sprintf(start_task_event, "RV_Prepare4Comms_start;");
    
    //	moduleSendEvent(start_task_event);
    
    
  }
  
  void orc_Mod_RV_Prepare4Comms::reparam (char *params)
  {
  }
  
  void orc_Mod_RV_Prepare4Comms::init ()
  {
    //  std::cerr << "-> RV_Prepare4Comms: start init" << std::endl;
    
    index = 0;
    
    RV_Prepare4Comms_prec = NO_EVENT;
    RV_Prepare4Comms_post = NO_EVENT;

    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    DHS_LowPwr2Reduced_phase  = 0;
    
    RV_Prepare4Comms_prec  = SET_EVENT;
    //	moduleSendEvent("RV_Prepare4Comms_prec;");
    
    
  }
  
  void orc_Mod_RV_Prepare4Comms::compute ()
  {
    if ( COMMS_SwitchOn_main_phase == 0) {
      std::cerr << "COMMS_SwitchOn (MAIN)" << std::endl;
      COMMS_SwitchOn.execute("MAIN"); 
      if (COMMS_SwitchOn.COMMS_SwitchOn_post == 1) {
	COMMS_SwitchOn.compute_completed = 1;
      }
      if (COMMS_SwitchOn.end_completed == 1) {
	COMMS_SwitchOn_main_phase = 1;
      }
    }
    else if ( COMMS_SwitchOn_red_phase == 0) {
      std::cerr << "COMMS_SwitchOn (REDUNDANT)" << std::endl;
      COMMS_SwitchOn.execute("REDUNDANT"); 
      if (COMMS_SwitchOn.COMMS_SwitchOn_post == 1) {
	COMMS_SwitchOn.compute_completed = 1;
      }
      if (COMMS_SwitchOn.end_completed == 1) {
	COMMS_SwitchOn_red_phase = 1;
      }
    }
    else if (DHS_LowPwr2Reduced_phase  == 0) {
      std::cerr << "DHS_LowPwr2Reduced" << std::endl;
      DHS_LowPwr2Reduced.execute(""); 
      if (DHS_LowPwr2Reduced.DHS_LowPwr2Reduced_post == 1) {
	DHS_LowPwr2Reduced.compute_completed = 1;
      }
      if (DHS_LowPwr2Reduced.end_completed == 1) {
	DHS_LowPwr2Reduced_phase = 1;
	RV_Prepare4Comms_post = SET_EVENT;
      }
    }
    index ++;
  }
  
  void orc_Mod_RV_Prepare4Comms::end ()
  {
    //  fprintf( stderr, "RV_Prepare4Comms:: End\n" );
    RV_Prepare4Comms_prec = NO_EVENT;
    RV_Prepare4Comms_post = NO_EVENT;
    
    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    DHS_LowPwr2Reduced_phase  = 0;

}

}

// End class orc_Mod_RV_Prepare4Comms

