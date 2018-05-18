//*******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Inc/Exec/global.h
// Author   	  : Roger Pissard-Gibollet and Konstantin Kapellos 
// Version  	  : 3.0 beta
// Creation 	  : 6 November 1996 
//
//***************************** Description ***********************************
//
//  		 Header for Orccad Exec storage
//  		 of globals object (time, debug, datas...)
//
// Class Definition: 
//   Global: Storage of globals object (time, debug, datas...)
//
//**************************** Modifications **********************************
//
// 6 November 1996 integration on Orccad Exec
//
//*****************************************************************************
// (c) Copyright 1996, INRIA, all rights reserved
//*****************************************************************************
#ifndef ORC_TASKLIB_H
#define ORC_TASKLIB_H

#include <string>
#include <dlfcn.h>
#include <vector>
#include <list>

#include "utils.h"
#include "simplethread.h"

using std::vector;
using std::string;
using std::list;

class TaskLib : public SimpleThread 
{
 protected:
  
  std::string Name;

  std::list<std::string> solFiles;
  
  void *libHandler;


  int State;

  int Status;


 public:
  
  TaskLib (std::string name);
  ~TaskLib ();
  std::string GetName();
  int loadTaskLib();
  FUNCPTR getFunction(const char *funcname);
  int closeTaskLib();
  int callFunction(const char* funcname);
  int getState();

  int insertSol (std::string sol);

  int ExecuteActivityPlan();

  /** The thread that manages the AP execution */
  virtual void* thread ();

};

#endif
