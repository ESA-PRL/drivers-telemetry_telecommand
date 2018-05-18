#include "module_MMS_WaitAbsTime.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

extern void addOffsetTime(double seconds);

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_MMS_WaitAbsTime::orc_Mod_MMS_WaitAbsTime(/*ModuleTask* mt,
						     int indexclk*/) :
    ModuleAlgo(/*"orc_Mod_MMS_WaitAbsTime", mt, indexclk*/) { 
    index=0;
  }
  
  orc_Mod_MMS_WaitAbsTime::~orc_Mod_MMS_WaitAbsTime() {
    
  }
  
  void orc_Mod_MMS_WaitAbsTime::param(char *params) {  
    if (1 != sscanf(params, "%d", &seconds)) {
      fprintf(stderr, "In MMS_WaitAbsTime::param() error in parameterisation\n");
      //      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //					       params);
      return;
    }
  }
  
  void orc_Mod_MMS_WaitAbsTime::reparam(char *params) { 
    
  }
  
  void orc_Mod_MMS_WaitAbsTime::init() { 
    
    index=0;
    MMS_WaitAbsTime_prec = NO_EVENT;
    MMS_WaitAbsTime_post = NO_EVENT;
    
    final_time = seconds; 
    
    //
    // the precondition is satisfied
    //
    MMS_WaitAbsTime_prec = SET_EVENT;
    // moduleSendEvent("MMS_WaitAbsTime_prec;");
  }
  
  void orc_Mod_MMS_WaitAbsTime::compute() { 

    // std::cerr << "orc_Mod_MMS_WaitAbsTime::compute()" << std::endl;
    
    //
    // check if the time is reached
    //
    if (index > 10) {
      addOffsetTime(seconds-2.0);
      MMS_WaitAbsTime_post = SET_EVENT;
      // moduleSendEvent("MMS_WaitAbsTime_post;");
    }
    index++;
  }
  
  void orc_Mod_MMS_WaitAbsTime::end() { 
    MMS_WaitAbsTime_prec = NO_EVENT;
    MMS_WaitAbsTime_post = NO_EVENT;
  }
  
}

// End class orc_Mod_MMS_WaitAbsTime

