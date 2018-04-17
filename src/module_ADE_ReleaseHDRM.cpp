#include "module_ADE_ReleaseHDRM.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  
  orc_Mod_ADE_ReleaseHDRM::orc_Mod_ADE_ReleaseHDRM(/*ModuleTask* mt,
						     int indexclk*/) :
    ModuleAlgo(/*"orc_Mod_ADE_ReleaseHDRM", mt, indexclk*/) {
    
    rtId = 73;
    index = 0;
    duration = 0.0;
    //    PhR_Ade = NULL;
    ADE_ReleaseHDRM_prec = NO_EVENT;
    ADE_ReleaseHDRM_post = NO_EVENT;
  }
  
  orc_Mod_ADE_ReleaseHDRM::~orc_Mod_ADE_ReleaseHDRM() {
  }
  
  void orc_Mod_ADE_ReleaseHDRM::param(char *params) {
    fprintf( stderr, "ADE_ReleaseHDRM:: Param\n" );
    if (2 != sscanf(params, "%d %d", &adeId, &hdrmId)) {
      fprintf(stderr, "In ADE_ReleaseHDRM::param() error in parameterisation\n");
      //      theRobotProcedure->ExitOnParamValueError(Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(),
      //					       params);
      return;
    }
  }
  
  void orc_Mod_ADE_ReleaseHDRM::reparam(char *params) {
    
  }
  
  void orc_Mod_ADE_ReleaseHDRM::init() {
    
    fprintf( stderr, "ADE_ReleaseHDRM:: Init\n" );
    index = 0;
    
    ADE_ReleaseHDRM_prec = NO_EVENT;
    ADE_ReleaseHDRM_post = NO_EVENT;
    
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
    
    //    PhR_Ade = (orc_PhR_Ade*) (Mt_ptr->GetRobotTaskPtr()->GetPhR());
    
    //
    // get the global state
    //
    if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }
    
    //
    // check the preconditions
    //
    /*
      if (AdeState[ADE_STATUS_LEFT_INDEX] != ADE_OPER_MODE_STNDBY_HDRM) {
      PhR_Ade->stateTransitionError(AdeState[ADE_STATUS_LEFT_INDEX],
      ADE_OPER_MODE_STNDBY_HDRM,
      (Mt_ptr->GetRobotTaskPtr()->GetMnemonic()).c_str());
      theRobotProcedure->ExitOnInitialStateError();
      }
    */
    duration = 10.0;
    
    //
    // Indicate that the preconditions are satisfied
    //
    ADE_ReleaseHDRM_prec = SET_EVENT;
    //    moduleSendEvent("ADE_ReleaseHDRM_prec;");
  }
  
  void orc_Mod_ADE_ReleaseHDRM::compute() {
    
    // get Action ID
    rtId = 0; //Mt_ptr->GetRobotTaskPtr()->GetId();
    
    //
    // get the global state
    //
    if (theRobotProcedure->GetParameters()->get("AdeState", DOUBLE,
						MAX_STATE_SIZE, 0, (char *) AdeState) == ERROR) {
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }
    
    if (adeId == 0) {
      AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } 
    else {
      AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_OP_HDRM;
    } 
    
    // Set Action ID and Ret val
    AdeState[ADE_ACTION_ID_INDEX] = rtId;
    AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_RUNNING;
    
    if (index
	>= (duration / (theRobotProcedure->GetClock()->GetBasePeriod()))) {

      if (adeId == 0) {
	AdeState[ADE_STATUS_LEFT_INDEX] = ADE_OPER_MODE_STNDBY;
      } 
      else {
	AdeState[ADE_STATUS_RIGHT_INDEX] = ADE_OPER_MODE_STNDBY;
      } 

      switch (hdrmId) {
      case 0: 
	AdeState[HDRM_DMA_1_INDEX]    = 1.0;
	break;
      case 1: 
	AdeState[HDRM_DMA_2_INDEX]    = 1.0;
	break;
      case 2: 
	AdeState[HDRM_DRILL_L_INDEX]  = 1.0;
	break;
      case 3: 
	AdeState[HDRM_DRILL_R_INDEX]  = 1.0;
	break;
      case 4: 
	AdeState[HDRM_SA_LFI_INDEX]   = 1.0;
	break;
      case 5: 
	AdeState[HDRM_SA_LFO_INDEX]   = 1.0;
	break;
      case 6: 
	AdeState[HDRM_SA_LRI_INDEX]   = 1.0;
	break;
      case 7: 
	AdeState[HDRM_SA_RFI_INDEX]   = 1.0;
	break;
      case 8: 
	AdeState[HDRM_SA_RFO_INDEX]   = 1.0;
	break;
      case 9: 
	AdeState[HDRM_SA_RRI_INDEX]   = 1.0;
	break;
      case 10: 
	AdeState[HDRM_UMB_L_INDEX]    = 1.0;
	break;
      case 11: 
	AdeState[HDRM_UMB_R_INDEX]    = 1.0;
	break;
      case 12: 
	AdeState[HDRM_WHEEL_LF_INDEX] = 1.0;
	break;
      case 13: 
	AdeState[HDRM_WHEEL_LM_INDEX] = 1.0;
	break;
      case 14: 
	AdeState[HDRM_WHEEL_LR_INDEX] = 1.0;
	break;
      case 15: 
	AdeState[HDRM_WHEEL_RF_INDEX] = 1.0;
	break;
      case 16: 
	AdeState[HDRM_WHEEL_RM_INDEX] = 1.0;
	break;
      case 17: 
	AdeState[HDRM_WHEEL_RR_INDEX] = 1.0;
	break;
      case 18: 
	AdeState[HDRM_BODY_LF_INDEX]  = 1.0;
	break;
      case 19: 
	AdeState[HDRM_BODY_RF_INDEX]  = 1.0;
	break;
      case 20: 
	AdeState[HDRM_BODY_R_INDEX]   = 1.0;
	break;
      }
      
      // Set Action ID and Ret val
      AdeState[ADE_ACTION_ID_INDEX] = 0;
      AdeState[ADE_ACTION_RET_INDEX] = ACTION_RET_OK;
      
      
      ADE_ReleaseHDRM_post = SET_EVENT;
      //      moduleSendEvent("ADE_ReleaseHDRM_post;");
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
      //      theRobotProcedure->ExitOnMissingStateSymbol(
      //						  Mt_ptr->GetRobotTaskPtr()->GetMnemonic().c_str(), "AdeState");
    }
    
    index++;
    
  }
  
  void orc_Mod_ADE_ReleaseHDRM::end() {
    fprintf( stderr, "ADE_ReleaseHDRM:: End\n" );
    ADE_ReleaseHDRM_prec = NO_EVENT;
    ADE_ReleaseHDRM_post = NO_EVENT;
    
  }
  
}

// End class orc_Mod_ADE_ReleaseHDRM

