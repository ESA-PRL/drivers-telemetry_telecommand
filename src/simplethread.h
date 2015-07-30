#ifndef ORC_SIMPLETHREAD_H
#define ORC_SIMPLETHREAD_H

#include <iostream>
#include <pthread.h>


class SimpleThread
{
public:

  SimpleThread ();
  virtual ~SimpleThread ();
  
  int	 createThread();			// create and start thread execution
  void terminateThread();			// signal thread using the m_exit boolean to terminate itself
  void joinThread();				// blocks until thread is terminated
  
  
 protected:
  
  bool isThreadTerminated();		// used inside the thread for self termination
  
 private:
  
  pthread_t			m_thread_id;
  pthread_mutex_t		m_terminate_mutex;
  bool				m_bExit;
  bool				m_bRunning;
  
  virtual void* thread ();	// the thread (redefine with your own thread function in a child class)
  static void* threadCaller (void* data);
}; 

// Example
/*

class ChildClass : public SimpleThread
{
public:

ChildClass ();
virtual ~ChildClass ();

private:
virtual void* thread ();

}; 

// End class ChildClass
*/

#endif
