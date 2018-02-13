 
/*  A Bison parser, made from rapdgrammar.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	EOL_TOKEN	258
#define	SUBSYSTEM_TOKEN	259
#define	NODES_TOKEN	260
#define	MODE_TOKEN	261
#define	ACTION_TOKEN	262
#define	START_SOL_TOKEN	263
#define	END_SOL_TOKEN	264
#define	ID	265
#define	NUMBER	266
#define	DATA_RATE	267
#define	DATA_UNIT	268
#define	EXEC_TOKEN	269
#define	START_TOKEN	270
#define	STOP_TOKEN	271
#define	WAIT_UNTIL_TOKEN	272
#define	WAIT_TIME_TOKEN	273
#define	WAIT_ACTIVITY_END_TOKEN	274

#line 1 "rapdgrammar.y"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE_IS_DECLARED 1 
#define MSDOS

extern char *yytext;

extern int yylex();
extern FILE* yyin;

void yyerror(char *s);
int  yywrap(void);
void initParamList();
void newParam( char *p);

char paramList[1000];
int  paramNumber;

/* redefined to extend the size of string */
int ewmParsError=0;
int nodesCnt, modeCnt, nodeValCnt, actionCnt;
//int yydebug=1;
void setNumSol(int nsol){};
 char * mlTime;
int insTotPwr(float a, char print ){return 0;};
int insNodeVal( int b , float c){return 0;};
int insAction(char *a , float b, char* c, char *d,  char e){return 0;};
int insSubSys( char * name, char print, float f){return 0;};
void secToMlt( int secTot ){};
int mltToSec( int solN, int hh, int mm, int ss){return 0;};

void setMLTSecondsGlobal(int solNum){};
void insNodesNum ( int n){};
void insNodeName( char * name){};
void insMode( char * name, char print){};
void initRapd(){};

  
void ExecActivity  (  char *ActId, char * ActName,int nPar, char *paramList) {
  printf("In RAPD: ExecActivity ID=%s ACT=%s NbrParams=%d params=%s\n", ActId, ActName,nPar ,paramList );
  orcExecActFromAP(ActName, ActName, paramList); 
   printf("In RAPD: ExecActivity ID=%s ACT=%s completed \n", ActId, ActName);

}
void StartActivity (    char *ActId, char * ActName,int nPar, char *paramList) {
  printf("In RAPD: StartActivity ID=%s ACT=%s NbrParams=%d params=%s\n", ActId, ActName,nPar ,paramList );
  orcStartActFromAP(ActName, paramList); 
  printf("In RAPD: StartActivity ID=%s ACT=%s completed \n", ActId, ActName);
}
void StopActivity ( char *ActId) {
  printf("In RAPD: StopActivity ID=%s \n", ActId );
  orcStopActivity(ActId);
}
void EndOfSol() {
};
void waitAbsTime(int a) {
  printf("WAIT ABS TIME %d\n", a);
  char params[1024];
  sprintf(params, "1 %d", a);
  orcExecActFromAP("WaitTime", params); 
};
 void waitRelTime(int a){
   printf("WAIT RELATIVE TIME %d\n", a);
   char params[1024];
   sprintf(params, "2 %d", a);
   orcExecActFromAP("WaitTime", params); 
 };
 void waitActivityEnd(char *a){
   printf("WAIT ACTIVITY END %s\n", a);
   orcWaitActivityEnd(a);
};
void insDataRate(float a, char b){}; 



#line 58 "rapdgrammar.y"
typedef union
{
        int     intNum;
        float   number;
        char    string[512];
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		86
#define	YYFLAG		-32768
#define	YYNTBASE	26

#define YYTRANSLATE(x) ((unsigned)(x) <= 274 ? yytranslate[x] : 49)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
    25,     2,     2,    20,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    23,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    21,     2,    22,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    10,    13,    16,    18,    21,    24,
    27,    28,    31,    35,    41,    45,    51,    54,    57,    59,
    60,    66,    70,    71,    72,    76,    78,    82,    84,    87,
    88,    94,    96,   100,   105,   106,   108,   114,   118,   119,
   121,   125,   127,   129,   131,   134
};

