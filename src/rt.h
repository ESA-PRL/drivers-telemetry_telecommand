#ifndef ORC_RT_H
#define ORC_RT_H

/**
 * Include files
 */
#include "simplethread.h"
#include "linuxOrcc.h"


class RobotTask : public SimpleThread
{
  
 protected:

  /** The Id of the Robot Task */
  int rtId;

  /** The name of the Robot Task */
  std::string rtName;

 protected:	

  /** The semaphore used to block the execution until the end */
  ORCSEM_ID waitEndActionSem;
  
  /** The id of the thread that controls the Modules Tasks of the Robot Task */
  ORCTHR_ID ctrlId;   	
  
  int tcRequestId;
  
  char rtParams[1024];

 public:
  
  RobotTask (std::string name);
  virtual ~RobotTask ();
  
  /** Launch the threads that correspond to the Module Tasks */
  int Control ();  
  
  /** Blocks until the waitEndActionSem is deblocked */
  void waitEndActionExec ();

  /** Get the name of the Robot Task */
  std::string GetName ();

  /** Get the Id of the Robot Task */
  int GetId();

  int SetTcRequestId (int ); 

  int GetTcRequestId ();
 
  int SetParam (char*);
  
  // method used only for the continuous execution; in this
  // case it does not do anything
 private:
  virtual void* thread ();

};

#endif

