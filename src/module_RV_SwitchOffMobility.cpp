#include "module_RV_SwitchOffMobility.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_RV_SwitchOffMobility::orc_Mod_RV_SwitchOffMobility(/*ModuleTask* mt,
							       int indexclk*/) :
    ModuleAlgo(/*"orc_Mod_RV_SwitchOffMobility", mt, indexclk*/) { 
    
    GNC_SwitchOff_phase = 0;
    ADE_SwitchOff_phase = 0;
    DHS_HighPwr2Reduced_phase = 0;
  }
  
  orc_Mod_RV_SwitchOffMobility::~orc_Mod_RV_SwitchOffMobility() {
    
  }
  
  void orc_Mod_RV_SwitchOffMobility::param(char *params) {  
    std::cerr << "-> RV_SwitchOffMobility:param" << std::endl;
    
    char start_task_event[80];
    sprintf(start_task_event, "Task_RV_SwitchOffMobility_start;");
    
    // moduleSendEvent(start_task_event);
    
  }
  
  void orc_Mod_RV_SwitchOffMobility::reparam(char *params) { 
    
  }
  
  void orc_Mod_RV_SwitchOffMobility::init() { 
    std::cerr << "-> RV_SwitchOffMobility:init" << std::endl;
    index = 0;
    
    RV_SwitchOffMobility_prec = NO_EVENT;
    RV_SwitchOffMobility_post = NO_EVENT;
    
    GNC_SwitchOff_phase = 0;
    ADE_SwitchOff_phase = 0;
    DHS_HighPwr2Reduced_phase = 0;
    
    RV_SwitchOffMobility_prec  = SET_EVENT;
    //	moduleSendEvent("RV_SwitchOffMobility_prec;");
    
  }
  
  void orc_Mod_RV_SwitchOffMobility::compute() { 
    //  std::cerr << "-> RV_SwitchOffMobility: start compute" << std::endl;

    if ( ADE_SwitchOff_phase == 0) {
      std::cerr << "ADE_SwitchOff (2)" << std::endl;
      ADE_SwitchOff.execute("2"); 
      if (ADE_SwitchOff.ADE_SwitchOff_post == 1) {
	ADE_SwitchOff.compute_completed = 1;
      }
      if (ADE_SwitchOff.end_completed == 1) {
	ADE_SwitchOff.reset();
	ADE_SwitchOff_phase = 1;
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
      }
    }
    else if ( DHS_HighPwr2Reduced_phase == 0) {
      std::cerr << "DHS_HighPwr2Reduced ()" << std::endl;
      DHS_HighPwr2Reduced.execute(""); 
      if (DHS_HighPwr2Reduced.DHS_HighPwr2Reduced_post == 1) {
	DHS_HighPwr2Reduced.compute_completed = 1;
      }
      if (DHS_HighPwr2Reduced.end_completed == 1) {
	DHS_HighPwr2Reduced_phase = 1;
	DHS_HighPwr2Reduced.reset();
	RV_SwitchOffMobility_post = 1;
      }
    }

    index ++;
  }
  
  void orc_Mod_RV_SwitchOffMobility::end() { 
    std::cerr << "-> RV_SwitchOffMobility:end" << std::endl;
    RV_SwitchOffMobility_prec = NO_EVENT;
    RV_SwitchOffMobility_post = NO_EVENT;
    
    GNC_SwitchOff_phase = 0;
    ADE_SwitchOff_phase = 0;
    DHS_HighPwr2Reduced_phase = 0;
  }

}

// End class orc_Mod_RV_SwitchOffMobility

