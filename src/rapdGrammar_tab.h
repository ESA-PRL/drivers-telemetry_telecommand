typedef union
{
        int     intNum;
        float   number;
        char    string[512];
} YYSTYPE;
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


extern YYSTYPE yylval;
