/*
 * GeneralSupportLibrary.h
 *
 *  Created on: Jan 22, 2010
 *      Author: nre
 */

#ifndef GENERALSUPPORTLIBRARY_H_
#define GENERALSUPPORTLIBRARY_H_

//
// General use definitions
//
#ifndef ERROR
   #define ERROR -1
#endif
#ifndef OK
   #define OK 0
#endif
#ifndef DEG_TO_RAD
   #define DEG_TO_RAD M_PI/180.0
#endif
#ifndef RAD_TO_DEG
   #define RAD_TO_DEG 180.0/M_PI
#endif
#ifndef BOLTZMANN
   #define BOLTZMANN 5.6704E-8 // W*m-2*K-4
#endif
#ifndef KELVIN_TO_CELSIUS
   #define KELVIN_TO_CELSIUS 273.15
#endif
#ifndef SEC_PER_HOUR
   #define SEC_PER_HOUR 3600.0
#endif
#ifndef MARS_MEAN_RADIUS
#define MARS_MEAN_RADIUS   3389.5
#endif

#ifndef MAX_NUMBER_RAPD_EVENTS
#define MAX_NUMBER_RAPD_EVENTS   100000
#endif
//
// General use libraries
//
#ifndef __STDIO__
   #define __STDIO__
   #include <stdio.h>
#endif

#ifndef __STRING__
   #define __STRING__
   #include <string.h>
#endif

#ifndef __STDLIB__
   #define __STDLIB__
   #include <stdlib.h>
#endif

#ifndef __CTYPE__
   #define __CTYPE__
   #include <ctype.h>
#endif

#ifndef __CTYPES__
   #define __CTYPES__
   #include <sys/types.h>
#endif

#include <complex>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;
namespace GeneralSupport
{
#ifndef MAX_CONFLINE_SIZE
#define MAX_CONFLINE_SIZE 512
#endif

#ifndef NTERP_MATRIX_MAX_SIZE
   #define INTERP_MATRIX_MAX_SIZE 70
#endif
#ifndef MAX_MATRIC_COL
   #define MAX_MATRIC_COL         2     // Do NOT change this value. Max val allowed by algorithm is 2
#endif
#ifndef MAX_LOAD_MATRIX_COL
   #define MAX_LOAD_MATRIX_COL    10    // Do NOT change this value, other functions are related to it
#endif
#ifndef MAX_LOAD_MATRIX_ROW
   #define MAX_LOAD_MATRIX_ROW    70
#endif


struct rapdTab_s
{
  int time;
  double power;
};
 
typedef struct rapdTab_s rapdTab;
 
 
 int readRapdFile(char * fname);
 double getTotPwr( int t) ;
 
 int read_int( FILE *infile,  char label[], int* nRetVal);
 int read_int( FILE *infile,  char label[], unsigned int* nRetVal);
 int read_double( FILE *infile, char label[], double* retVal);
 int read_float( FILE *infile, char label[], float* retVal);
 int Interp2DMatrix(double matrix[INTERP_MATRIX_MAX_SIZE+1][INTERP_MATRIX_MAX_SIZE+1], double argx, double argy, int nx, int ny, double* retVal );
 int Interp2DMatrix(float matrix[INTERP_MATRIX_MAX_SIZE+1][INTERP_MATRIX_MAX_SIZE+1], float argx, float argy, int nx, int ny, float* retVal );
 int InterpMatrix(int nr, float (*matrixx)[2], float arg, int n, float* retVal );
 int InterpMatrix(int nr, double (*matrixx)[2], double arg, int n, double* retVal );
 double Interp(int Nc, double *x,  double *fx, double arg,int n );
 float Interp(int nc, float *x, float *fx, float arg, int n );
 double InterpNoExtra(int nc, double *x, double *fx, double arg, int n );
 int ProfileIndex(double arg, double *profilearray, int dimOfArray);
 int ProfileIndex(float arg, float *profilearray, int nDimOfArray);
 int secondDegree(double a , double b, double c, double *x1,double *x2);
 int ReadDoubleArray( FILE *infile,  char label[], unsigned nCol, double   *retMatrix);
 int ReadFloatArray( FILE *infile,  char label[], unsigned nCol, float   *retMatrix);
 int ReadString( FILE*      infile,  char  label[],  char  retValue[]);
 int CheckOutDValue( double value,double maxValue,double minValue);
 int readDblMatrix(    FILE*      infile,         // pointer to file
		       char       label[],        // marking label
		       int   nRow,
		       int   nCol,
		       double returnMatrix[][MAX_LOAD_MATRIX_COL]);     // returned double val

