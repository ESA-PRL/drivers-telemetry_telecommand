/* sscc : C CODE OF SORTED EQUATIONS aa - INLINE MODE */

/* AUXILIARY DECLARATIONS */

#ifndef STRLEN
#define STRLEN 81
#endif
#define _COND(A,B,C) ((A)?(B):(C))
#ifdef TRACE_ACTION
#include <stdio.h>
#endif
#ifndef NULL
#define NULL ((char*)0)
#endif

#ifndef __EXEC_STATUS_H_LOADED
#define __EXEC_STATUS_H_LOADED

typedef struct {
unsigned int start:1;
unsigned int kill:1;
unsigned int active:1;
unsigned int suspended:1;
unsigned int prev_active:1;
unsigned int prev_suspended:1;
unsigned int exec_index;
unsigned int task_exec_index;
void (*pStart)();
void (*pRet)();
} __ExecStatus;

#endif
#define __ResetExecStatus(status) {\
   status.prev_active = status.active; \
   status.prev_suspended = status.suspended; \
   status.start = status.kill = status.active = status.suspended = 0; }
#define __DSZ(V) (--(V)<=0)
#define BASIC_TYPES_DEFINED
typedef int boolean;
typedef int integer;
typedef char* string;
#define _true 1
#define _false 0
#define __aa_GENERIC_TEST(TEST) return TEST;
typedef void (*__aa_APF)();
static __aa_APF *__aa_PActionArray;

#include "aa.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_PROCEDURE_DEFINITIONS
#ifndef _ActivateActionFromTask_DEFINED
#ifndef ActivateActionFromTask
extern void ActivateActionFromTask(string ,string);
#endif
#endif
#ifndef _Deactivate_DEFINED
#ifndef Deactivate
extern void Deactivate(string);
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static boolean __aa_V0;
static boolean __aa_V1;
static boolean __aa_V2;
static boolean __aa_V3;


/* INPUT FUNCTIONS */

void aa_I_ADE_LEFT_Initialise_start () {
__aa_V0 = _true;
}
void aa_I_GNC_SwitchOff_start () {
__aa_V1 = _true;
}
void aa_I_ADE_LEFT_Initialise_GoodEnd () {
__aa_V2 = _true;
}
void aa_I_GNC_SwitchOff_GoodEnd () {
__aa_V3 = _true;
}

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

#define __aa_A1 \
__aa_V0
#define __aa_A2 \
__aa_V1
#define __aa_A3 \
__aa_V2
#define __aa_A4 \
__aa_V3

/* OUTPUT ACTIONS */

/* ASSIGNMENTS */

#define __aa_A5 \
__aa_V0 = _false
#define __aa_A6 \
__aa_V1 = _false
#define __aa_A7 \
__aa_V2 = _false
#define __aa_A8 \
__aa_V3 = _false

/* PROCEDURE CALLS */

#define __aa_A9 \
ActivateActionFromTask("ADE_LEFT_Initialise","left")
#define __aa_A10 \
Deactivate("ADE_LEFT_Initialise")
#define __aa_A11 \
ActivateActionFromTask("GNC_SwitchOff","")
#define __aa_A12 \
Deactivate("GNC_SwitchOff")

/* CONDITIONS */

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int aa_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __aa__reset_input () {
__aa_V0 = _false;
__aa_V1 = _false;
__aa_V2 = _false;
__aa_V3 = _false;
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __aa_R[5] = {_true,
 _false,
 _false,
 _false,
 _false};

/* AUTOMATON ENGINE */

int aa () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[11];
E[0] = __aa_R[4]&&!(__aa_R[0]);
E[1] = E[0]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 4\n"),
#endif
__aa_A4);
if (E[1]) {
__aa_A12;
#ifdef TRACE_ACTION
fprintf(stderr, "__aa_A12\n");
#endif
}
E[2] = E[1];
E[3] = __aa_R[1]&&!(__aa_R[0]);
E[4] = E[3]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__aa_A1));
E[4] = __aa_R[0]||(__aa_R[1]&&E[4]);
E[3] = E[3]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__aa_A1);
if (E[3]) {
__aa_A9;
#ifdef TRACE_ACTION
fprintf(stderr, "__aa_A9\n");
#endif
}
E[5] = __aa_R[2]&&!(__aa_R[0]);
E[6] = E[5]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 3\n"),
#endif
__aa_A3));
E[6] = E[3]||(__aa_R[2]&&E[6]);
E[5] = E[5]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 3\n"),
#endif
__aa_A3);
if (E[5]) {
__aa_A10;
#ifdef TRACE_ACTION
fprintf(stderr, "__aa_A10\n");
#endif
}
E[7] = __aa_R[3]&&!(__aa_R[0]);
E[8] = E[7]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__aa_A2));
E[8] = E[5]||(__aa_R[3]&&E[8]);
E[7] = E[7]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__aa_A2);
if (E[7]) {
__aa_A11;
#ifdef TRACE_ACTION
fprintf(stderr, "__aa_A11\n");
#endif
}
E[0] = E[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 4\n"),
#endif
__aa_A4));
E[0] = E[7]||(__aa_R[4]&&E[0]);
E[9] = E[4]||E[6]||E[8]||E[0];
E[10] = __aa_R[1]||__aa_R[2]||__aa_R[3]||__aa_R[4];
__aa_R[0] = !(_true);
__aa_R[1] = E[4];
__aa_R[2] = E[6];
__aa_R[3] = E[8];
__aa_R[4] = E[0];
__aa__reset_input();
return E[9];
}

/* AUTOMATON RESET */

int aa_reset () {
__aa_R[0] = _true;
__aa_R[1] = _false;
__aa_R[2] = _false;
__aa_R[3] = _false;
__aa_R[4] = _false;
__aa__reset_input();
return 0;
}
