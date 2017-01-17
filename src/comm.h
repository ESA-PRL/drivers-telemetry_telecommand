//*******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Inc/Exec/comm.h
// Author   	  : Soraya Arias
// Version  	  : 1.0 beta
// Creation 	  : 24 Mar 1999 
//
//***************************** Description ***********************************
//
//  		 Header for Orccad Exec Runtine of
//  		 communication between Orccad Application
//  		 and the environment
//
// Class Definition: 
//   Communication:
//
//**************************** Modifications **********************************
//
//*****************************************************************************
// (c) Copyright 1996, INRIA, all rights reserved
//*****************************************************************************

#ifndef ORC_COMM_H
#define ORC_COMM_H

#include <SDL/SDL_net.h>
#include <string>
#include <vector>
#include <list>

#include "ActiveMQTMSender.h"
#include "simplethread.h"
#include "prr.h"

#define COMM_ERROR0 1
#define COMM_ERROR1 2
#define COMM_ERROR2 3
#define COMM_ERROR3 4
#define COMM_ERROR4 5
#define COMM_ERROR5 6
#define COMM_ERROR6 5
#define COMM_ERROR7 6
#define COMM_ERROR8 6
#define MAX_SIZE_MESSAGE 80

#define MAX_PLAN_TC_NBR 20

#define SESSION_NOSTATUS  0
#define SESSION_INIT	  1
#define SESSION_CONNECTED 2

#define SESSION_STOP	  0
#define SESSION_RUN 	  1

#define CMD_NO   0
#define CMD_YES  1

using std::vector;
using std::string;


class CommServer :public SimpleThread
{
 protected:
  int Port;
  TCPsocket Server;
  TCPsocket Client;
  int Running;
  int Connected;
  int theStatus;
 public:
  CommServer(int port);
   ~CommServer();
   int GetStatus();
   void StopRunning();
   void Close();
   virtual void* thread (){ return NULL;};
}; 

class CommTmServer : public CommServer
{
 private:
 RobotProcedure* prr;
 ActiveMQTMSender *activemqTMSender;
 public:
  CommTmServer(int port, RobotProcedure* prr, ActiveMQTMSender *tmsender);
  ~CommTmServer(){};
  void orcGetTmMsg(std::string &tmmsg);
  int sendImageMessage(int seq, long time, int size, const unsigned char * data, MessageProducer* messproducer);
  void* thread ();
}; 

class CommTcReplyServer : public CommServer
{
 private:
 public:
  CommTcReplyServer(int port);
  ~CommTcReplyServer(){};
  int sendData (char *buffer);
  void* thread ();
}; 
class CommandInfo {
 public:
  std::string activityName;
  std::string activityParams;
 public:
  CommandInfo(std::string activity_name, std::string activity_param);
  
};
class CommTcServer : public CommServer
{
 private:
  std::list <CommandInfo*> cmdList;
 public:
  CommTcServer(int port);
  ~CommTcServer(){};
  void addCommandInfo(CommandInfo *);
  CommandInfo* extractCommandInfo();
  int strTokenize (const string& str, vector<string>& tokens, const string& delimiters = " ");
  void* thread ();
}; 


class CommClient : public SimpleThread
{
 private:
  int Port;
  TCPsocket Server;
  TCPsocket Client;
  int Running;
  int Connected;
  int theStatus;
 public:
  CommClient(int port);
  ~CommClient();
  void* thread ();
  int sendData (char *buffer);
  int readData (char *msg);
   int GetStatus();
   void StopRunning();
   void Close();
}; 




#endif

