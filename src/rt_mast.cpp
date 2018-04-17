#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeDeploy_Mast(){
if (param_completed == 0){
  Deploy_Mast.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  Deploy_Mast.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    Deploy_Mast.compute();
  if (  Deploy_Mast.  Deploy_Mast_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    Deploy_Mast.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_DEP_Initialise(){
if (param_completed == 0){
  MAST_DEP_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_DEP_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_DEP_Initialise.compute();
  if (  MAST_DEP_Initialise.  MAST_DEP_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_DEP_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_DEP_MoveTo(){
if (param_completed == 0){
  MAST_DEP_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_DEP_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_DEP_MoveTo.compute();
  if (  MAST_DEP_MoveTo.  MAST_DEP_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_DEP_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_DEP_SwitchOff(){
if (param_completed == 0){
  MAST_DEP_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_DEP_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_DEP_SwitchOff.compute();
  if (  MAST_DEP_SwitchOff.  MAST_DEP_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_DEP_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_PAN_Initialise(){
if (param_completed == 0){
  MAST_PAN_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_PAN_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_PAN_Initialise.compute();
  if (  MAST_PAN_Initialise.  MAST_PAN_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_PAN_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_PAN_MoveTo(){
if (param_completed == 0){
  MAST_PAN_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_PAN_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_PAN_MoveTo.compute();
  if (  MAST_PAN_MoveTo.  MAST_PAN_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_PAN_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_PAN_SwitchOff(){
if (param_completed == 0){
  MAST_PAN_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_PAN_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_PAN_SwitchOff.compute();
  if (  MAST_PAN_SwitchOff.  MAST_PAN_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_PAN_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_PTU_MoveTo(){
if (param_completed == 0){
  MAST_PTU_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_PTU_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_PTU_MoveTo.compute();
  if (  MAST_PTU_MoveTo.  MAST_PTU_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_PTU_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_TILT_Initialise(){
if (param_completed == 0){
  MAST_TILT_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_TILT_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_TILT_Initialise.compute();
  if (  MAST_TILT_Initialise.  MAST_TILT_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_TILT_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_TILT_MoveTo(){
if (param_completed == 0){
  MAST_TILT_MoveTo.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_TILT_MoveTo.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_TILT_MoveTo.compute();
  if (  MAST_TILT_MoveTo.  MAST_TILT_MoveTo_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_TILT_MoveTo.end();
  end_completed = 1;
}
}


int RobotTask::computeMAST_TILT_SwitchOff(){
if (param_completed == 0){
  MAST_TILT_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MAST_TILT_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MAST_TILT_SwitchOff.compute();
  if (  MAST_TILT_SwitchOff.  MAST_TILT_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MAST_TILT_SwitchOff.end();
  end_completed = 1;
}
}
