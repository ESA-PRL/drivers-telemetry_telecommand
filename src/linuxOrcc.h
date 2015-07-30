// *******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Inc/ExecSolaris/linuxOrcc.h
// Author   	  : Roger Pissard-Gibollet and Konstantin Kapellos 
// Version  	  : 3.0 alpha
// Creation 	  : 6 November 1996
//
// ***************************** Description ***********************************
//
//  		 Header for Orccad Exec Runtime
//  		  abstract type, define
//
// **************************** Modifications **********************************
// 
// Author   	  : Soraya Arias
// Date 		  : 12 April 2000
//
// This file provides an interface between all Orccad system call and 
// Red Hatv6-1 Linux2.0
// 
// BEWARE: timer resolution grain is 10ms in this version !
//  	   
// *****************************************************************************
// (c) Copyright 1996, INRIA, all rights reserved
// *****************************************************************************
#ifndef ORC_LINUXORCC_H
#define ORC_LINUXORCC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <iostream>
#include <signal.h>
#include <netdb.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <math.h>


//
// Define
//

typedef void (*FUNCPTR)  (...);
typedef void*(*SOSO)  (void*); //special type for cast in pthread_create()

#define OK 0
#define ERROR -1
#define STATUS int

#define FALSE 0
#define TRUE 1

// Linux Timer Resolution = 10 ms
#define TIME_UNIT 1000000
#define TIME_RES  10000

// Max numbers of characters for file name
#define MAXFILENAME 1024
//_POSIX_PATH_MAX +1 //_POSIX_PATH_MAX in posix1_lim.h
// -> limits.h ifdef __USE_POSIX
/* Structure of the headers */

/*-------Sockets----------*/
typedef struct
{
	unsigned char highMSB;
	unsigned char highLSB;
	unsigned char lowMSB;
	unsigned char lowLSB;
} SOCK_INTEGER;

/*-------Message Queues----------*/
typedef struct msgQId
{
	int msgId;
	key_t key;
	//  char msgName[256];
} orcmsgQ_t;

typedef struct msgBuf
{
	long mtype; 	/* message type, must be > 0 */
	int orcmsgInfo; /* message data */
} orcmsgQBuf_t;

// Message Queue Type
#define ORCMSGQ orcmsgQ_t *
// Size of the Message Queue
#define SIZE_QUEUE  10
// MAX, MIN Size of message in Queue
#define SIZE_MES_MAX 4056
#define SIZE_MES_MIN 128
// Message Queue Permission
#define MQPERM IPC_CREAT | IPC_EXCL | 0666
// Message Queue Priorities
#define MQPRIO_MAX (255)
// Message Queue Priority */
#define ORCNORMALPRI 1 
#define ORCURGENTPRI MQPRIO_MAX

/*-------Semaphores----------*/
// Semaphore Type
#define ORCSEM_ID sem_t *
// Init States of a Semaphore
#define ORCFULL  1
#define ORCEMPTY 0
#define ORCFOREVER -1

#define WAIT_FOREVER 0
/*-------Tasks----------*/
#define ORCTHR_ID pthread_t *
#define STACKSIZE size_t

/*-------Sockets----------*/
#define ORCSOCK_ID int

#define SCHEDPOLICY SCHED_OTHER  // SCHED_OTHER in schedbits.h -> sched.h
// Tasks Parameters
#define PRI_CLK   sched_get_priority_max(SCHEDPOLICY) // sched_get_priority_max in sched ->extern ?
#define PRI_CNL   PRI_CLK - 1 
#define PRI_RT    PRI_CLK - 2
#define PRI_MT    PRI_RT
#define PRI_PRR   PRI_RT
//---------
#define SMALL_STACK  5000//PTHREAD_STACK_MIN // NOT DEFINED !!!
#define NORMAL_STACK 5*SMALL_STACK
#define BIG_STACK    15*SMALL_STACK
#define MAX_TLM_TABLE_SIZE 12000

/*-------Timers----------*/
typedef struct timer
{
	struct timeval interval;
	double period;
} orcTimer_t;

#define ORCTIMER_ID orcTimer_t *
#define ORCSIGTIMER SIGALRM
#define TIMERHANDLER FUNCPTR

typedef struct two_args
{
	TIMERHANDLER arg1; 
	void* arg2;
}  TIMERSTRUCT;
    

