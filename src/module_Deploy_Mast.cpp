#include "module_Deploy_Mast.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_Deploy_Mast::orc_Mod_Deploy_Mast (/*ModuleTask* mt,
					      int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_Deploy_Mast", mt, indexclk*/)
  {
    GNC_MonitoringOnly_phase = 0; 
    MAST_PAN_Initialise_phase = 0;
    MAST_PAN_MoveTo_phase = 0;
    MAST_PAN_SwitchOff_phase = 0;
    MAST_TILT_Initialise_phase = 0;
    MAST_TILT_MoveTo_phase = 0;
    MAST_TILT_SwitchOff_phase = 0;
    MAST_DEP_Initialise_phase = 0;
    MAST_DEP_MoveTo_phase = 0;
    MAST_DEP_SwitchOff_phase = 0;
    GNC_SwitchOff_phase = 0;
  }
  
  orc_Mod_Deploy_Mast::~orc_Mod_Deploy_Mast ()
  {
    
  }
  
  void orc_Mod_Deploy_Mast::param (char *params)
  {
    
  }
  
  void orc_Mod_Deploy_Mast::reparam (char *params)
  {
    
  }
  
  void orc_Mod_Deploy_Mast::init ()
  {
    index = 0;
    
    Deploy_Mast_prec = NO_EVENT;
    Deploy_Mast_post = NO_EVENT;
    
    Deploy_Mast_prec  = SET_EVENT;
  }
  
  void orc_Mod_Deploy_Mast::compute ()
  {
    if (GNC_MonitoringOnly_phase == 0) {
      std::cerr << "GNC_MonitoringOnly" << std::endl;
      GNC_MonitoringOnly.execute(""); 
      if (GNC_MonitoringOnly.GNC_MonitoringOnly_post == 1) {
	GNC_MonitoringOnly.compute_completed = 1;
      }
      if (GNC_MonitoringOnly.end_completed == 1) {
	GNC_MonitoringOnly_phase = 1;
	GNC_MonitoringOnly.reset();
      }
    }
    else if (MAST_PAN_Initialise_phase == 0) {
      std::cerr << "MAST_PAN_Initialise_phase" << std::endl;
      MAST_PAN_Initialise.execute("7200 0"); 
      if (MAST_PAN_Initialise.MAST_PAN_Initialise_post == 1) {
	MAST_PAN_Initialise.compute_completed = 1;
      }
      if (MAST_PAN_Initialise.end_completed == 1) {
	MAST_PAN_Initialise_phase = 1;
	MAST_PAN_Initialise.reset();
      }
    }
    else if (MAST_PAN_MoveTo_phase == 0) {
      std::cerr << "MAST_PAN_MoveTo" << std::endl;
      MAST_PAN_MoveTo.execute("10.0"); 
      if (MAST_PAN_MoveTo.MAST_PAN_MoveTo_post == 1) {
	MAST_PAN_MoveTo.compute_completed = 1;
      }
      if (MAST_PAN_MoveTo.end_completed == 1) {
	MAST_PAN_MoveTo_phase = 1;
	MAST_PAN_MoveTo.reset();
      }
    }
    else if (MAST_PAN_SwitchOff_phase == 0) {
      std::cerr << "MAST_PAN_SwitchOff" << std::endl;
      MAST_PAN_SwitchOff.execute(""); 
      if (MAST_PAN_SwitchOff.MAST_PAN_SwitchOff_post == 1) {
	MAST_PAN_SwitchOff.compute_completed = 1;
      }
      if (MAST_PAN_SwitchOff.end_completed == 1) {
	MAST_PAN_SwitchOff_phase = 1;
	MAST_PAN_SwitchOff.reset();
      }
    }
    else if (MAST_TILT_Initialise_phase == 0) {
      std::cerr << "MAST_TILT_Initialise" << std::endl;
      MAST_TILT_Initialise.execute("7200 0"); 
      if (MAST_TILT_Initialise.MAST_TILT_Initialise_post == 1) {
	MAST_TILT_Initialise.compute_completed = 1;
      }
      if (MAST_TILT_Initialise.end_completed == 1) {
	MAST_TILT_Initialise_phase = 1;
	MAST_TILT_Initialise.reset();
      }
    }
    else if (MAST_TILT_MoveTo_phase == 0) {
      std::cerr << "MAST_TILT_MoveTo" << std::endl;
      MAST_TILT_MoveTo.execute("10"); 
      if (MAST_TILT_MoveTo.MAST_TILT_MoveTo_post == 1) {
	MAST_TILT_MoveTo.compute_completed = 1;
      }
      if (MAST_TILT_MoveTo.end_completed == 1) {
	MAST_TILT_MoveTo_phase = 1;
	MAST_TILT_MoveTo.reset();
      }
    }
    else if (MAST_TILT_SwitchOff_phase == 0) {
      std::cerr << "MAST_TILT_SwitchOff" << std::endl;
      MAST_TILT_SwitchOff.execute(""); 
      if (MAST_TILT_SwitchOff.MAST_TILT_SwitchOff_post == 1) {
	MAST_TILT_SwitchOff.compute_completed = 1;
      }
      if (MAST_TILT_SwitchOff.end_completed == 1) {
	MAST_TILT_SwitchOff_phase = 1;
	MAST_TILT_SwitchOff.reset();
      }
    }
    else if (MAST_DEP_Initialise_phase == 0) {
      std::cerr << "MAST_DEP_Initialise" << std::endl;
      MAST_DEP_Initialise.execute("7200 0"); 
      if (MAST_DEP_Initialise.MAST_DEP_Initialise_post == 1) {
	MAST_DEP_Initialise.compute_completed = 1;
      }
      if (MAST_DEP_Initialise.end_completed == 1) {
	MAST_DEP_Initialise_phase = 1;
	MAST_DEP_Initialise.reset();
      }
    }
    else if (MAST_DEP_MoveTo_phase == 0) {
      std::cerr << "MAST_DEP_MoveTo" << std::endl;
      MAST_DEP_MoveTo.execute("10"); 
      if (MAST_DEP_MoveTo.MAST_DEP_MoveTo_post == 1) {
	MAST_DEP_MoveTo.compute_completed = 1;
      }
      if (MAST_DEP_MoveTo.end_completed == 1) {
	MAST_DEP_MoveTo_phase = 1;
	MAST_DEP_MoveTo.reset();
      }
    }
    else if (MAST_DEP_SwitchOff_phase == 0) {
      std::cerr << "MAST_DEP_SwitchOff" << std::endl;
      MAST_DEP_SwitchOff.execute(""); 
      if (MAST_DEP_SwitchOff.MAST_DEP_SwitchOff_post == 1) {
	MAST_DEP_SwitchOff.compute_completed = 1;
      }
      if (MAST_DEP_SwitchOff.end_completed == 1) {
	MAST_DEP_SwitchOff_phase = 1;
	MAST_DEP_SwitchOff.reset();
      }
    }
    else if (GNC_SwitchOff_phase == 0) {
      std::cerr << "GNC_SwitchOff" << std::endl;
      GNC_SwitchOff.execute(""); 
      if (GNC_SwitchOff.GNC_SwitchOff_post == 1) {
	GNC_SwitchOff.compute_completed = 1;
      }
      if (GNC_SwitchOff.end_completed == 1) {
	GNC_SwitchOff_phase = 1;
	GNC_SwitchOff.reset();
      }
      
    }
    else {
      Deploy_Mast_post = SET_EVENT;
    }
  }
  
  void orc_Mod_Deploy_Mast::end ()
  {
    //  fprintf( stderr, "Deploy_Mast:: End\n" );
    Deploy_Mast_prec = NO_EVENT;
    Deploy_Mast_post = NO_EVENT;

    
    GNC_MonitoringOnly_phase = 0; 
    MAST_PAN_Initialise_phase = 0;
    MAST_PAN_MoveTo_phase = 0;
    MAST_PAN_SwitchOff_phase = 0;
    MAST_TILT_Initialise_phase = 0;
    MAST_TILT_MoveTo_phase = 0;
    MAST_TILT_SwitchOff_phase = 0;
    MAST_DEP_Initialise_phase = 0;
    MAST_DEP_MoveTo_phase = 0;
    MAST_DEP_SwitchOff_phase = 0;
    GNC_SwitchOff_phase = 0;
  }
  
}

// End class orc_Mod_Deploy_Mast

