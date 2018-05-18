#include "module_RV_Prepare4Travel.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  orc_Mod_RV_Prepare4Travel::orc_Mod_RV_Prepare4Travel (/*ModuleTask* mt,
							  int indexclk*/)
    : ModuleAlgo (/*"orc_Mod_RV_Prepare4Travel", mt, indexclk*/)
  {
    ADE_SwitchOn_phase        = 0; 
    GNC_Initialise_phase      = 0; 
    DHS_Reduced2HighPwr_phase = 0; 
    GNC_AbsLocalisation_phase = 0; 
  }
  
  orc_Mod_RV_Prepare4Travel::~orc_Mod_RV_Prepare4Travel ()
  {
    //  PRINT1( "** orc_Mod_RV_Prepare4Travel destructor" )
  }
  
  void orc_Mod_RV_Prepare4Travel::param (char *params)
  {
    
    fprintf (stderr, "RV_Prepare4Travel:: param\n");
    
    
    char start_task_event[80];
    sprintf(start_task_event, "Task_RV_Prepare4Travel_start;");
    
    //	moduleSendEvent(start_task_event);
    
    
  }
  
  void orc_Mod_RV_Prepare4Travel::reparam (char *params)
  {
    //  fprintf( stderr, "RV_Prepare4Travel:: reparam\n" );
    // #include   "RV_Prepare4Travel/user_code/reparam_code.c"
  }
  
  void orc_Mod_RV_Prepare4Travel::init ()
  {
    std::cerr << "-> RV_Prepare4Travel: start init" << std::endl;
    
    index = 0;
    
    RV_Prepare4Travel_prec = NO_EVENT;
    RV_Prepare4Travel_post = NO_EVENT;
    
    ADE_SwitchOn_phase        = 0; 
    GNC_Initialise_phase      = 0; 
    DHS_Reduced2HighPwr_phase = 0; 
    GNC_AbsLocalisation_phase = 0; 
    
    RV_Prepare4Travel_prec  = SET_EVENT;
    //	moduleSendEvent("RV_Prepare4Travel_prec;");
    
    
  }
  
  void orc_Mod_RV_Prepare4Travel::compute ()
  {

    if ( ADE_SwitchOn_phase == 0) {
      std::cerr << "ADE_SwitchOn" << std::endl;
      ADE_SwitchOn.execute("2"); 
      if (ADE_SwitchOn.ADE_SwitchOn_post == 1) {
	ADE_SwitchOn.compute_completed = 1;
      }
      if (ADE_SwitchOn.end_completed == 1) {
	ADE_SwitchOn_phase = 1;
	ADE_SwitchOn.reset();
      }
    }
    else if ( GNC_Initialise_phase == 0) {
      std::cerr << "GNC_Initialise" << std::endl;
      GNC_Initialise.execute(""); 
      if (GNC_Initialise.GNC_Initialise_post == 1) {
	GNC_Initialise.compute_completed = 1;
      }
      if (GNC_Initialise.end_completed == 1) {
	GNC_Initialise_phase = 1;
	GNC_Initialise.reset();
      }
    }
    else if ( DHS_Reduced2HighPwr_phase == 0) {
      std::cerr << "DHS_Reduced2HighPwr ()" << std::endl;
      DHS_Reduced2HighPwr.execute(""); 
      if (DHS_Reduced2HighPwr.DHS_Reduced2HighPwr_post == 1) {
	DHS_Reduced2HighPwr.compute_completed = 1;
      }
      if (DHS_Reduced2HighPwr.end_completed == 1) {
	DHS_Reduced2HighPwr_phase = 1;
	DHS_Reduced2HighPwr.reset();
      }
    }
    else if ( GNC_AbsLocalisation_phase == 0) {
      std::cerr << "GNC_AbsLocalisation ()" << std::endl;
      GNC_AbsLocalisation.execute(""); 
      if (GNC_AbsLocalisation.GNC_AbsLocalisation_post == 1) {
	GNC_AbsLocalisation.compute_completed = 1;
      }
      if (GNC_AbsLocalisation.end_completed == 1) {
	GNC_AbsLocalisation_phase = 1;
	GNC_AbsLocalisation.reset();
	RV_Prepare4Travel_post = 1;
      }
    }
    
    index ++;
  }
  
  void orc_Mod_RV_Prepare4Travel::end ()
  {
    fprintf( stderr, "RV_Prepare4Travel:: End\n" );
    RV_Prepare4Travel_prec = NO_EVENT;
    RV_Prepare4Travel_post = NO_EVENT;
    
    ADE_SwitchOn_phase        = 0; 
    GNC_Initialise_phase      = 0; 
    DHS_Reduced2HighPwr_phase = 0; 
    GNC_AbsLocalisation_phase = 0; 
    
  }
  
}

// End class orc_Mod_RV_Prepare4Travel

