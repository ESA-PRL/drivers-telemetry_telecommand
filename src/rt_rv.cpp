// KK RV_XXX methods moved from rt.cc to this new file
#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

int RobotTask::computeRV_PostComms(){
if (param_completed == 0){
  RV_PostComms.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_PostComms.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_PostComms.compute();
  if (  RV_PostComms.  RV_PostComms_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_PostComms.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_Prepare4Comms(){
if (param_completed == 0){
  RV_Prepare4Comms.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_Prepare4Comms.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_Prepare4Comms.compute();
  if (  RV_Prepare4Comms.  RV_Prepare4Comms_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_Prepare4Comms.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_Prepare4Dozing(){
if (param_completed == 0){
  RV_Prepare4Dozing.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_Prepare4Dozing.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_Prepare4Dozing.compute();
  if (  RV_Prepare4Dozing.  RV_Prepare4Dozing_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_Prepare4Dozing.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_Prepare4Night(){
if (param_completed == 0){
  RV_Prepare4Night.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_Prepare4Night.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_Prepare4Night.compute();
  if (  RV_Prepare4Night.  RV_Prepare4Night_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_Prepare4Night.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_Prepare4Science(){
if (param_completed == 0){
  RV_Prepare4Science.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_Prepare4Science.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_Prepare4Science.compute();
  if (  RV_Prepare4Science.  RV_Prepare4Science_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_Prepare4Science.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_Prepare4Travel(){
if (param_completed == 0){
  RV_Prepare4Travel.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_Prepare4Travel.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_Prepare4Travel.compute();
  if (  RV_Prepare4Travel.  RV_Prepare4Travel_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_Prepare4Travel.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_SwitchOffMobility(){
if (param_completed == 0){
  RV_SwitchOffMobility.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_SwitchOffMobility.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_SwitchOffMobility.compute();
  if (  RV_SwitchOffMobility.  RV_SwitchOffMobility_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_SwitchOffMobility.end();
  end_completed = 1;
}
}


int RobotTask::computeRV_WakeUp(){
if (param_completed == 0){
  RV_WakeUp.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  RV_WakeUp.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    RV_WakeUp.compute();
  if (  RV_WakeUp.  RV_WakeUp_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    RV_WakeUp.end();
  end_completed = 1;
}
}

int RobotTask::computeRelease_Body(){
if (param_completed == 0){
  Release_Body.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  Release_Body.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    Release_Body.compute();
  if (  Release_Body.  Release_Body_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    Release_Body.end();
  end_completed = 1;
}
}

int RobotTask::computeRelease_Umbilical(){
if (param_completed == 0){
  Release_Umbilical.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  Release_Umbilical.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    Release_Umbilical.compute();
  if (  Release_Umbilical.  Release_Umbilical_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    Release_Umbilical.end();
  end_completed = 1;
}
}
