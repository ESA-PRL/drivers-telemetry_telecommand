#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;


int RobotTask::computeMMS_WaitAbsTime(){
if (param_completed == 0){
  MMS_WaitAbsTime.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MMS_WaitAbsTime.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MMS_WaitAbsTime.compute();
  if (  MMS_WaitAbsTime.  MMS_WaitAbsTime_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MMS_WaitAbsTime.end();
  end_completed = 1;
}
}


int RobotTask::computeMMS_WaitRelTime(){
if (param_completed == 0){
  MMS_WaitRelTime.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  MMS_WaitRelTime.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    MMS_WaitRelTime.compute();
  if (  MMS_WaitRelTime.  MMS_WaitRelTime_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    MMS_WaitRelTime.end();
  end_completed = 1;
}
}
