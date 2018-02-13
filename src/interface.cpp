#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "prr.h"
#include "rt.h"

typedef void (*FUNCPTR)  (...);

extern "C" {
  FUNCPTR aa_I_START();
  FUNCPTR aa_I_ADE_LEFT_Initialise_start();
  FUNCPTR aa_I_ADE_LEFT_Initialise_GoodEnd();
  FUNCPTR aa_I_GNC_SwitchOff_start();
  FUNCPTR aa_I_GNC_SwitchOff_GoodEnd();
};
extern "C" {
  int aa();
  int aa_reset();
}


extern RobotProcedure*  theRobotProcedure;

enum INPUT_SIGNALS_USER {
  ADE_LEFT_Initialise_start, 
  ADE_LEFT_Initialise_GoodEnd, 
  GNC_SwitchOff_start, 
  GNC_SwitchOff_GoodEnd,
  NB_SIGNALS
};

char TABEVENT[ NB_SIGNALS ][ MAXCHARNAME ] = {
  "ADE_LEFT_Initialise_start;",
  "ADE_LEFT_Initialise_GoodEnd;",
  "GNC_SwitchOff_start;",
  "GNC_SwitchOff_GoodEnd;"
};


FUNCPTR TABSIG[ NB_SIGNALS ] = {
  ( FUNCPTR ) aa_I_ADE_LEFT_Initialise_start,
  ( FUNCPTR ) aa_I_ADE_LEFT_Initialise_GoodEnd,
  ( FUNCPTR ) aa_I_GNC_SwitchOff_start,
  ( FUNCPTR ) aa_I_GNC_SwitchOff_GoodEnd
};

int getEventFromName(char const *eventname) {
  // compare all the event names with the given name
  for (int i = 0; i<NB_SIGNALS; i++) {
    //    fprintf(stderr, "In getEventFromName: eventname = %s\n", eventname);
    if (strcmp( TABEVENT[i], eventname ) == 0) {
      return i;
    }
  }
  fprintf(stderr, "Return eventId = -1\n");
  return -1;
}
/**
 * Send the event of the given name to the application
 * automaton
 */
int moduleSendEvent(const char *event_name) {
  int event_id = getEventFromName(event_name);
  if (event_id != -1) {
    aa();
    TABSIG[event_id]();
    aa();
    return OK;
  }
  return ERROR;

}
extern "C" {
  int orcExecActFromAP(const char* rtinstanceid, const char* rtmnemonic,  char *rtparams) {
    std::cout << "orcExecActFromAP: " << rtmnemonic  << std::endl;

    RobotTask* RT;
    RT = ( RobotTask* ) theRobotProcedure->GetRTFromName((char*)rtmnemonic);
    if (RT != NULL) {
      RT->Control();
      RT->waitEndActionExec ();
    }
  }
  int orcStopActFromAP(const char* rtname) {
    std::cout << "orcStopActFromAP: " <<  rtname << std::endl;
  }
  
  int orcWaitActivityEnd(const char* rtname) {
    
  }
  int orcStartActFromAP(const char* rtinstanceid, const char* rtmnemonic,  char *rtparams) {
    std::cout << "orcStartActFromAP: " << rtmnemonic  << std::endl;
    
  }
  int orcStopActivity(){}
  void Deactivate(char *rtname) {
    std::cout << "Deactivate: " << rtname  << std::endl;
    RobotTask* RT = ( RobotTask* ) theRobotProcedure->GetRTFromName(rtname);
    if (RT != NULL) {
    }
  }
  void ActivateActionFromTask(char *rtname, char *rtparams) {
    std::cout << "ActivateActionFromTask: " << rtname  << std::endl;
    RobotTask* RT;
    RT = ( RobotTask* ) theRobotProcedure->GetRTFromName((char*)rtname);
    if (RT != NULL) {
      RT->Control();
    }
  }
}
