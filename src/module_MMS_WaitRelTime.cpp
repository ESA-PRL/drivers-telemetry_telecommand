#include "module_MMS_WaitRelTime.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {


  orc_Mod_MMS_WaitRelTime::orc_Mod_MMS_WaitRelTime(/*ModuleTask* mt,
						     int indexclk*/) :
    ModuleAlgo(/*"orc_Mod_MMS_WaitRelTime", mt, indexclk*/) { 
    
  }
  
  orc_Mod_MMS_WaitRelTime::~orc_Mod_MMS_WaitRelTime() {
    
  }
  
  void orc_Mod_MMS_WaitRelTime::param(char *params) {  
    if (1 != sscanf(params, "%lf", &waitTime)) {
      fprintf(stderr, "In WaitTime::param() error in parameterisation\n");
      //      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //					       params);
      return;
    }
  }
  
  void orc_Mod_MMS_WaitRelTime::reparam(char *params) { 
    
  }
  
  void orc_Mod_MMS_WaitRelTime::init() { 
    index = 0;
    
    MMS_WaitRelTime_prec = NO_EVENT;
    MMS_WaitRelTime_post = NO_EVENT;
    
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
    */

    //
    // the precondition is satisfied
    //
    MMS_WaitRelTime_prec = SET_EVENT;
    
    // send the pre-condition
    //    moduleSendEvent("MMS_WaitRelTime_prec;");
  }
  
  void orc_Mod_MMS_WaitRelTime::compute() { 

    //    std::cerr << "orc_Mod_MMS_WaitRelTime::compute()" << std::endl;

    // Get Action ID
    rtId = 0; // Mt_ptr->GetRobotTaskPtr()->GetId();
    
    //
    // check if the time is reached
    //
    if (index
	>= ( waitTime / (theRobotProcedure->GetClock()->GetBasePeriod()))) {
      
      MMS_WaitRelTime_post = SET_EVENT;
      // moduleSendEvent("MMS_WaitRelTime_post;");
    }
      
    /*
    double act_duration =
      getModuleTaskPtr()->GetRobotTaskPtr()->getDuration() + getSampleTime();
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */

    index ++;
  }
  
  void orc_Mod_MMS_WaitRelTime::end() { 
    MMS_WaitRelTime_prec = NO_EVENT;
    MMS_WaitRelTime_post = NO_EVENT;
  }
  
}

// End class orc_Mod_MMS_WaitRelTime

