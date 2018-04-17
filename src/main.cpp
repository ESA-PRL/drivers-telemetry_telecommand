
#include <stdio.h>
#include "prr.h"
#include "comm.h"
#include "RobotProcedure.h"
#include "rt.h"
#include "ActiveMQTCReceiver.h"

ActiveMQTCReceiver* activemqTCReceiver = 0;

int main() {

  theRobotProcedure = new RobotProcedure ("rpr");
  RobotTask *rt;
  // rt = new RobotTask("RV_WakeUp"); rt->SetParam("");
  // rt = new RobotTask("MMS_WaitAbsTime"); rt->SetParam("100.0"); // TODO
  // rt = new RobotTask("MMS_WaitRelTime"); rt->SetParam("10.0"); 
  // rt = new RobotTask("GNC_MonitoringOnly"); rt->SetParam("");
  // rt = new RobotTask("ADEs_Activate"); rt->SetParam("3 3 10800 -50 10800"); 
  // rt = new RobotTask("ADEs_DeActivate"); rt->SetParam("3000"); 
  // rt = new RobotTask("PanCam_Initialise"); rt->SetParam("1 1 1"); 
  // rt = new RobotTask("PanCam_PIUSwitchOff"); rt->SetParam("1 1"); 
  // rt = new RobotTask("LocCam_TakeStereoImage"); rt->SetParam(""); // TODO
  // rt = new RobotTask("PanCam_TakeStereoImage"); rt->SetParam(""); // TODO
  // rt = new RobotTask("GNC_SwitchOff"); rt->SetParam(""); 
  // rt = new RobotTask("RV_Prepare4Night"); rt->SetParam("");
  // rt = new RobotTask("Deploy_Mast"); rt->SetParam("");
  // rt = new RobotTask("MAST_PAN_Initialise"); rt->SetParam("7200 0");
  // rt = new RobotTask("MAST_PTU_MoveTo"); rt->SetParam("45 45"); Implemented
  // rt = new RobotTask("MAST_DEP_SwitchOff"); rt->SetParam("");
  // rt = new RobotTask("MAST_PAN_SwitchOff"); rt->SetParam("");
  // rt = new RobotTask("MAST_TILT_SwitchOff"); rt->SetParam("");
  // rt = new RobotTask("Release_Body"); rt->SetParam("");    
  // rt = new RobotTask("Deploy_BEMA_pt1"); rt->SetParam(""); // TODO 
  // rt = new RobotTask("Deploy_BEMA_pt2"); rt->SetParam(""); // TODO 
  // rt = new RobotTask("Deploy_BEMA_pt3"); rt->SetParam(""); // TODO 
  // rt = new RobotTask("Deploy_LEFT_SA"); rt->SetParam("");  
  // rt = new RobotTask("Deploy_RIGHT_SA"); rt->SetParam(""); 
  // rt = new RobotTask("Release_Umbilical"); rt->SetParam(""); 
  // rt = new RobotTask("GNC_AbsLocalisation"); rt->SetParam(""); 
  // rt = new RobotTask("RV_Prepare4Travel"); rt->SetParam("");
  // rt = new RobotTask("RV_SwitchOffMobility"); rt->SetParam("");
  // rt = new RobotTask("Release_Umbilical"); rt->SetParam("");  
  // rt = new RobotTask("HDRM_Release"); rt->SetParam("");       // TODO the content
  // rt = new RobotTask("ADE_ReleaseHDRM"); rt->SetParam("0 2"); 
  rt->Control ();

  while(1) {
    sleep(10);
  }
}