static const short yyrhs[] = {    27,
     0,    26,    27,     0,     3,     0,    29,     3,     0,    32,
     3,     0,    28,     3,     0,     1,     0,    17,    43,     0,
    18,    43,     0,    19,    10,     0,     0,    30,    31,     0,
    14,    10,    44,     0,    14,    10,    20,    10,    44,     0,
    15,    10,    44,     0,    15,    10,    20,    10,    44,     0,
    16,    10,     0,     8,    11,     0,     9,     0,     0,    34,
    35,    33,    38,    47,     0,     4,    10,    11,     0,     0,
     0,     5,    36,    37,     0,    10,     0,    37,    20,    10,
     0,    39,     0,    38,    39,     0,     0,     6,    10,    40,
    41,    42,     0,    11,     0,    41,    20,    11,     0,    21,
    11,    12,    22,     0,     0,    11,     0,    11,    23,    11,
    23,    11,     0,    24,    45,    25,     0,     0,    46,     0,
    45,    20,    46,     0,    11,     0,    10,     0,    48,     0,
    47,    48,     0,     7,    10,    43,    10,    10,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    74,    75,    77,    78,    79,    80,    81,    84,    85,    86,
    89,    90,    92,    94,    96,    98,   100,   102,   104,   108,
   108,   111,   114,   115,   115,   118,   119,   122,   123,   126,
   126,   129,   130,   133,   134,   138,   139,   142,   143,   146,
   147,   150,   151,   154,   155,   158
};

static const char * const yytname[] = {   "$","error","$undefined.","EOL_TOKEN",
"SUBSYSTEM_TOKEN","NODES_TOKEN","MODE_TOKEN","ACTION_TOKEN","START_SOL_TOKEN",
"END_SOL_TOKEN","ID","NUMBER","DATA_RATE","DATA_UNIT","EXEC_TOKEN","START_TOKEN",
"STOP_TOKEN","WAIT_UNTIL_TOKEN","WAIT_TIME_TOKEN","WAIT_ACTIVITY_END_TOKEN",
"','","'['","']'","':'","'('","')'","commandList","command","wait","activityExecControl",
"@1","activityExecution","subsystem","@2","subsystemNameDef","nodesDef","@3",
"nodeList","listOfModes","modeDef","@4","nodesVal","optionalDataRate","timeSeconds",
"listOfPars","parameters","parameter","listOfActions","ActionDef",""
};
#endif

static const short yyr1[] = {     0,
    26,    26,    27,    27,    27,    27,    27,    28,    28,    28,
    30,    29,    31,    31,    31,    31,    31,    31,    31,    33,
    32,    34,    35,    36,    35,    37,    37,    38,    38,    40,
    39,    41,    41,    42,    42,    43,    43,    44,    44,    45,
    45,    46,    46,    47,    47,    48
};

static const short yyr2[] = {     0,
     1,     2,     1,     2,     2,     2,     1,     2,     2,     2,
     0,     2,     3,     5,     3,     5,     2,     2,     1,     0,
     5,     3,     0,     0,     3,     1,     3,     1,     2,     0,
     5,     1,     3,     4,     0,     1,     5,     3,     0,     1,
     3,     1,     1,     1,     2,     5
};

static const short yydefact[] = {     0,
     7,     3,     0,     0,     0,     0,     0,     1,     0,     0,
     0,     0,    23,     0,    36,     8,     9,    10,     2,     6,
     4,     0,    19,     0,     0,     0,    12,     5,    24,    20,
    22,     0,    18,    39,    39,    17,     0,     0,     0,     0,
     0,    13,     0,    15,    26,    25,     0,     0,    28,     0,
    39,    43,    42,     0,    40,    39,     0,    30,     0,    29,
    21,    44,    37,    14,     0,    38,    16,    27,     0,     0,
    45,    41,    32,    35,     0,     0,     0,    31,     0,    33,
     0,    46,     0,    34,     0,     0
};

static const short yydefgoto[] = {     7,
     8,     9,    10,    11,    27,    12,    38,    13,    30,    37,
    46,    48,    49,    69,    74,    78,    16,    42,    54,    55,
    61,    62
};

