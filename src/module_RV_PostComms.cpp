#include "module_RV_PostComms.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  orc_Mod_RV_PostComms::orc_Mod_RV_PostComms (/*ModuleTask* mt,
						int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_RV_PostComms", mt, indexclk*/)
  {
    //  PRINT1("** orc_Mod_RV_PostComms constructor")
    COMMS_SwitchOff_main_phase = 0;
    COMMS_SwitchOff_red_phase  = 0;
    DHS_Reduced2LowPwr_phase   = 0;
  }
  
  orc_Mod_RV_PostComms::~orc_Mod_RV_PostComms ()
  {
    //  PRINT1( "** orc_Mod_RV_PostComms destructor" )
  }
  
  void orc_Mod_RV_PostComms::param (char *params)
  {
    
    //  fprintf (stderr, "RV_PostComms:: param\n");
    
    char start_task_event[80];
    sprintf(start_task_event, "RV_PostComms_start;");
    
    //	moduleSendEvent(start_task_event);
    
    
  }
  
  void orc_Mod_RV_PostComms::reparam (char *params)
  {
    //  fprintf( stderr, "RV_PostComms:: reparam\n" );
    // #include   "RV_PostComms/user_code/reparam_code.c"
  }
  
  void orc_Mod_RV_PostComms::init ()
  {
    //  std::cerr << "-> RV_PostComms: start init" << std::endl;
    
    index = 0;
    
    RV_PostComms_prec = NO_EVENT;
    RV_PostComms_post = NO_EVENT;
    
    COMMS_SwitchOff_main_phase = 0;
    COMMS_SwitchOff_red_phase  = 0;
    DHS_Reduced2LowPwr_phase   = 0;

    RV_PostComms_prec  = SET_EVENT;
    //	moduleSendEvent("RV_PostComms_prec;");
    
    
  }
  
  void orc_Mod_RV_PostComms::compute ()
  {
    index ++;
    if ( COMMS_SwitchOff_main_phase == 0) {
      std::cerr << "COMMS_SwitchOff (MAIN)" << std::endl;
      COMMS_SwitchOff.execute("MAIN"); 
      if (COMMS_SwitchOff.COMMS_SwitchOff_post == 1) {
	COMMS_SwitchOff.compute_completed = 1;
      }
      if (COMMS_SwitchOff.end_completed == 1) {
	COMMS_SwitchOff_main_phase = 1;
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
	RV_PostComms_post = SET_EVENT;
      }
    }
}

void orc_Mod_RV_PostComms::end ()
{
  //  fprintf( stderr, "RV_PostComms:: End\n" );
	RV_PostComms_prec = NO_EVENT;
	RV_PostComms_post = NO_EVENT;

  COMMS_SwitchOff_main_phase = 0;
  COMMS_SwitchOff_red_phase  = 0;
  DHS_Reduced2LowPwr_phase   = 0;

}

}

// End class orc_Mod_RV_PostComms

