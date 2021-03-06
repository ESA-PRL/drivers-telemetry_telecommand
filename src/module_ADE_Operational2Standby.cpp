#include "module_ADE_Operational2Standby.h"
#include "prr.h"

extern RobotProcedure *theRobotProcedure;

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_ADE_Operational2Standby::orc_Mod_ADE_Operational2Standby(/*ModuleTask* mt,
								     int indexclk*/) 
    : ModuleAlgo(/*"orc_Mod_ADE_Operational2Standby", mt, indexclk*/) 
  { 
    
  }
  
  orc_Mod_ADE_Operational2Standby::~orc_Mod_ADE_Operational2Standby() {
  }
  
  void orc_Mod_ADE_Operational2Standby::param(char *params) {  
    // the action status is ok 
    
    int adeid_int = 0;
    if (1 != sscanf(params, "%d", &adeid_int)) {
      //    theRobotProcedure->
      //      ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), 
      //			    params);
      return;
    }
    
    strcpy(target_mode, "STANDBY");
    if (adeid_int == 0) {
      strcpy(ade_id, "left");
    }
    else {
      strcpy(ade_id, "right");
    }
    
  }
  
  void orc_Mod_ADE_Operational2Standby::reparam(char *params) { 
    
  }
  
  void orc_Mod_ADE_Operational2Standby::init() { 
    index = 0;

	ADE_Operational2Standby_prec = NO_EVENT;
	ADE_Operational2Standby_post = NO_EVENT;

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

	//	phrAde = (orc_PhR_Ade*) (Mt_ptr->GetRobotTaskPtr()->GetPhR());

	//
	// get the global state
	//
	if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						    MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //				Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
	}

	//
	// check the preconditions
	//

	if (!strcmp(target_mode, "STANDBY")) {
	}
	else if (!strcmp(target_mode, "OPERATIONAL")) {
	}
	else {
	  //	  theRobotProcedure->ExitOnParamValueError(
	  //						   (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str(),
	  //						   target_mode);
	}
	/*
	if (!strcmp(target_mode, "STANDBY")) {
	  if (AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_STNDBY_HDRM
	      && AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_OP_MOTORS
	      && AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_STNDBY) {
	    
	    PhR_Ade->stateTransitionError(AdeState[ADE_STATUS_LEFT_INDEX],
					  ADE_OPER_MODE_STNDBY_HDRM,
					  (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str());
	    theRobotProcedure->ExitOnInitialStateError();
	  }
	} else if (!strcmp(target_mode, "OPERATIONAL")) {
	  if (AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_STNDBY
	      && AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_OP_MOTORS) {
	    PhR_Ade->stateTransitionError(AdeState[ADE_STATUS_LEFT_INDEX],
					  ADE_OPER_MODE_STNDBY,
					  (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str());
	    theRobotProcedure->ExitOnInitialStateError();
	  }
	} else if (!strcmp(target_mode, "HDRM")) {
	  if (AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_STNDBY) {
	    PhR_Ade->stateTransitionError(AdeState[ADE_STATUS_LEFT_INDEX],
					  ADE_OPER_MODE_STNDBY,
					  (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str());
	    theRobotProcedure->ExitOnInitialStateError();
	  }
	} else {
	  theRobotProcedure->ExitOnParamValueError(
						   (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str(),
						   (char *) "configuration mode error");
	}
	
	*/
	//
	// Identify the duration function of the target mode.
	// The target modes are: reduced, nominal, highpower,
	// lowpower, recovery
	//
	if (!strcmp(target_mode, "STANDBY")) {
		duration = 1.0; // CL 04032016 change duration from 5 to 1 sec 5.0; // sec
		target_mode_id = ADE_OPER_MODE_STNDBY;
	} else if (!strcmp(target_mode, "OPERATIONAL")) {
		duration = 1.0; // CL 04032016 change duration from 5 to 1 sec 5.0; // sec
		target_mode_id = ADE_OPER_MODE_OP_MOTORS;
	} else {
	  //	  theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
	  //						   target_mode);
	  return;
	}

	//
	// Indicate that the preconditions are satisfied
	//
	ADE_Operational2Standby_prec = SET_EVENT;
	//	moduleSendEvent("ADE_Operational2Standby_prec;");
  }
  
  void orc_Mod_ADE_Operational2Standby::compute() { 
    	// Get Action ID
    rtId = 74; // Mt_ptr->GetRobotTaskPtr()->GetId();

	//
	// get the global state
	//
	if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
	MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //				Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
	}

	// Set Action ID and Ret val
	AdeState[ADE_ACTION_ID_INDEX] = rtId;
	AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;

	if (index >= (duration / 0.2)) {
		if (!strcmp(ade_id, "left")) {
			AdeState[ADE_STATUS_LEFT_INDEX] = target_mode_id;
		} else if (!strcmp(ade_id, "right")) {
			AdeState[ADE_STATUS_RIGHT_INDEX] = target_mode_id;
		} else if (!strcmp(ade_id, "all")) {
			AdeState[ADE_STATUS_LEFT_INDEX] = target_mode_id;
			AdeState[ADE_STATUS_RIGHT_INDEX] = target_mode_id;
		}

		// Set Action ID and Ret val
		AdeState[ADE_ACTION_ID_INDEX] = 0;
		AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;

		ADE_Operational2Standby_post = SET_EVENT;
		//		moduleSendEvent("ADE_Operational2Standby_post;");
	}

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
	// set the global state
	//
	if (theRobotProcedure->GetParameters()->set("AdeState", DOUBLE,
	MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
	  //		theRobotProcedure->ExitOnMissingStateSymbol(
	  //				Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
	}

	index++;

  }

  void orc_Mod_ADE_Operational2Standby::end() { 
    ADE_Operational2Standby_prec = NO_EVENT;
    ADE_Operational2Standby_post = NO_EVENT;
  }
  
}

// End class orc_Mod_ADE_Operational2Standby

