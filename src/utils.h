//*******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Inc/Exec/utils.h
// Author   	  : Roger Pissard-Gibollet and Konstantin Kapellos 
// Version  	  : 3.0 alpha
// Creation 	  : 6 November 1996
//
//***************************** Description ***********************************
//
//  		 Header for Orccad Exec Runtime
//  		  abstract type, define
//
//**************************** Modifications **********************************
//
// SOSO#6 09-03-00 changement de DATA_INT en DATA_INTEGER
// SOSO#step 10-04-00 ajout d'une erreur pour le mode d'execution
// SOSO#Linux 05-00 Add the Linux .C file and a generic line to be customed
//  				when a new Execution Kernel Librairy is implemented and added
//
//*****************************************************************************
// (c) Copyright 1996, INRIA, all rights reserved
//*****************************************************************************
#ifndef ORC_UTILS_H
#define ORC_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <log4cxx/logger.h>

using namespace log4cxx;


#include "linuxOrcc.h"

//
// Define
//

// Input Signals for Canal
#define FAIL		-2
#define DESTROY 	-1
#define MAXLABEL	8
#define SIGNAL  	int

// it was 400
#define MAXINPUTSIG 800
// Timeout for semaphores waiting
#define  SHORT_WAIT  WAIT_FOREVER  
#define  MEDIUM_WAIT WAIT_FOREVER
#define  LONG_WAIT   WAIT_FOREVER 

// RT.Parametrized
#define NON_PARAMETRIZED 0
#define PARAMETRIZED	 1
// Max numbers of characters for a name
#define MAXCHARNAME  80
// Max Number of Parameters for a RT
#define MAXPARAM	50
// Types of Parameters for a RT
#define INTEGER 	0
#define DOUBLE  	1
#define FLOAT   	1
#define SCALAR  	1
#define VECTOR  	2
#define MATRIX  	3
// Define for Tables Events (it was 150)
#define MAXTABINEVENT 900
#define MAXTABSEM     10
#define MAXTABHIST    500
#define FILEHISTORY  "./EventHistory.esi"
#define CURRENTDIR   "./"
// Display Event Mode which can be combined
#define DBG_NONE	 0x0  
#define DBG_STDOUT   0x1  
#define DBG_WINDVIEW 0x2  
#define DBG_SOCKET   0x4
#define DBG_FILE	 0x8
// Display Data Mode which can be combined
#define DBG_DATA_NONE     0x0  
#define DBG_DATA_STDOUT   0x1  
#define DBG_DATA_SOCKET   0x2
#define DBG_DATA_FILE     0x4
//Max values for Data debug
#define MAX_ROW_ELEMENT   50
#define MAX_COL_ELEMENT   50           
#define MAX_TAB_SIZE	  5000
#define MAXVARNAME  	  80
#define MAX_SAVE_VAR	  100
// values for clocks
#define MAXHARMONIC 	  50
#define MINPERIOD   	  0.001 // 1 ms
// numbers max of parameters
#define MAX_RT_PARAM	  10

#define MAX_STATE_SIZE    100

// External communications port numbers

#ifdef ARC
#define TC_SERVER_PORT_NBR 7131
#define TM_SERVER_PORT_NBR 7132
#else
#ifdef GRM
#define TC_SERVER_PORT_NBR 7231
#define TM_SERVER_PORT_NBR 7232
#else
#define TC_SERVER_PORT_NBR 7031
#define TM_SERVER_PORT_NBR 7033
#endif
#endif
//
// Enum
//

//Index of Semaphore for Phr control
enum SemPhrIndex
{
	INIT_OK,
	ACTIVATE_OK,
	CMD_STOP_OK,
	KILL_OK,
	MAX_SEMPHR
};
// Index of Semaphore for Mt control
enum SemIndex
{
	Create_ok,  		// MT is created
	Init,   			// Wait authorisation for init
	Init_ok,			// MT is initialised
	Compute,			// Wait authorisation for data processing
	Filter_ok,  		// MT filter is filled
	End_ok, 			// MT has finished his end code
	Kill_ok,			// MT is killed
	Kill,   			// Wait authorisation to be killed
	Synchro,			// MT real time clock
	Continue,
	USED_SEM
};  	
// Index of System Input signals
enum INPUT_SIGNALS_SYS
{
	ROBOT_FAIL, 	//  RTs exceptions     
	SOFT_FAIL,
	SENSOR_FAIL,
	CPU_OVERLOAD,
	PRECTIMEOUT,
	COMPUTETIMEOUT
};
// Index of System Output signals
enum OUTPUT_SIGNALS_SYS
{
	O_ACTIVATE,
	O_NORMAL,
	O_TRANSITE,
	O_END,
	O_REPARAM,
	MAXTABOUTEVENT
};
// all states of a RT
enum RT_STATE
{
	INITSTATE,
	NOCMDACTIV,
	ACTIVE,
	TRANSITE,
	REPARAM,
	END,
	DEFUNCT
};

