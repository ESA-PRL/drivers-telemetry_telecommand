#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

// KK Updated for egress experiments

extern RobotProcedure*  theRobotProcedure;


int RobotTask::computePanCam_Initialise(){
if (param_completed == 0){
  PanCam_Initialise.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  PanCam_Initialise.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    PanCam_Initialise.compute();
  if (  PanCam_Initialise.  PanCam_Initialise_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    PanCam_Initialise.end();
  end_completed = 1;
}
}


int RobotTask::computePanCam_PIUSwitchOff(){
if (param_completed == 0){
  PanCam_PIUSwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  PanCam_PIUSwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    PanCam_PIUSwitchOff.compute();
  if (  PanCam_PIUSwitchOff.  PanCam_PIUSwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    PanCam_PIUSwitchOff.end();
  end_completed = 1;
}
}
