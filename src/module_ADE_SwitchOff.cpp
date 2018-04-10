#include "module_ADE_SwitchOff.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_ADE_SwitchOff::orc_Mod_ADE_SwitchOff(/*ModuleTask* mt,
						 int indexclk*/) 
  // : ModuleAlgo("orc_Mod_ADE_SwitchOff", mt, indexclk) 
  { 
    
    rtId = 0; 
    index = 0;
    duration = 10.0;
    //    phrAde = NULL;
    ADE_SwitchOff_prec = NO_EVENT;
    ADE_SwitchOff_post = NO_EVENT;
    action_exec_status = ACTION_RET_OK;
  }
  
  orc_Mod_ADE_SwitchOff::~orc_Mod_ADE_SwitchOff() {
    
  }
  
  void orc_Mod_ADE_SwitchOff::param(char *params) {  
    // the action status is ok 
    int tmp1;
    if (1 != sscanf(params, "%d", &tmp1)) {
      std::cerr << "In ADE_SwitchOff param failed" << std::endl;
      //      theRobotProcedure->
      //	ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //			      params);
      return;
    }
    switch (tmp1) {
    case 0:
      strcpy(ade_id, "left");
      break;
    case 1:
      strcpy(ade_id, "right");
      break;
    case 2:
      strcpy(ade_id, "all");
      break;
    default:
      std::cerr << "In ADE_SwitchOff param failed" << std::endl;
      //      theRobotProcedure->
      //	ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //			      params);
      return;
    }

    
  }
  
  void orc_Mod_ADE_SwitchOff::reparam(char *params) { 
    
  }
  
  void orc_Mod_ADE_SwitchOff::init() { 
    
    index = 0;
    
    // reset the events
    ADE_SwitchOff_prec = NO_EVENT;
    ADE_SwitchOff_post = NO_EVENT;
    
    // reset the state
    for (int i = 0; i < MAX_STATE_SIZE; i++) {
      AdeState[i] = 0.0;
    }
    
    //
    // reset the resources of the robot task
    //
    /*
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(0.0);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(0.0);
    */

    //    phrAde = (orc_PhR_Ade*) (Mt_ptr->GetRobotTaskPtr()->GetPhR());
    
    //
    // check the state
    //
    if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }
    
    // set action execution information
    AdeState[ADE_ACTION_ID_INDEX] = rtId;
    AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_INITIALISING;
    
    if (theRobotProcedure->GetParameters()->set("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }
    
    //
    // the pre-conditions are satisfied
    //
    ADE_SwitchOff_prec = SET_EVENT;
    //    moduleSendEvent("ADE_SwitchOff_prec;");
  }
  
  void orc_Mod_ADE_SwitchOff::compute() { 
    
    //
    // get the global state of the ADE
    //
    if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //						  "AdeState");
    }
    
    // set action execution information
    AdeState[ADE_ACTION_ID_INDEX] = rtId;
    AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    //
    // update the resources of the robot task
    //
    /*
    double energy_cons = getModuleTaskPtr()->GetRobotTaskPtr()->getEnergyCons()
      + AdeState[ADE_LEFT_POWER_CONS_INDEX] * getSampleTime() / 60.0
      / 60.0;
    
    double memmass_cons =
      getModuleTaskPtr()->GetRobotTaskPtr()->getMemoryMassCons()
      + AdeState[ADE_DATARATE_INDEX] * getSampleTime();
    
    double act_duration = getModuleTaskPtr()->GetRobotTaskPtr()->getDuration()
      + getSampleTime();
    
    getModuleTaskPtr()->GetRobotTaskPtr()->setEnergyCons(energy_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setMemoryMassCons(memmass_cons);
    getModuleTaskPtr()->GetRobotTaskPtr()->setDuration(act_duration);
    */
    //
    // the postcondition is satisfied
    //
    if (index >= (duration) / (0.2)) {
      if (!strcmp(ade_id, "left")) {
	AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
      } else if (!strcmp(ade_id, "right")) {
	AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      } else if (!strcmp(ade_id, "all")) {
	AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OFF;
	AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OFF;
      }
      ADE_SwitchOff_post = SET_EVENT;
      //      moduleSendEvent("ADE_SwitchOff_post;");
    }
    
    //
    // set the global state
    //
    if (theRobotProcedure->GetParameters()->set("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, 
						(char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //						  "AdeState");
    }
    
    index++;
  }
  
  void orc_Mod_ADE_SwitchOff::end() { 
    ADE_SwitchOff_prec = NO_EVENT;
    ADE_SwitchOff_post = NO_EVENT;
  }

}

// End class orc_Mod_ADE_SwitchOff

