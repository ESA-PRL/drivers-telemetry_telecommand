

#include "rt.h"
#include "param.h"
#include "prr.h"

extern RobotProcedure*  theRobotProcedure;

RobotTask::RobotTask (std::string name)
{
  std::cout << "** RobotTask constructor:" << name << std::endl;
  tcRequestId = -1;

  if (( waitEndActionSem = orcSemCreate( ORCEMPTY ) ) == NULL ) {
    //EventStorage->displayError( RT_ERROR3, Clock->GetTime() );
  }

  // set the name
  rtName = name;
}

RobotTask::~RobotTask ()
{
}

int RobotTask::SetTcRequestId (int tc_req_id) {
  tcRequestId = tc_req_id;
}

int RobotTask::GetTcRequestId () {
  return tcRequestId;
}


int RobotTask::Control ()
{
  if ( createThread() == ERROR ) {
    return 0;
  }
  
  return 1;
}


void RobotTask::waitEndActionExec () {
  if ( orcSemTake( waitEndActionSem, ORCFOREVER ) == ERROR ) {
    
  }
}

std::string RobotTask::GetName ()
{
  return rtName;
}
int RobotTask::GetId ()
{
  return rtId;
}

int RobotTask::SetParam (char* params)
{
  strcpy(rtParams, params);
}


void* RobotTask::thread ()
{
  std::cerr << "++ Thread RobotTask::thread spawned" << std::endl;
  FILE *logFile;
  char filename[240];
  sprintf(filename, "%s.log", rtName.c_str());
  if ((logFile = fopen( filename, "w+")) == NULL) {
    printf ("ERROR: Log init failed!!!!! can't open file %s\n", 
	    filename);
    return NULL;
  }
  
  int index = 0;
  int run = TRUE;
  do
    {
      if (rtName == "ADE_LEFT_Initialise") { 
	computeADE_LEFT_Initialise();
      }
      else if (rtName == "ADE_LEFT_conf") { 
	computeADE_LEFT_conf();
      }
      else if (rtName == "ADE_LEFT_ReleaseHDRM") { 
	computeADE_LEFT_ReleaseHDRM();
      }
      else if (rtName == "ADE_LEFT_SwitchOff") { 
	computeADE_LEFT_SwitchOff();
      }
      else if (rtName == "ADE_RIGHT_Initialise") { 
	computeADE_RIGHT_Initialise();
      }
      else if (rtName == "ADE_RIGHT_conf") {
	computeADE_RIGHT_conf();
      }
      else if (rtName == "ADE_RIGHT_ReleaseHDRM") { 
	computeADE_RIGHT_ReleaseHDRM();
      }
      else if (rtName == "ADE_RIGHT_SwitchOff") { 
	computeADE_RIGHT_SwitchOff();
      }
      else if (rtName == "SA_LEFT_Initialise") { 
	computeSA_LEFT_Initialise();
      }
      else if (rtName == "SA_LEFT_PrimaryMoveTo") { 
	computeSA_LEFT_PrimaryMoveTo();
      }
      else if (rtName == "SA_LEFT_SecondaryMoveTo") { 
	computeSA_LEFT_SecondaryMoveTo();
      }
      else if (rtName == "SA_LEFT_SwitchOff") { 
	computeSA_LEFT_SwitchOff();
      }
      else if (rtName == "SA_RIGHT_Initialise") { 
	computeSA_RIGHT_Initialise();
      }
      else if (rtName == "SA_RIGHT_PrimaryMoveTo") { 
	computeSA_RIGHT_PrimaryMoveTo();
      }
      else if (rtName == "SA_RIGHT_SecondaryMoveTo") { 
	computeSA_RIGHT_SecondaryMoveTo();
      }
      else if (rtName == "SA_RIGHT_SwitchOff") { 
	computeSA_RIGHT_SwitchOff();
      }
      
      else if (rtName == "PanCam_Initialise") { 
	computePanCam_Initialise();
      }
      else if (rtName == "PanCam_InitWACs") { 
	computePanCam_InitWACs();
      }
      else if (rtName == "PanCam_SwitchOn") { 
	computePanCam_SwitchOn();
      }
      else if (rtName == "PanCam_WACAcqImage") { 
	computePanCam_WACAcqImage();
      }
      else if (rtName == "PanCam_WACGetImage") { 
	computePanCam_WACGetImage();
      }
      else if (rtName == "PanCam_SwitchOff") { 
	computePanCam_SwitchOff();
      }
      else if (rtName == "PanCam_PIUSwitchOff") { 
	computePanCam_PIUSwitchOff();
      }
      else if (rtName == "PANCAM_WAC_RRGB") { 
	computePANCAM_WAC_RRGB();
      }
      else if (rtName == "PanCam_FilterSel") { 
	computePanCam_FilterSel();
      }
      
      else if (rtName == "MAST_DEP_Initialise") { 
	computeMAST_DEP_Initialise();
      }
      else if (rtName == "MAST_DEP_Deploy") { 
	computeMAST_DEP_Deploy();
      }
      else if (rtName == "MAST_PTU_Initialise") { 
	computeMAST_PTU_Initialise();
      }
      else if (rtName == "MAST_PTU_MoveTo") { 
	computeMAST_PTU_MoveTo();
      }
      else if (rtName == "MAST_SwitchOff") { 
	computeMAST_SwitchOff();
      }
      
      else if (rtName == "GNC_Initialise") { 
	computeGNC_Initialise();
      }
      else if (rtName == "GNC_LLO") { 
	computeGNC_LLO();
      }
      else if (rtName == "GNC_SwitchOff") { 
	computeGNC_SwitchOff();
      }
      
      else if (rtName == "RV_WakeUp") { 
	computeRV_WakeUp();
      }
      else if (rtName == "MMS_WaitAbsTime") { 
	computeMMS_WaitAbsTime();
      }
      else if (rtName == "RV_Prepare4Comms") { 
	computeRV_Prepare4Comms();
      }
      else if (rtName == "RV_PostComms") { 
	computeRV_PostComms();
      }
      else if (rtName == "DHS_Go2Nominal") { 
	computeDHS_Go2Nominal();
      }
      else if (rtName == "RV_Prepare4Travel") { 
	computeRV_Prepare4Travel();
      }
      else if (rtName == "RV_Prepare4Night") { 
	computeRV_Prepare4Night();
      }
      else if (rtName == "RV_Prepare4Dozing") { 
	computeRV_Prepare4Dozing();
      }
      
      sleep(1);
      index++;
      fprintf(logFile, "%d %s\n", index, rtName.c_str());
      if (index == 3) 
	run = FALSE;
    }
  while ( run );
  
  fclose(logFile);
  
  // at the end of the Control method
  if ( orcSemGive(waitEndActionSem) == ERROR ) { 
    return NULL;
  }
  
  std::cout << "-- Thread RobotTask::thread terminated" << std::endl;
}

