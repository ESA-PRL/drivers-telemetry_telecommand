#include "module_RV_WakeUp.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_RV_WakeUp::orc_Mod_RV_WakeUp (/*ModuleTask* mt,
					  int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_RV_WakeUp", mt, indexclk*/)
  {

    DHS_LowPwr2Reduced_phase  = 0;
    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    COMMS_LST2WH_main_phase   = 0;
    COMMS_LST2WH_red_phase    = 0;
  }
  
  orc_Mod_RV_WakeUp::~orc_Mod_RV_WakeUp ()
  {

  }

  void orc_Mod_RV_WakeUp::param (char *params)
  {
    
    //  fprintf (stderr, "RV_WakeUp:: param\n");
    
    char start_task_event[80];
    sprintf(start_task_event, "Task_RV_WakeUp_start;");
    
    //    moduleSendEvent(start_task_event);
    
  }
  
  void orc_Mod_RV_WakeUp::reparam (char *params)
  {
  }
  
  void orc_Mod_RV_WakeUp::init ()
  {
    //  std::cerr << "-> RV_WakeUp: start init" << std::endl;
    index = 0;
    
    RV_WakeUp_prec = NO_EVENT;
    RV_WakeUp_post = NO_EVENT;
    
    DHS_LowPwr2Reduced_phase  = 0;
    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    COMMS_LST2WH_main_phase   = 0;
    COMMS_LST2WH_red_phase    = 0;
    
    RV_WakeUp_prec  = SET_EVENT;
    // moduleSendEvent("RV_WakeUp_prec;");
  }

  void orc_Mod_RV_WakeUp::compute ()
  {

    if ( DHS_LowPwr2Reduced_phase == 0) {
      std::cerr << "DHS_LowPwr2Reduced" << std::endl;
      DHS_LowPwr2Reduced.execute(""); 
      if (DHS_LowPwr2Reduced.DHS_LowPwr2Reduced_post == 1) {
	DHS_LowPwr2Reduced.compute_completed = 1;
      }
      if (DHS_LowPwr2Reduced.end_completed == 1) {
	DHS_LowPwr2Reduced_phase = 1;
	DHS_LowPwr2Reduced.reset();
      }
    }
    else if ( COMMS_SwitchOn_main_phase == 0) {
      std::cerr << "COMMS_SwitchOn (MAIN)" << std::endl;
      COMMS_SwitchOn.execute("MAIN"); 
      if (COMMS_SwitchOn.COMMS_SwitchOn_post == 1) {
	COMMS_SwitchOn.compute_completed = 1;
      }
      if (COMMS_SwitchOn.end_completed == 1) {
	COMMS_SwitchOn_main_phase = 1;
	COMMS_SwitchOn.reset();
      }
    }
    else if ( COMMS_LST2WH_main_phase == 0) {
      std::cerr << "COMMS_LST2WH (MAIN)" << std::endl;
      COMMS_LST2WH.execute("MAIN"); 
      if (COMMS_LST2WH.COMMS_LST2WH_post == 1) {
	COMMS_LST2WH.compute_completed = 1;
      }
      if (COMMS_LST2WH.end_completed == 1) {
	COMMS_LST2WH_main_phase = 1;
	COMMS_LST2WH.reset();
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
	COMMS_SwitchOn.reset();
      }
    }
    else if ( COMMS_LST2WH_red_phase == 0) {
      std::cerr << "COMMS_LST2WH (REDUNDANT)" << std::endl;
      COMMS_LST2WH.execute("REDUNDANT"); 
      if (COMMS_LST2WH.COMMS_LST2WH_post == 1) {
	COMMS_LST2WH.compute_completed = 1;
      }
      if (COMMS_LST2WH.end_completed == 1) {
	COMMS_LST2WH_red_phase = 1;
	RV_WakeUp_post = 1;
	COMMS_LST2WH.reset();
      }
    }

    index ++;
  }
  
  void orc_Mod_RV_WakeUp::end ()
  {
    RV_WakeUp_prec = NO_EVENT;
    RV_WakeUp_post = NO_EVENT;

    DHS_LowPwr2Reduced_phase  = 0;
    COMMS_SwitchOn_main_phase = 0;
    COMMS_SwitchOn_red_phase  = 0;
    COMMS_LST2WH_main_phase   = 0;
    COMMS_LST2WH_red_phase    = 0;
  }
  
}

// End class orc_Mod_RV_WakeUp

