//*******************************  VIMANCO *************************************
//
// File 	  : $VIMANCO_SRC/kernel/inc/prr.h
// Author   	  : Konstantinos Kapellos 
// Version  	  : 1.0 
// Creation 	  : September 5 2006
//
//***************************** Description ***********************************
//
// Implements the Execution Machine of the application automaton. It satisfies 
// the following requirements (see VIMANCO_SRD_TRA):
//
//**************************** Modifications **********************************
//
// This file is part of the INRIA ORCCAD controller developped by 
// Roger Pissard-Gibollet and Konstantinos Kapellos May 1994. 
// See [RD1] VIMANCO_SRD_TRA 
//
//
//*****************************************************************************
// (c) Copyright 2006, TRASYS Space, all rights reserved
//*****************************************************************************

#ifndef ORC_PRR_H
#define ORC_PRR_H

#include <string>
#include <list>

#include "utils.h"
#include "param.h"
#include "rt.h"

  class MyClock {
	  public:
	  double period;
	  MyClock() { period =1.0;}
	  double GetBasePeriod() {return period;}
  };
  
class RobotProcedure
{
 public:
  MyClock *Clock;
  
 protected:
  std::string Name;
  
  int Status;
  
  Parameters* GlobState;  		// Table of symbol for manage data state
  
  std::list<RobotTask*> RobotTasks;

  double State[MAX_STATE_SIZE];
  double ADEState[MAX_STATE_SIZE];
  double SAState[MAX_STATE_SIZE];
  double MastState[MAX_STATE_SIZE];
  double PanCamState[MAX_STATE_SIZE];
  double GNCState[MAX_STATE_SIZE];


  char OrccadPath[ MAXFILENAME ];		// Orccad user Path

public:

  RobotProcedure (std::string name);
  virtual ~RobotProcedure ();

  virtual bool Init () { return false;}
  virtual void Launch () {return;}
  
  void Terminate();
  
  void SetUp (std::string name);
  
  char* GetName ();
  
  // insert a RT in PrR
  int insertRT (RobotTask* rt);
  
  int GetRTNumber ();

  std::list<RobotTask*> GetRobotTasks(); 

  RobotTask* GetRTFromName (char*);
  RobotTask* GetRTFromMnemonic (char*);
  RobotTask* GetRTFromInstanceId (char*);
  Parameters* GetParameters ();
   
  void AddTaskInPlan(char *msg); 
  void GetNextTaskOfPlan();
  void PlanAbort();

  int GetStatus ();
  void SetStatus (int);

  void SetStateSize(int);
  int GetStateSize();


  char* GetPath ();
  void SetPath (char*);
};



#endif