namespace ORC_TYPE
{
  /// Template that encapsulates an array.
  /// This template allows using arrays as return types of 
  /// operation and property.
  template <class ArrayItemType, int size>
    struct Array
    {
      ArrayItemType internalArray[size];

      // Constructor
      Array()
      {
	memset(internalArray, 0, sizeof(internalArray));
      }
      
      // index-get operator
      inline const ArrayItemType& operator [] (long index) const 
      {
	return internalArray[index];
      }
      
      // index-set operator
      inline ArrayItemType& operator [] (long index)
      {
	return internalArray[index];
      }
      
      // address operator, especially for strings to get a char pointer.
      inline ArrayItemType* operator & (void)
      { 
	return internalArray;
      }
    };
}


//xtern "C" double rint(double);

static sigset_t allsig;
static struct sigaction new_sa; // mandatory unless segmentation fault!

extern TIMERSTRUCT orcTimerStruct;
extern ORCTIMER_ID orcTimer;

/*-------Message Queues----------*/
// Function to create message queues
inline ORCMSGQ orcMsgQCreate ()
{

	ORCMSGQ orcMsgQ;
	key_t key = IPC_PRIVATE;
	int err;


	err = msgget( key, MQPERM ); 
	if ( ( err == ERROR ) && ( errno == EEXIST ) )
	{
		printf( "orcMsgQCreate: msgQ already exists \n" );
		err = msgget( key, 0 );
		msgctl( err, IPC_RMID, 0 );
		err = msgget( key, IPC_CREAT | IPC_EXCL | MQPERM );
	}
	else if ( ( err == ERROR ) && ( errno != EEXIST ) )
	{
		printf( "orcMsgQCreate: Error = %d \n", errno );
		return NULL;
	}

	orcMsgQ = ( ORCMSGQ ) malloc( sizeof( orcmsgQ_t ) );
	orcMsgQ->msgId = err;
	orcMsgQ->key = key;

	return orcMsgQ;

}

// Function to get the number of messages in queue
inline long orcMsgQNumMsgs (ORCMSGQ queue)
{

	struct msqid_ds tmpBuf;

	if ( msgctl( queue->msgId, IPC_STAT, &tmpBuf ) == ERROR )
	{
		printf( "orcMsgQNumMsgs: Error = %d \n", errno );
		return ERROR;
	}
#ifdef DEBUG
	printf( "orcMsgQNumMsgs:: nb of msgs = %d \n", tmpBuf.msg_qnum );
#endif
	return ( long ) tmpBuf.msg_qnum;

}

// Function to send messages on a message queue
inline int orcMsgQSend (ORCMSGQ queue, int msg, int prio)
{

	orcmsgQBuf_t tmpBuf;
	int msgSize;

	msgSize = sizeof( orcmsgQBuf_t ) - sizeof( long );
#ifdef DEBUG
	printf( "orcMsgQSend: msgId = %d \n", queue->msgId );
	printf( "orcMsgQSend: msgSize = %d \n", msgSize );
#endif
	tmpBuf.orcmsgInfo = msg;
	tmpBuf.mtype = MQPRIO_MAX - prio;

	/* 0 : If message queue is full -> message is not written to the queue */
	if ( msgsnd( queue->msgId, &tmpBuf, msgSize, 0 ) == ERROR )
	{
		printf( "orcMsgQSend: Error = %d \n", errno ); 
		return ERROR;
	}
	return OK;

}

// Function to receive messages on a message queue
inline int orcMsgQReceive (ORCMSGQ queue, int* msg)
{

	orcmsgQBuf_t tmpBuf;
	int msgSize;

	msgSize = sizeof( orcmsgQBuf_t ) - sizeof( long );

	/* 0 : the calling process blocks until a message arrives in queue */
	/* mtype = -MQPRIO_MAX: type of message to retrieve from the queue 
			   if mtype < 0 : first message on
				the queue with the lowest type less than  or  equal
				to the absolute value of msgtyp will be read
	*/
	if ( msgrcv( queue->msgId, &tmpBuf, msgSize, -MQPRIO_MAX, 0 ) == ERROR )
	{
		printf( "orcMsgQReceive: Error = %d \n", errno ); 
		return ERROR;
	} 
#ifdef DEBUG
	printf( "orcMsgQReceive: msg received = %d \n", tmpBuf.orcmsgInfo );
#endif
	*msg = tmpBuf.orcmsgInfo; 

	return OK;

}