 int thirdDegree(double a , double b, double c, complex <double> *x1, complex <double> *x2, complex <double> *x3);
 int fourthDegree(double a,double b,double c,double d, complex <double> *z1, complex <double> *z2, complex <double> *z3, complex <double> *z4);
 
 //int fourthDegree(double a,double b,double c,double d, double complex *z1, double complex *z2, double complex *z3,double complex *z4);
 
#ifndef MAX_LOG_VARIABLES
#define MAX_LOG_VARIABLES    70
#endif
 
 struct logVariablesListType {
   unsigned idx[MAX_LOG_VARIABLES];
   char* description[MAX_LOG_VARIABLES];
   char* measUnit[MAX_LOG_VARIABLES];
   float dim[MAX_LOG_VARIABLES];
 };
 
 
 struct logVariablesStruct { const unsigned idx; const char* description; const char* measUnit; const float dim;};
 
 static const logVariablesStruct logVariables[] =
   {          //1234567890123  //1234567890123
     {   0,  " Julian date ", "   [days]    ", 13.4},
     {   1,  " ltst ",        " [hr] "       , 6.3 },
     {   2,  "year",          "[yr]"         , 4.0 },
     {   3,  "month",         "[mth]"        , 5.0 },
     {   4,  " day ",         "[day]"        , 5.0 },
     {   5,  "hour",          "[hr]"         , 4.0 },
     {   6,  " min ",         "[min]"        , 5.0 },
     {   7,  " sec ",         "[sec]"        , 5.0 },
     //Electrical 1234567890123  //1234567890123
     {   8,  " Bus V ",       "  [V]  "      , 7.3 },
     {   9,  "Bt  SOC",       "  [%]  "      , 7.2 },
     {  10,  "SA pwr ",       "[Watts]"      , 7.2 },
     {  11,  "S3R pwr",       "[Watts]"      , 7.2 },
     {  12,  "BCDRpwr",       "[Watts]"      , 7.2 },
     {  13,  "Bt  pwr",       "[Watts]"      , 7.2 },
     {  14,  "Bt Pdis",       "[Watts]"      , 7.2 },
     {  15,  "PDU pwr",       "[Watts]"      , 7.2 },
     {  16,  "Bt Enrgy",      "  [Wh]  "     , 8.2 },
     {  17,  "DayEnrgy",      "  [Wh]  "     , 8.2 },
     {  18,  "NigEnrgy",      "  [Wh]  "     , 8.2 },
     {  19,  "SunEnrgy",      "  [Wh]  "     , 8.2 },
     {  20,  "Bt cpcty",      "  [Ah]  "     , 8.2 },
     // Thermal   1234567890123  //1234567890123
     {  21,  "Pnl 1 T",       "  [C]  "      , 7.2 },
     {  22,  "Pnl 2 T",       "  [C]  "      , 7.2 },
     {  23,  "Pnl 3 T",       "  [C]  "      , 7.2 },
     {  24,  "Pnl 1 F",       " [W/m2]"      , 7.2 },
     {  25,  "Pnl 2 F",       " [W/m2]"      , 7.2 },
     {  26,  "Pnl 3 F",       " [W/m2]"      , 7.2 },
     {  27,  "Pnl 1 mxP",     "   [W]   "      , 9.3 },
     {  28,  "Pnl 2 mxP",     "   [W]   "      , 9.3 },
     {  29,  "Pnl 3 mxP",     "   [W]   "      , 9.3 },
     {  30,  "Air Tmp",       "  [C]  "      , 7.2 },
     {  31,  "Sky Tmp",       "  [C]  "      , 7.2 },
     {  32,  "Grd Tmp",       "  [C]  "      , 7.2 },
     {  33,  "lmd Air Temp",  "     [K]    " ,12.4 },
     {  34,  "lmd Sky Temp",  "     [K]    " ,12.4 },
     {  35,  "lmd Grd Temp",  "     [K]    " ,12.4 },
     {  36,  "mcd Air Temp",  "     [K]    " ,12.4 },
     {  37,  "mcd Sky Temp",  "     [K]    " ,12.4 },
     {  38,  "mcd Grd Temp",  "     [K]    " ,12.4 },
     {  39,  "mcd-lmd AirT",  "     [K]    " ,12.4 },
     {  40,  "mcd-lmd SkyT",  "     [K]    " ,12.4 },
     {  41,  "mcd-lmd GrdT",  "     [K]    " ,12.4 },
     {  42,  "lmd tot flux",  "   [W/m2]   " ,12.4 },
     {  43,  "lmd sct flux",  "   [W/m2]   " ,12.4 },
     {  44,  "lmd ir flux ",  "   [W/m2]   " ,12.4 },
     {  45,  "mcd tot flux",  "   [W/m2]   " ,12.4 },
     {  46,  "mcd ir flux ",  "   [W/m2]   " ,12.4 },
     {  47,  "zim tot flux",  "   [W/m2]   " ,12.4 },
     {  48,  "zim sct flux",  "   [W/m2]   " ,12.4 },
     {  49,  "mcd-lmd totF",  "   [W/m2]   " ,12.4 },
     {  50,  "mcd-zim totF",  "   [W/m2]   " ,12.4 },
     {  51,  "lmd-zim totF",  "   [W/m2]   " ,12.4 },
     {  52,  "mcd-lmd IR F",  "   [W/m2]   " ,12.4 },
     {  53,  "lmd-zim sctF",  "   [W/m2]   " ,12.4 },
     

   };

