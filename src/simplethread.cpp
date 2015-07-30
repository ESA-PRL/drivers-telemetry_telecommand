#include "simplethread.h"


SimpleThread::SimpleThread ()
	: m_bExit(false), m_bRunning(false)
{

	m_thread_id = 0;
	pthread_mutex_init(&m_terminate_mutex, NULL);

}

SimpleThread::~SimpleThread ()
{

	terminateThread();		// make sure that the thread is terminated before exiting
	joinThread();

	pthread_mutex_destroy(&m_terminate_mutex);
} 


void* SimpleThread::threadCaller (void* data)
{

	SimpleThread* parent = (SimpleThread*) data;
	return parent->thread();
}

int SimpleThread::createThread ()
{
	int status;
    status = pthread_create( &m_thread_id, NULL, threadCaller, (void*) this);
	return status;
}

void SimpleThread::terminateThread()
{
	pthread_mutex_lock(&m_terminate_mutex);
	m_bExit = true;
	pthread_mutex_unlock(&m_terminate_mutex);
}

bool SimpleThread::isThreadTerminated()
{
	bool r;

	pthread_mutex_lock(&m_terminate_mutex);
	r = m_bExit;
	pthread_mutex_unlock(&m_terminate_mutex);

	return r;
}



void SimpleThread::joinThread()
{
  if (m_thread_id) 
    pthread_join( m_thread_id, NULL);
}


void* SimpleThread::thread ()
{
	
	std::cout << "######################### base thread started #######################" << std::endl;

}


// Example
/*

ChildClass::ChildClass ()
{
	std::cout << "** ChildClass constructor" << std::endl;

}

ChildClass::~ChildClass ()
{
	std::cout << "** ChildClass destructor" << std::endl;

	terminateThread();
	joinThread();
}


void* ChildClass::thread ()
{
	std::cout << "######################### child thread started #######################" << std::endl;	

	int i=0;
	while (isThreadTerminated()==false)
	{
		std::cout << this << "  " << i << std::endl;
		i++;
	}

}
*/