// Function to close a message queue
inline int orcMsgQClose (ORCMSGQ queue)
{

	if ( msgctl( queue->msgId, IPC_RMID, 0 ) == ERROR )
	{
		printf( "orcMsgQClose: Error = %d \n", errno );
		return ERROR;
	}
	free( queue );

	return OK;

}

/*-------Semaphores----------*/
// Function to create semaphores
inline ORCSEM_ID orcSemCreate (int initState)
{

	ORCSEM_ID newSem;

	newSem = new sem_t;

	int status;

	if ( initState == ORCEMPTY )
		status = sem_init( newSem, 0, 0 );
	else
		status = sem_init( newSem, 0, 1 );

	if ( status == OK )
		return newSem;
	else
		return NULL;

}

// Function to delete semaphores
inline int orcSemDelete (ORCSEM_ID sem)
{

	int res = ERROR;

	if ( sem != NULL )
	{
		res = sem_destroy( sem );
		delete sem;
		sem = NULL;
	}

	return res;

}

// Function to give a semaphore
inline int orcSemGive (ORCSEM_ID sem)
{

	return ( sem_post( sem ) );

}

// Function to take a semaphore
// TODO : no timeout in Posix semaphores
inline int orcSemTake (ORCSEM_ID sem, int timeout)
{

  int dummy = timeout; dummy++;// to avoid compilation warnings
  
  return ( sem_wait( sem ) );

}
inline int orcSemTryTake (ORCSEM_ID sem, int timeout)
{

  int dummy = timeout; dummy++;// to avoid compilation warnings
  
  return ( sem_trywait( sem ) );

}

/*-------Tasks----------*/
// Function for suspending current process
// TODO : no taskDelay in Posix (sleep uses seconds, delay ?, nanosleep ?)
inline int orcTaskDelay (int delay)
{

  int dummy = delay; dummy++;// to avoid compilation warnings
	return OK;

}


// Function to check if a task is still valid or not
inline int orcTaskIdVerify (ORCTHR_ID Id)
{

	if ( Id != NULL )
	{
		if ( pthread_kill( *Id, 0 ) != OK )
			return ERROR;
		else
			return OK;
	}
	return ERROR;

}

// Function to kill a task (thread)
inline int orcTaskDelete (ORCTHR_ID Id)
{

	// Check if thread is ok
	if ( Id != NULL )
	{
		if ( pthread_kill( *Id, 0 ) == OK )
		{
			// Send SIGTERM signal <- BAD!!
			// return (pthread_kill(*Id,SIGTERM)) ;
			return( pthread_cancel( *Id ) );
		}
	}
	return ERROR;

}

// Function to spawn
inline int orcSpawn (ORCTHR_ID* tid, const char* name, int prio, STACKSIZE stackSize, FUNCPTR funcptr, void* arg)
{

	int status;


	*tid = new pthread_t;

	pthread_attr_t attributes;
	sched_param schedattributes;

	// To avoid compilation warnings
	char* dummy = ( char* ) malloc( ( strlen( name ) * sizeof( char ) ) + 1 ); 
	strcpy( dummy, name );

	// Allocation and initialization of the attribute structure
	pthread_attr_init( &attributes );
	// Set stack size : BEWARE in SOlaris is better to set stacksize to default value
	// i.e. NULL instead of a user defined stacksize value -> see man pthread_create
	printf( "StackSize = %d \n", stackSize );
	// pthread_attr_setstacksize(&attributes, stackSize);
	// Set thread priority
	schedattributes.sched_priority = prio;
	pthread_attr_setschedparam( &attributes, &schedattributes );

	// Thread creation
	status = pthread_create( *tid, &attributes, ( SOSO ) funcptr, arg );
#ifdef DEBUG
	printf( "pthread_Create %s error = %d \n", name, status );
#endif
	
	pthread_detach(**tid);
	
	return status;

}

//function to lock the task
inline int orcTaskLock ()
{

	return OK;

}

//function to unlock the task
inline int orcTaskUnlock ()
{

	return OK;

}


/*-------Timers----------*/
void orcTimer_handler (int);

// Function to mask timer signal interruption
inline int orcTimerSigMask ()
{

	sigset_t allsig;

	sigemptyset( &allsig );
	sigaddset( &allsig, ORCSIGTIMER );
	if ( pthread_sigmask( SIG_UNBLOCK, &allsig, NULL ) != OK )
	{
		printf( "pthread_sigmask Failed %d \n", errno );
		return ERROR;
	}

	return OK;

}