 static const int MAX_OUTPUT_VARIABLES = 24;
 
 enum variableNamesEnum { JD = 0, ltst, year, month, day, hour, minute, second, busVoltage, batterySOC, totalSolarGeneratedPower, totalS3Rpower, BCDRpower,BatteryPower,BattDissipatedPower,
			  totalRequestedPower, BatteryEnergy, dayRequiredEnergy, nightRequiredEnergy, SunEnergy, BatteryCapacity, Panel1Temp, Panel2Temp, Panel3Temp, Panel1Flux, Panel2Flux, Panel3Flux,
			  Panel1MaxPower, Panel2MaxPower, Panel3MaxPower,AirTemp, SkyTemp, GroundTemp,
			  lmdAirTemp,lmdSkyTemp,lmdGrdTemp,mcdAirTemp,mcdSkyTemp,mcdGrdTemp,mcdVsLmdAir,mcdVsLmdSky,mcdVsLmdGrd, lmdTotFlux,lmdSctFlux,lmdIrFlux,mcdTotFlux,mcdIrFlux,zimTotFlux,zimSctFlux,
			  mcdVsLmdTotFlux,mcdVsZimTotFlux,lmdVsZimTotFlux,mcdVsLmdIrFlux,lmdVsZimSctFlux};
 
 class loggerClass
 {
   
 public:
   
   loggerClass(char *FileName);
   virtual ~loggerClass();
   
   void setSeparator(char* separatorChar);
   void setOutputInterval(double outInt);
   
   int loggerHeader(double simStartJulianDate , double ls ,
		    double roverInitialLatitude, double roverInitialLongitude);
   
   void displayHeader(bool display);
   void displayFooter(bool display);
   
   void writeInitVars(void);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
		       variableNamesEnum v21);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
		       variableNamesEnum v21, variableNamesEnum v22);
   void loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
		       variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
		       variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
		       variableNamesEnum v21, variableNamesEnum v22, variableNamesEnum v23);
   
   int writer(int numInputs, double elapSec);
   int loggerLog(double elapSec, double a1, double a2);
   int loggerLog(double elapSec,double a0, double a1, double a2);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,
		 double a21);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,
		 double a21,double a22);
   int loggerLog(double elapSec,double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		 double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,
		 double a21,double a22,double a23);
   
   void setLogVariablesList(logVariablesListType logList);
 private:
   char configFileName[512];
   std::ofstream outfile;
   time_t startTime;
   
   int variablesNumber;
   variableNamesEnum variableNames[MAX_OUTPUT_VARIABLES];
   double dblV[MAX_OUTPUT_VARIABLES];
   
   bool dispHeader;
   bool dispFooter;
   char separator[1];
   double firstJD;
   double elapsedTimeSeconds;
   double outputInt;
   
   logVariablesListType logVariablesList;
   
 }; // end class
 
 
}
#endif /* GENERALSUPPORTLIBRARY_H_ */