void RobotTask::computeADE_LEFT_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_LEFT_conf(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_LEFT_ReleaseHDRM(){ 
  std::cerr << rtName << std::endl;
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  } 
}
void RobotTask::computeADE_LEFT_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_RIGHT_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_RIGHT_conf(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_RIGHT_ReleaseHDRM(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeADE_RIGHT_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "ADEState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computeSA_LEFT_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_LEFT_PrimaryMoveTo(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_LEFT_SecondaryMoveTo(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_LEFT_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_RIGHT_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_RIGHT_PrimaryMoveTo(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeSA_RIGHT_SecondaryMoveTo(){ 
  std::cerr << rtName << std::endl; 
}
void RobotTask::computeSA_RIGHT_SwitchOff(){ 
std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "SAState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computePanCam_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_InitWACs(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_SwitchOn(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_WACAcqImage(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_WACGetImage(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_PIUSwitchOff(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePANCAM_WAC_RRGB(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computePanCam_FilterSel(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computeMAST_DEP_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeMAST_DEP_Deploy(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeMAST_PTU_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeMAST_PTU_MoveTo(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeMAST_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computeBEMA_Deploy_1(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeBEMA_Deploy_2(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeGNC_Initialise(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeGNC_LLO(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeGNC_SwitchOff(){ 
  std::cerr << rtName << std::endl; 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

void RobotTask::computeRV_WakeUp(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeMMS_WaitAbsTime(){ 
  std::cerr << rtName << std::endl; 
}
void RobotTask::computeRV_Prepare4Comms(){ 
  std::cerr << rtName << std::endl; 
}
void RobotTask::computeRV_PostComms(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeDHS_Go2Nominal(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeRV_Prepare4Travel(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeRV_Prepare4Night(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}
void RobotTask::computeRV_Prepare4Dozing(){ 
  std::cerr << rtName << std::endl; 
  if ( theRobotProcedure->GetParameters()->get( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
  if ( theRobotProcedure->GetParameters()->set( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
    std::cout << rtName << " failed" << std::endl;
  }
}