// Function to set the timer period
inline int orcTimerSetTime (double period)
{

	struct itimerval new_setting, old_setting;
	struct timeval time_delay ;
	double sec, usec;

	//Convert the period in microsecond
	double delay = ( double ) TIME_UNIT* period ;
	// Set the timespec struct -> delay in second, delay in microsecond
	// get the part in second
	sec = floor( delay / ( double ) TIME_UNIT );
	// get the remainder part in microsecond
	usec = rint( fmod( delay, ( double ) TIME_UNIT ) );

	time_delay.tv_sec = ( int ) ( sec );
	// Handle period < TIME_RES 
	if ( delay < ( double ) TIME_RES )
		time_delay.tv_usec = TIME_RES ;
	else
		time_delay.tv_usec = ( int ) ( floor( usec / ( double ) TIME_RES ) ) * TIME_RES;

	// Setting the delay for the alarm
	new_setting.it_value.tv_sec = time_delay.tv_sec ;
	new_setting.it_value.tv_usec = time_delay.tv_usec ;
	new_setting.it_interval.tv_sec = time_delay.tv_sec ;
	new_setting.it_interval.tv_usec = time_delay.tv_usec ;

	orcTimer->interval = new_setting.it_value;

#ifdef DEBUG
	printf( "orcTimerSetTime:: new_setting.it_value.tv_sec = %d, new_setting.it_value.tv_usec = %d \n",
			new_setting.it_value.tv_sec,
			new_setting.it_value.tv_usec );
#endif
	// Arm the timer using the new_setting delay 
	// in Linux: timer resolution = 10ms !
	// ITIMER_REAL decrements  in  real  time,  and   delivers
	//  		   SIGALRM upon expiration  
	if ( setitimer( ITIMER_REAL, &new_setting, &old_setting ) == ERROR )
	{
		printf( "Error setitimer = %d \n", errno );
		return ERROR;
	}
	return OK;

}

// Function to create a Timer
inline int orcTimerInit (double period)
{

	struct sigaction old_sa;

	//	orcTimer = ( ORCTIMER_ID ) malloc( sizeof( orcTimer_t ) );	// emc debug
	orcTimer = new orcTimer_t;

	orcTimer->period = period;

	// Set the handler upon delivery of ORCSIGTIMER
	// struct sigaction {void (*sa_handler)(int); ...}
	new_sa.sa_handler = orcTimer_handler;

	if ( orcTimerSigMask() == ERROR )
		return ERROR;

	sigaction( ORCSIGTIMER, &new_sa, &old_sa );

	return ( orcTimerSetTime( period ) );

}
// Function to delete the timer
inline int orcTimerDelete ()
{

	int err1 = OK;
	int err2 = OK;
	sigset_t allsig;

	// Cancel the timer
	err1 = setitimer( ITIMER_REAL, NULL, NULL );
	// Set a new IT mask
	sigemptyset( &allsig );
	pthread_sigmask( SIG_SETMASK, &allsig, NULL );


	if ( orcTimer != NULL )
	{
		delete orcTimer;
		orcTimer = NULL;
	}
	//	free( orcTimer );    // emc debug

	return ( ( err1 ) ? err1 : err2 );

}

inline int orcTimerArm (TIMERHANDLER func, void* arg)
{

	orcTimerStruct.arg1 = func;
	orcTimerStruct.arg2 = ( int * ) arg;

	return OK;

}

inline int orcTimerLaunch ()
{

	int err;

	// Unblock the ORCSIGTIMER signal  
	if ( sigismember( &allsig, ORCSIGTIMER ) )
	{
		// Unblock the ORSIGTIMER ie allow timer interruption
		if ( ( err = pthread_sigmask( SIG_SETMASK, &allsig, NULL ) ) != OK )
		{
			printf( "orcTimerHandler error pthread_sigmask : %d \n", err );
			return ERROR;
		}
	}
	return OK;

}



/* -------- MISC -------- */
// Function for getting the current path
// TODO : MAXFILENAME is set to 80 in util.h, it should be PATH_MAX+1
inline int orcGetPath (char* path)
{

	if ( getcwd( path, MAXFILENAME ) != OK )
		return ERROR;
	return OK;

}

// Function to set the current directory
inline int orcSetPath (const char* path)
{

	return chdir( path );

}

/*- Spy for Events  	   -*/
inline int orcSpyEvent (int eventid, char* buffer, int bufsize)
{

	return OK;

}

#endif