static const short yypact[] = {    29,
-32768,-32768,    -7,     1,     1,    -4,    10,-32768,    20,    28,
    26,    33,    34,    38,    31,-32768,-32768,-32768,-32768,-32768,
-32768,    41,-32768,    43,    45,    46,-32768,-32768,-32768,-32768,
-32768,    47,-32768,   -16,   -15,-32768,    49,    51,    37,    52,
     5,-32768,    53,-32768,-32768,    44,    56,    14,-32768,    50,
    48,-32768,-32768,   -18,-32768,    48,    57,-32768,    58,-32768,
    62,-32768,-32768,-32768,     5,-32768,-32768,-32768,    59,     1,
-32768,-32768,-32768,    30,    61,    63,    64,-32768,    66,-32768,
    65,-32768,    60,-32768,    73,-32768
};

static const short yypgoto[] = {-32768,
    71,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    32,-32768,-32768,-32768,    -5,   -34,-32768,    16,
-32768,    18
};


#define	YYLAST		82


static const short yytable[] = {    17,
    44,    65,    14,    40,    43,    18,    66,    41,    41,    85,
     1,    15,     2,     3,    52,    53,    64,   -11,   -11,    47,
    59,    67,    20,   -11,   -11,   -11,     4,     5,     6,     1,
    21,     2,     3,    22,    23,    28,   -11,   -11,    29,    24,
    25,    26,   -11,   -11,   -11,     4,     5,     6,    31,    76,
    77,    33,    34,    32,    35,    36,    47,    39,    45,    50,
    63,    51,    56,    57,    75,    58,    68,    70,    59,    73,
    79,    41,    86,    80,    81,    82,    83,    19,    71,    60,
    72,    84
};

