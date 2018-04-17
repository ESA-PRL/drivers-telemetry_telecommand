#include "module_Release_Body.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_Release_Body::orc_Mod_Release_Body(/*ModuleTask* mt,
					       int indexclk*/) :
    ModuleAlgo(/*"orc_Mod_Release_Body", mt, indexclk*/) { 
    
    GNC_MonitoringOnly_phase = 0;
    ADE_ReleaseHDRM_0_18_phase = 0;
    ADE_ReleaseHDRM_0_19_phase = 0;
    ADE_ReleaseHDRM_0_20_phase = 0;
    GNC_SwitchOff_phase = 0;
  }
  
  orc_Mod_Release_Body::~orc_Mod_Release_Body() {
    
  }
  
  void orc_Mod_Release_Body::param(char *params) { 
    std::cerr << "orc_Mod_Release_Body: param" << std::endl; 

    char start_task_event[80];
    sprintf(start_task_event, "Release_Body_Start;");
    
    // moduleSendEvent(start_task_event);
  }

  void orc_Mod_Release_Body::reparam(char *params) { 
    
  }
  
  void orc_Mod_Release_Body::init() { 
    std::cerr << "orc_Mod_Release_Body: init" << std::endl; 
    
	index = 0;

	Release_Body_prec = NO_EVENT;
	Release_Body_post = NO_EVENT;
	/*
	getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
	getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
	*/

  }
  
  // GNC_MonitoringOnly
  // ADE_ReleaseHDRM(0, 18) - HDRM_Release(18,2,0,120,200,0)
  // ADE_ReleaseHDRM(0, 19) - HDRM_Release(19,2,0,120,200,0)
  // ADE_ReleaseHDRM(0, 20) - HDRM_Release(20,2,0,120,200,0)
  // GNC_SwitchOff

  void orc_Mod_Release_Body::compute() { 
    
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
    else if ( ADE_ReleaseHDRM_0_18_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM" << std::endl;
      ADE_ReleaseHDRM.execute("0 18"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_18_phase = 1;
      }
    }
    else if ( ADE_ReleaseHDRM_0_19_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM" << std::endl;
      ADE_ReleaseHDRM.execute("0 19"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_19_phase = 1;
      }
    }
    else if ( ADE_ReleaseHDRM_0_20_phase == 0) {
      std::cerr << "ADE_ReleaseHDRM" << std::endl;
      ADE_ReleaseHDRM.execute("0 20"); 
      if (ADE_ReleaseHDRM.ADE_ReleaseHDRM_post == 1) {
	ADE_ReleaseHDRM.compute_completed = 1;
      }
      if (ADE_ReleaseHDRM.end_completed == 1) {
	ADE_ReleaseHDRM.reset();
	ADE_ReleaseHDRM_0_20_phase = 1;
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
	Release_Body_post = 1;
      }
    }
    index++;
    
  }
  
  void orc_Mod_Release_Body::end() { 
    std::cerr << "orc_Mod_Release_Body: end" << std::endl;
    
    Release_Body_prec = NO_EVENT;
    Release_Body_post = NO_EVENT;

    GNC_MonitoringOnly_phase = 0;
    ADE_ReleaseHDRM_0_18_phase = 0;
    ADE_ReleaseHDRM_0_19_phase = 0;
    ADE_ReleaseHDRM_0_20_phase = 0;
    GNC_SwitchOff_phase = 0;
  }
  
}

// End class orc_Mod_Release_Body

