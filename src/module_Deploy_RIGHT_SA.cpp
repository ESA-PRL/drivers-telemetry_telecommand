#include "module_Deploy_RIGHT_SA.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  orc_Mod_Deploy_RIGHT_SA::orc_Mod_Deploy_RIGHT_SA (/*ModuleTask* mt,
						    int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_Deploy_RIGHT_SA", mt, indexclk*/)
  {
    //  PRINT1("** orc_Mod_Deploy_RIGHT_SA constructor")
    ADE_ReleaseHDRM_0_7_phase          = 0;
    ADE_ReleaseHDRM_0_8_phase          = 0;
    ADE_ReleaseHDRM_0_9_phase          = 0;
    SA_RIGHT_Primary_Initialise_phase   = 0;
    SA_RIGHT_Secondary_Initialise_phase = 0;
    SA_RIGHT_Primary_MoveTo_phase       = 0;
    SA_RIGHT_Secondary_MoveTo_phase     = 0;
    SA_RIGHT_Primary_MoveTo_phase       = 0;
    SA_RIGHT_Primary_SwitchOff_phase    = 0;
    SA_RIGHT_Secondary_SwitchOff_phase  = 0;
    GNC_SwitchOff_phase                = 0;
  }
  
  orc_Mod_Deploy_RIGHT_SA::~orc_Mod_Deploy_RIGHT_SA ()
  {
    //  PRINT1( "** orc_Mod_Deploy_RIGHT_SA destructor" )
  }
  
  void orc_Mod_Deploy_RIGHT_SA::param (char *params)
  {
    std::cerr << "-> Deploy_RIGHT_SA: param" << std::endl;
    
  }
  
  void orc_Mod_Deploy_RIGHT_SA::reparam (char *params)
  {
  }
  
  void orc_Mod_Deploy_RIGHT_SA::init ()
  {
    std::cerr << "-> Deploy_RIGHT_SA: start init" << std::endl;
    
    index = 0;
    
    ADE_ReleaseHDRM_0_7_phase          = 0;
    ADE_ReleaseHDRM_0_8_phase          = 0;
    ADE_ReleaseHDRM_0_9_phase          = 0;
    SA_RIGHT_Primary_Initialise_phase   = 0;
    SA_RIGHT_Secondary_Initialise_phase = 0;
    SA_RIGHT_Primary_MoveTo_phase       = 0;
    SA_RIGHT_Secondary_MoveTo_phase     = 0;
    SA_RIGHT_Primary_MoveTo_phase       = 0;
    SA_RIGHT_Primary_SwitchOff_phase    = 0;
    SA_RIGHT_Secondary_SwitchOff_phase  = 0;
    GNC_SwitchOff_phase                = 0;
    
    Deploy_RIGHT_SA_prec = NO_EVENT;
    Deploy_RIGHT_SA_post = NO_EVENT;
    
  }
  
  void orc_Mod_Deploy_RIGHT_SA::compute ()
  {
    if ( ADE_ReleaseHDRM_0_7_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM(0,7)" << std::endl;
      ADE_ReleaseHDRM.execute("0 7"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_7_phase = 1;
      }
    } 
    else if ( ADE_ReleaseHDRM_0_8_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM (0,8)" << std::endl;
      ADE_ReleaseHDRM.execute("0 8"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_8_phase = 1;
      }
    } 
    else if ( ADE_ReleaseHDRM_0_9_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM (0,9)" << std::endl;
      ADE_ReleaseHDRM.execute("0 9"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_9_phase = 1;
      }
    } 
    else if ( SA_RIGHT_Primary_Initialise_phase == 0) {
      std::cerr << "SA_RIGHT_Primary_Initialise" << std::endl;
      SA_RIGHT_Primary_Initialise.execute("1 1"); 
      if (SA_RIGHT_Primary_Initialise.SA_RIGHT_Primary_Initialise_post == 1) {
	SA_RIGHT_Primary_Initialise.compute_completed = 1;
      }
      if (SA_RIGHT_Primary_Initialise.end_completed == 1) {
	SA_RIGHT_Primary_Initialise.reset();
	SA_RIGHT_Primary_Initialise_phase = 1;
      }
    } 
    else if ( SA_RIGHT_Secondary_Initialise_phase == 0) {
      std::cerr << "SA_RIGHT_Secondary_Initialise" << std::endl;
      SA_RIGHT_Secondary_Initialise.execute("1 1"); 
      if (SA_RIGHT_Secondary_Initialise.SA_RIGHT_Secondary_Initialise_post == 1) {
	SA_RIGHT_Secondary_Initialise.compute_completed = 1;
      }
      if (SA_RIGHT_Secondary_Initialise.end_completed == 1) {
	SA_RIGHT_Secondary_Initialise.reset();
	SA_RIGHT_Secondary_Initialise_phase = 1;
      }
    } 
    else if ( SA_RIGHT_Primary_MoveTo_phase == 0) {
      std::cerr << "SA_RIGHT_Primary_MoveTo" << std::endl;
      SA_RIGHT_Primary_MoveTo.execute("10.0"); 
      if (SA_RIGHT_Primary_MoveTo.SA_RIGHT_Primary_MoveTo_post == 1) {
	SA_RIGHT_Primary_MoveTo.compute_completed = 1;
      }
      if (SA_RIGHT_Primary_MoveTo.end_completed == 1) {
	SA_RIGHT_Primary_MoveTo.reset();
	SA_RIGHT_Primary_MoveTo_phase = 1;
      }
    } else if ( SA_RIGHT_Secondary_MoveTo_phase == 0) {
      std::cerr << "SA_RIGHT_Secondary_MoveTo" << std::endl;
      SA_RIGHT_Secondary_MoveTo.execute("10.0"); 
      if (SA_RIGHT_Secondary_MoveTo.SA_RIGHT_Secondary_MoveTo_post == 1) {
	SA_RIGHT_Secondary_MoveTo.compute_completed = 1;
      }
      if (SA_RIGHT_Secondary_MoveTo.end_completed == 1) {
	SA_RIGHT_Secondary_MoveTo.reset();
	SA_RIGHT_Secondary_MoveTo_phase = 1;
      }
    } 
    else if ( SA_RIGHT_Primary_SwitchOff_phase == 0) {
      std::cerr << "SA_RIGHT_Primary_SwitchOff" << std::endl;
      SA_RIGHT_Primary_SwitchOff.execute(""); 
      if (SA_RIGHT_Primary_SwitchOff.SA_RIGHT_Primary_SwitchOff_post == 1) {
	SA_RIGHT_Primary_SwitchOff.compute_completed = 1;
      }
      if (SA_RIGHT_Primary_SwitchOff.end_completed == 1) {
	SA_RIGHT_Primary_SwitchOff.reset();
	SA_RIGHT_Primary_SwitchOff_phase = 1;
      }
    } 
    else if ( SA_RIGHT_Secondary_SwitchOff_phase == 0) {
      std::cerr << "SA_RIGHT_Secondary_SwitchOff" << std::endl;
      SA_RIGHT_Secondary_SwitchOff.execute(""); 
      if (SA_RIGHT_Secondary_SwitchOff.SA_RIGHT_Secondary_SwitchOff_post == 1) {
	SA_RIGHT_Secondary_SwitchOff.compute_completed = 1;
      }
      if (SA_RIGHT_Secondary_SwitchOff.end_completed == 1) {
	SA_RIGHT_Secondary_SwitchOff.reset();
	SA_RIGHT_Secondary_SwitchOff_phase = 1;
      }
    } 
    else if ( GNC_SwitchOff_phase == 0) {
      std::cerr << "GNC_SwitchOff" << std::endl;
      GNC_SwitchOff.execute(""); 
      if (GNC_SwitchOff.GNC_SwitchOff_post == 1) {
	GNC_SwitchOff.compute_completed = 1;
      }
      if (GNC_SwitchOff.end_completed == 1) {
	GNC_SwitchOff.reset();
	GNC_SwitchOff_phase = 1;
	Deploy_RIGHT_SA_post = 1;
      }
    } 
}

void orc_Mod_Deploy_RIGHT_SA::end ()
{
  fprintf( stderr, "Deploy_RIGHT_SA:: End\n" );
  Deploy_RIGHT_SA_prec = NO_EVENT;
  Deploy_RIGHT_SA_post = NO_EVENT;
  
  ADE_ReleaseHDRM_0_7_phase          = 0;
  ADE_ReleaseHDRM_0_8_phase          = 0;
  ADE_ReleaseHDRM_0_9_phase          = 0;
  SA_RIGHT_Primary_Initialise_phase   = 0;
  SA_RIGHT_Secondary_Initialise_phase = 0;
  SA_RIGHT_Primary_MoveTo_phase       = 0;
  SA_RIGHT_Secondary_MoveTo_phase     = 0;
  SA_RIGHT_Primary_MoveTo_phase       = 0;
  SA_RIGHT_Primary_SwitchOff_phase    = 0;
  SA_RIGHT_Secondary_SwitchOff_phase  = 0;
  GNC_SwitchOff_phase                = 0;

}

}

// End class orc_Mod_Deploy_RIGHT_SA

