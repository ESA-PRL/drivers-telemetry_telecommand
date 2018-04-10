#include "rt.h"
#include "param.h"
#include "prr.h"
#include "ctrl_state.h"

//#include "module_COMMS_LST2WH.h"
//#include "module_COMMS_SwitchOff.h"
//#include "module_COMMS_SwitchOn.h"
//#include "module_COMMS_WH2LST.h"

extern RobotProcedure*  theRobotProcedure;

using namespace ControllerModelNamespace;

int RobotTask::computeCOMMS_LST2WH(){
if (param_completed == 0){
  COMMS_LST2WH.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  COMMS_LST2WH.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    COMMS_LST2WH.compute();
  if (  COMMS_LST2WH.  COMMS_LST2WH_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    COMMS_LST2WH.end();
  end_completed = 1;
}
}


int RobotTask::computeCOMMS_SwitchOff(){
if (param_completed == 0){
  COMMS_SwitchOff.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  COMMS_SwitchOff.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    COMMS_SwitchOff.compute();
  if (  COMMS_SwitchOff.  COMMS_SwitchOff_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    COMMS_SwitchOff.end();
  end_completed = 1;
}
}


int RobotTask::computeCOMMS_SwitchOn(){
if (param_completed == 0){
  COMMS_SwitchOn.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  COMMS_SwitchOn.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    COMMS_SwitchOn.compute();
  if (  COMMS_SwitchOn.  COMMS_SwitchOn_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    COMMS_SwitchOn.end();
  end_completed = 1;
}
}


int RobotTask::computeCOMMS_WH2LST(){
if (param_completed == 0){
  COMMS_WH2LST.param(rtParams);
  param_completed = 1;
}
if (param_completed == 1 && init_completed == 0){
  COMMS_WH2LST.init();
  init_completed = 1;
}
if (init_completed == 1 && compute_completed == 0){
    COMMS_WH2LST.compute();
  if (  COMMS_WH2LST.  COMMS_WH2LST_post == 1)
  {
    post_cond = 1;
    compute_completed = 1;
  }
}
if (compute_completed == 1 && end_completed == 0){
    COMMS_WH2LST.end();
  end_completed = 1;
}
}
