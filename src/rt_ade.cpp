#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeADE_Operational2Standby(){
if (param_completed == 0){
  ADE_Operational2Standby.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADE_Operational2Standby.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADE_Operational2Standby.compute();
  if (  ADE_Operational2Standby.  ADE_Operational2Standby_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADE_Operational2Standby.end();
  end_completed = 1;
}
}


int RobotTask::computeADE_Standby2Operational(){
if (param_completed == 0){
  ADE_Standby2Operational.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADE_Standby2Operational.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADE_Standby2Operational.compute();
  if (  ADE_Standby2Operational.  ADE_Standby2Operational_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADE_Standby2Operational.end();
  end_completed = 1;
}
}


int RobotTask::computeADE_SwitchOn(){
if (param_completed == 0){
  ADE_SwitchOn.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADE_SwitchOn.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADE_SwitchOn.compute();
  if (  ADE_SwitchOn.  ADE_SwitchOn_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADE_SwitchOn.end();
  end_completed = 1;
}
}


int RobotTask::computeADE_SwitchOff(){
if (param_completed == 0){
  ADE_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADE_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADE_SwitchOff.compute();
  if (  ADE_SwitchOff.  ADE_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADE_SwitchOff.end();
  end_completed = 1;
}
}

int RobotTask::computeADEs_Activate(){
if (param_completed == 0){
  ADEs_Activate.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADEs_Activate.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADEs_Activate.compute();
  if (  ADEs_Activate.  ADEs_Activate_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADEs_Activate.end();
  end_completed = 1;
}
}


int RobotTask::computeADEs_DeActivate(){
if (param_completed == 0){
  ADEs_DeActivate.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADEs_DeActivate.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADEs_DeActivate.compute();
  if (  ADEs_DeActivate.  ADEs_DeActivate_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADEs_DeActivate.end();
  end_completed = 1;
}
}


int RobotTask::computeADE_ReleaseHDRM(){
if (param_completed == 0){
  ADE_ReleaseHDRM.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  ADE_ReleaseHDRM.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    ADE_ReleaseHDRM.compute();
  if (  ADE_ReleaseHDRM.  ADE_ReleaseHDRM_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    ADE_ReleaseHDRM.end();
  end_completed = 1;
}
}

int RobotTask::computeHDRM_Release(){
if (param_completed == 0){
  HDRM_Release.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  HDRM_Release.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    HDRM_Release.compute();
  if (  HDRM_Release.  HDRM_Release_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    HDRM_Release.end();
  end_completed = 1;
}
}
