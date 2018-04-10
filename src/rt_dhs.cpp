#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

//#include "module_DHS_HighPwr2Reduced.h"
//#include "module_DHS_LowPwr2Reduced.h"
//#include "module_DHS_Nominal2Reduced.h"
//#include "module_DHS_Reduced2HighPwr.h"
//#include "module_DHS_Reduced2LowPwr.h"
//#include "module_DHS_Reduced2Nominal.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeDHS_HighPwr2Reduced(){
if (param_completed == 0){
  DHS_HighPwr2Reduced.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_HighPwr2Reduced.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_HighPwr2Reduced.compute();
  if (  DHS_HighPwr2Reduced.  DHS_HighPwr2Reduced_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_HighPwr2Reduced.end();
  end_completed = 1;
}
}


int RobotTask::computeDHS_LowPwr2Reduced(){
if (param_completed == 0){
  DHS_LowPwr2Reduced.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_LowPwr2Reduced.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_LowPwr2Reduced.compute();
  if (  DHS_LowPwr2Reduced.  DHS_LowPwr2Reduced_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_LowPwr2Reduced.end();
  end_completed = 1;
}
}


int RobotTask::computeDHS_Nominal2Reduced(){
if (param_completed == 0){
  DHS_Nominal2Reduced.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_Nominal2Reduced.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_Nominal2Reduced.compute();
  if (  DHS_Nominal2Reduced.  DHS_Nominal2Reduced_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_Nominal2Reduced.end();
  end_completed = 1;
}
}


int RobotTask::computeDHS_Reduced2HighPwr(){
if (param_completed == 0){
  DHS_Reduced2HighPwr.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_Reduced2HighPwr.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_Reduced2HighPwr.compute();
  if (  DHS_Reduced2HighPwr.  DHS_Reduced2HighPwr_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_Reduced2HighPwr.end();
  end_completed = 1;
}
}


int RobotTask::computeDHS_Reduced2LowPwr(){
if (param_completed == 0){
  DHS_Reduced2LowPwr.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_Reduced2LowPwr.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_Reduced2LowPwr.compute();
  if (  DHS_Reduced2LowPwr.  DHS_Reduced2LowPwr_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_Reduced2LowPwr.end();
  end_completed = 1;
}
}


int RobotTask::computeDHS_Reduced2Nominal(){
if (param_completed == 0){
  DHS_Reduced2Nominal.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  DHS_Reduced2Nominal.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    DHS_Reduced2Nominal.compute();
  if (  DHS_Reduced2Nominal.  DHS_Reduced2Nominal_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    DHS_Reduced2Nominal.end();
  end_completed = 1;
}
}
