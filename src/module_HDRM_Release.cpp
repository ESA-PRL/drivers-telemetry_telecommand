#include "module_HDRM_Release.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_HDRM_Release::orc_Mod_HDRM_Release (/*ModuleTask* mt,
						int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_HDRM_Release", mt, indexclk*/)
  {
    //    PRINT1("** orc_Mod_HDRM_Release constructor")
  }
  
  orc_Mod_HDRM_Release::~orc_Mod_HDRM_Release ()
  {
    //PRINT1( "** orc_Mod_HDRM_Release destructor" )
  }
  
  void orc_Mod_HDRM_Release::param (char *params)
  {
    
    fprintf (stderr, "HDRM_Release:: param\n");
    
    
    char start_task_event[80];
    sprintf(start_task_event, "Task_HDRM_Release_start;");
    
    //  moduleSendEvent(start_task_event);
    
    
  }
  
  void orc_Mod_HDRM_Release::reparam (char *params)
  {
    //  fprintf( stderr, "HDRM_Release:: reparam\n" );
    // #include   "HDRM_Release/user_code/reparam_code.c"
  }
  
  void orc_Mod_HDRM_Release::init ()
  {
    std::cerr << "-> HDRM_Release: start init" << std::endl;
    
    index = 0;
    
    HDRM_Release_prec = NO_EVENT;
    HDRM_Release_post = NO_EVENT;
    
    
    HDRM_Release_prec  = SET_EVENT;
    // moduleSendEvent("HDRM_Release_prec;");
    
    
  }
  
  void orc_Mod_HDRM_Release::compute ()
  {
    if (index == 10) {
      HDRM_Release_post = SET_EVENT;
    }

    index ++;
    
  }
  
  void orc_Mod_HDRM_Release::end ()
  {
    fprintf( stderr, "HDRM_Release:: End\n" );
    HDRM_Release_prec = NO_EVENT;
    HDRM_Release_post = NO_EVENT;
    
    
  }
  
}

// End class orc_Mod_HDRM_Release

