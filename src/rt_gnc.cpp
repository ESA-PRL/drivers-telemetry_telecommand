#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeGNC_MonitoringOnly(){
if (param_completed == 0){
  GNC_MonitoringOnly.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  GNC_MonitoringOnly.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    GNC_MonitoringOnly.compute();
  if (  GNC_MonitoringOnly.  GNC_MonitoringOnly_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
}
int RobotTask::computeGNC_Initialise(){
if (param_completed == 0){
  GNC_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  GNC_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    GNC_Initialise.compute();
  if (  GNC_Initialise.  GNC_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    GNC_Initialise.end();
  end_completed = 1;
}
}

int RobotTask::computeGNC_SwitchOff(){
if (param_completed == 0){
  GNC_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  GNC_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    GNC_SwitchOff.compute();
  if (  GNC_SwitchOff.  GNC_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    GNC_SwitchOff.end();
  end_completed = 1;
}
}

int RobotTask::computeGNC_AbsLocalisation(){
if (param_completed == 0){
  GNC_AbsLocalisation.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  GNC_AbsLocalisation.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    GNC_AbsLocalisation.compute();
  if (  GNC_AbsLocalisation.  GNC_AbsLocalisation_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    GNC_AbsLocalisation.end();
  end_completed = 1;
}
}
