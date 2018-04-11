#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeDeploy_LEFT_SA(){
if (param_completed == 0){
  Deploy_LEFT_SA.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  Deploy_LEFT_SA.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    Deploy_LEFT_SA.compute();
  if (  Deploy_LEFT_SA.  Deploy_LEFT_SA_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    Deploy_LEFT_SA.end();
  end_completed = 1;
}
}



int RobotTask::computeDeploy_RIGHT_SA(){
if (param_completed == 0){
  Deploy_RIGHT_SA.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  Deploy_RIGHT_SA.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    Deploy_RIGHT_SA.compute();
  if (  Deploy_RIGHT_SA.  Deploy_RIGHT_SA_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    Deploy_RIGHT_SA.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Primary_Initialise(){
if (param_completed == 0){
  SA_LEFT_Primary_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Primary_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Primary_Initialise.compute();
  if (  SA_LEFT_Primary_Initialise.  SA_LEFT_Primary_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Primary_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Primary_MoveTo(){
if (param_completed == 0){
  SA_LEFT_Primary_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Primary_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Primary_MoveTo.compute();
  if (  SA_LEFT_Primary_MoveTo.  SA_LEFT_Primary_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Primary_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Primary_SwitchOff(){
if (param_completed == 0){
  SA_LEFT_Primary_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Primary_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Primary_SwitchOff.compute();
  if (  SA_LEFT_Primary_SwitchOff.  SA_LEFT_Primary_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Primary_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Secondary_Initialise(){
if (param_completed == 0){
  SA_LEFT_Secondary_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Secondary_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Secondary_Initialise.compute();
  if (  SA_LEFT_Secondary_Initialise.  SA_LEFT_Secondary_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Secondary_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Secondary_MoveTo(){
if (param_completed == 0){
  SA_LEFT_Secondary_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Secondary_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Secondary_MoveTo.compute();
  if (  SA_LEFT_Secondary_MoveTo.  SA_LEFT_Secondary_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Secondary_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_LEFT_Secondary_SwitchOff(){
if (param_completed == 0){
  SA_LEFT_Secondary_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_LEFT_Secondary_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_LEFT_Secondary_SwitchOff.compute();
  if (  SA_LEFT_Secondary_SwitchOff.  SA_LEFT_Secondary_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_LEFT_Secondary_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Primary_Initialise(){
if (param_completed == 0){
  SA_RIGHT_Primary_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Primary_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Primary_Initialise.compute();
  if (  SA_RIGHT_Primary_Initialise.  SA_RIGHT_Primary_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Primary_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Primary_MoveTo(){
if (param_completed == 0){
  SA_RIGHT_Primary_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Primary_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Primary_MoveTo.compute();
  if (  SA_RIGHT_Primary_MoveTo.  SA_RIGHT_Primary_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Primary_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Primary_SwitchOff(){
if (param_completed == 0){
  SA_RIGHT_Primary_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Primary_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Primary_SwitchOff.compute();
  if (  SA_RIGHT_Primary_SwitchOff.  SA_RIGHT_Primary_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Primary_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Secondary_Initialise(){
if (param_completed == 0){
  SA_RIGHT_Secondary_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Secondary_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Secondary_Initialise.compute();
  if (  SA_RIGHT_Secondary_Initialise.  SA_RIGHT_Secondary_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Secondary_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Secondary_MoveTo(){
if (param_completed == 0){
  SA_RIGHT_Secondary_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Secondary_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Secondary_MoveTo.compute();
  if (  SA_RIGHT_Secondary_MoveTo.  SA_RIGHT_Secondary_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Secondary_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeSA_RIGHT_Secondary_SwitchOff(){
if (param_completed == 0){
  SA_RIGHT_Secondary_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  SA_RIGHT_Secondary_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    SA_RIGHT_Secondary_SwitchOff.compute();
  if (  SA_RIGHT_Secondary_SwitchOff.  SA_RIGHT_Secondary_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    SA_RIGHT_Secondary_SwitchOff.end();
  end_completed = 1;
}
}