static const short yycheck[] = {     5,
    35,    20,    10,    20,    20,    10,    25,    24,    24,     0,
     1,    11,     3,     4,    10,    11,    51,     8,     9,     6,
     7,    56,     3,    14,    15,    16,    17,    18,    19,     1,
     3,     3,     4,     8,     9,     3,     8,     9,     5,    14,
    15,    16,    14,    15,    16,    17,    18,    19,    11,    20,
    21,    11,    10,    23,    10,    10,     6,    11,    10,    23,
    11,    10,    10,    20,    70,    10,    10,    10,     7,    11,
    10,    24,     0,    11,    11,    10,    12,     7,    61,    48,
    65,    22
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 77 "rapdgrammar.y"
{;
    break;}
case 4:
#line 78 "rapdgrammar.y"
{;
    break;}
case 5:
#line 79 "rapdgrammar.y"
{;
    break;}
case 6:
#line 80 "rapdgrammar.y"
{;
    break;}
case 7:
#line 81 "rapdgrammar.y"
{;
    break;}
case 8:
#line 84 "rapdgrammar.y"
{ waitAbsTime(yyvsp[0].intNum); ;
    break;}
case 9:
#line 85 "rapdgrammar.y"
{ waitRelTime(yyvsp[0].intNum); ;
    break;}
case 10:
#line 86 "rapdgrammar.y"
{ waitActivityEnd(yyvsp[0].string); ;
    break;}
case 11:
#line 89 "rapdgrammar.y"
{ initParamList(); ;
    break;}
case 13:
#line 93 "rapdgrammar.y"
{        ExecActivity ("*", yyvsp[-1].string, paramNumber, paramList);;
    break;}
case 14:
#line 95 "rapdgrammar.y"
{        ExecActivity (yyvsp[-3].string, yyvsp[-1].string,paramNumber, paramList);;
    break;}
case 15:
#line 97 "rapdgrammar.y"
{		StartActivity ("*", yyvsp[-1].string,paramNumber, paramList);;
    break;}
case 16:
#line 99 "rapdgrammar.y"
{		StartActivity (yyvsp[-3].string, yyvsp[-1].string,paramNumber, paramList);;
    break;}
case 17:
#line 101 "rapdgrammar.y"
{		StopActivity (yyvsp[0].string);;
    break;}
case 18:
#line 103 "rapdgrammar.y"
{		setNumSol(yyvsp[0].number);  ;
    break;}
case 19:
#line 105 "rapdgrammar.y"
{		EndOfSol() ; ;
    break;}
case 20:
#line 108 "rapdgrammar.y"
{modeCnt=0; ;
    break;}
case 22:
#line 111 "rapdgrammar.y"
{ insSubSys( yyvsp[-1].string, 1, yyvsp[0].number) ;;
    break;}
case 24:
#line 115 "rapdgrammar.y"
{nodesCnt = 0; ;
    break;}
case 25:
#line 115 "rapdgrammar.y"
{ insNodesNum(nodesCnt); ;
    break;}
case 26:
#line 118 "rapdgrammar.y"
{insNodeName( yyvsp[0].string); ;
    break;}
case 27:
#line 119 "rapdgrammar.y"
{insNodeName( yyvsp[0].string); ;
    break;}
case 28:
#line 122 "rapdgrammar.y"
{modeCnt++; ;
    break;}
case 29:
#line 123 "rapdgrammar.y"
{modeCnt++; ;
    break;}
case 30:
#line 126 "rapdgrammar.y"
{ insMode( yyvsp[0].string, 1); ;
    break;}
case 32:
#line 129 "rapdgrammar.y"
{ insTotPwr( yyvsp[0].number,1) ; nodeValCnt=0;;
    break;}
case 33:
#line 130 "rapdgrammar.y"
{ nodeValCnt++;  insNodeVal( nodeValCnt, yyvsp[0].number); ;
    break;}
case 34:
#line 133 "rapdgrammar.y"
{ insDataRate(yyvsp[-2].number*yyvsp[-1].number,1);  printf("\n"); ;
    break;}
case 36:
#line 138 "rapdgrammar.y"
{ yyval.intNum = yyvsp[0].number ; ;
    break;}
case 37:
#line 139 "rapdgrammar.y"
{ yyval.intNum = mltToSec( 0, yyvsp[-4].number, yyvsp[-2].number, yyvsp[0].number); ;
    break;}
case 39:
#line 143 "rapdgrammar.y"
{ ;
    break;}
case 41:
#line 147 "rapdgrammar.y"
{ ;
    break;}
case 42:
#line 150 "rapdgrammar.y"
{ newParam( yytext); ;
    break;}
case 43:
#line 151 "rapdgrammar.y"
{ newParam( yytext); ;
    break;}
case 46:
#line 158 "rapdgrammar.y"
{ insAction( yyvsp[-3].string, yyvsp[-2].intNum, yyvsp[-1].string, yyvsp[0].string,  1); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 162 "rapdgrammar.y"


/*
int main(int argc, char *argv[])
{
 
        char fname[100];

        initRapd();
        printf("Opening file apin\n");
        strcpy(fname, "C:/RAPDwork/apin.txt");
        yyin= fopen(fname,"r");   
        printf("\n\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        if (yyin == 0) 
        {   printf("Cant open file %s\n", fname); 
        exit (1);
        }    
        printf("\n-Start Parsing RAPD: apin-\n"); 
        yyparse();
             
        printf("-End of  parsing RAPD:apin \n\n\n");
        printf("\n\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

        printf("Opening file ap.txt\n");
        strcpy(fname, "C:/RAPDwork/ap.txt");        
        yyin= fopen(fname,"r");   
        if (yyin == 0) 
        {   printf("Cant open file %s\n", fname); 
            exit (1);
        }    
        printf("Start Parsing RAPD-\n"); 
        yyparse();
               
        printf("End of  parsing RAPD \n\n\n");
        
        processActivityPlan();

        exit(0) ;
}

*/
int activityPlanExec(const char *apname)
{
  fprintf(stderr, "Executing the AP: %s\n", apname);
  
  initRapd();
  // printf("Opening file apin\n");
  // yyin= fopen("apin.txt","r");   
  
  //printf("\n-Start Parsing RAPD: apin-\n"); 
  //yyparse();
  
  //printf("-End of  parsing RAPD:apin \n");
  
  // printf("Opening file\n");
  yyin= fopen(apname,"r");   
  
  fprintf(stderr, "-Start Parsing RAPD: %s-\n", apname); 
  yyparse();
  
  fprintf(stderr, "-End of  parsing RAPD \n");
  // printActivityTable();
  // printSubSysTab();
  // printActionTab();
  
  return 1;
}

void initParamList()
{   
   paramNumber=0;
   paramList[0] ='\0';
} 

void newParam( char *p)
{
   
   char temp[1000];
   
   paramNumber++;
   strcpy(temp, paramList);
   sprintf(paramList,"%s %s", temp, p);
       
}

int yywrap(void) 
{   
        return(1);
} 

void yyerror(char *s) 
{
extern char * yytext;
ewmParsError = 1;
fprintf(stderr,"      -->>!!!! PARSER ERROR !!!!\"%s\" in \"%s\"\n\n",s, yytext);
/* exit(1); */
}