// all states of a RT
enum RT_CTRL_STATE
{
        CTRL_DEFUNCT,
	CTRL_PAUSE,
	CTRL_RESUME,
	CTRL_ABORT
};
enum RT_ORDER
{
	RT_FIRST,
	RT_LAST,
	RT_MIDDLE
};
enum RT_EXEC_ERROR
{
        RT_EXEC_NO_ERROR,
	RT_EXEC_WRONG_PARAMS,
	RT_EXEC_WRONG_MODE,
	RT_EXEC_PREC_TIMEOUT,
	RT_EXEC_POST_TIMEOUT,
	RT_EXEC_SW_ERROR 
};

enum PHR_STATE
{
	PHR_FAIL,
	PHR_NOACCESS,
	PHR_ACCESS
};

// all states of a MT
enum MT_STATE
{
	MT_NOT_CREATED,
	MT_FREE,
	MT_OCCUPY,
	MT_OVERRUN
};
// Type of events (Error, Input or Output Signals, SemTake or SemGive)
enum DBG_EVT_TYPE
{
	EVT_TYPE_NONE,
	KERNEL_ERROR,
	EVT_INPUT,
	EVT_OUTPUT,
	SEM_TAKE,
	SEM_GIVE
};
// Index of system error 
enum ERROR_NUMBER
{
	MT_ERROR1,
	MT_ERROR2,
	MT_ERROR3,
	MT_ERROR4,
	MT_ERROR5,
	MT_ERROR6,
	RT_ERROR1,
	RT_ERROR2,
	RT_ERROR3,
	RT_ERROR4,
	RT_ERROR5,
	RT_ERROR6,
	RT_ERROR7,
	RT_ERROR8,
	RT_ERROR9,
	RT_ERROR10,
	RT_ERROR11,
	RT_ERROR12,
	CANAL_ERROR1,
	CANAL_ERROR2,
	CANAL_ERROR3,
	CANAL_ERROR4,
	CANAL_ERROR5,
	CANAL_ERROR6,
	CANAL_ERROR7,
	CANAL_ERROR8,
	CANAL_ERROR9,
	PRR_ERROR1,
	PRR_ERROR2,
	PRR_ERROR3,
	PRR_ERROR4,
		// SOSO#step 10-04-00 vvvvv
	PRR_ERROR5,
		// SOSO#step 10-04-00 ^^^^^
	PHR_ERROR1,
	PHR_ERROR2,
	PHR_ERROR3,
	PHR_ERROR4,
	PHR_ERROR5,
	PHR_ERROR6,
	PHR_ERROR7,
	PHR_ERROR8,
	MOD_ERROR1,
	MAXTABERROR
};

enum TYPE_DATA
{
	DATA_NONE,
		// SOSO#6 09-03-00 vvvvv
	DATA_INTEGER,
		// SOSO#6 09-03-00 ^^^^
	DATA_FLOAT,
	DATA_DOUBLE
};

enum BUFFER_MODE
{
	FIRST_DATA,
	LAST_DATA
};

enum TYPE_EVENT
{
	NO_EVENT,   // No occurence of event
	SET_EVENT,  // Set an user event occurence
	TAKE_EVENT  // event take by the system
};


typedef struct
{
	char name[ MAXCHARNAME ];	// Name of the symbol
	int type;   				// Type of variables INTEGER or DOUBLE
	int sizex;  				// Size of variables sizex by sizey
	int sizey;  				// if sizex=sizey=0 => scalar
	int dimtype;				// internal information (scalar,vector or matrix)
	char* p;					// pointers of variable
} PARAMETER;

//Structure for windview
typedef struct
{
	char EventName[ 40 ];
} AUTOMATON_EVENT_INFO;

typedef struct
{
	char SemaphoreName[ 40 ];
} CTRL_SEM_INFO;

typedef struct
{
	char error_mes[ 40 ];
} ERROR_INFO;

#endif
