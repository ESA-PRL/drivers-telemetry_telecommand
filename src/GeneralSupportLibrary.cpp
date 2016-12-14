/*
 * GeneralSupportLibrary.cpp
 *
 *  Created on: Jan 22, 2010
 *      Author: nre
 */
#include "GeneralSupportLibrary.h"
#include <complex>
#include <cmath>

using namespace std;
namespace GeneralSupport

{

  rapdTab RAPD_Tab[MAX_NUMBER_RAPD_EVENTS];
  static int RAPD_TabMaxIndex=0;
  static int rapdIndex=0;
  
  int readRapdFile(char * fname)
  {
    FILE *fp;
    int t;
    double pwr,data;
    
    fp= fopen(fname,"r");
    if (fp == 0)
      {
	printf("Cant open file %s\n", fname);
	exit (1);
      }
    while ( ! feof( fp) )
      {
	fscanf(fp, "%d %lf %lf\n", &t, &pwr, &data);
	RAPD_Tab[RAPD_TabMaxIndex].time = t;
	RAPD_Tab[RAPD_TabMaxIndex++].power = pwr;
	// printf("-->%d %f\n",t,pwr);
      }
    RAPD_TabMaxIndex--;
    return OK;
  }
  
  //--------------------------------------------------------
  double getTotPwr( int t) // -1.0 if time > tmax.
  {
    if ( t<0 ) 	exit (1);
    if ( t == 0 ) return (0.0);
    // GiP added this to cycle table //
    t =  t % RAPD_Tab[RAPD_TabMaxIndex].time;
    // End Gip add
    if ( t >= RAPD_Tab[rapdIndex].time )
      {
	while ( rapdIndex < RAPD_TabMaxIndex )
	  {
	    if ( t < RAPD_Tab[rapdIndex+1].time) return RAPD_Tab[rapdIndex].power;
	    else rapdIndex++;
	  }
	rapdIndex--;
	return(-1.0) ;
      }
    else
      {
	while ( rapdIndex > 0 )
	  {
	    if ( t >= RAPD_Tab[rapdIndex-1].time) return RAPD_Tab[rapdIndex - 1].power;
	    else rapdIndex--;
	  }
	return(-1.0) ;
      }
    return(-1.0) ;
  }
  
  
  
  /******************************************************************************/
  /*
  ** Method: 	read_int()
  **
  ** Description: read from a specified file a variable of type int marked with
  **              the given label. Returns the value of type int read.
  **
  **              example:
  **                 if the file 'in.conf' looks like
  **
  **                 ...
  **                 mylab
  **                 33
  **                 ...
  **
  **                 the following code
  **                    infile = fopen("in.conf","r");
  **                    x = read_int(infile, "mylab");
  **
  **                 returns x=33
  **
  **              warnings: if label is present twice in the file,
  **                        the first occurrence is used
  **
  ** Prototype:
  **
  */
  
  int read_int( FILE *infile,            // pointer to file
		char label[],            // marking label
		int* nRetVal)            // returned int val
  {
    char  line[MAX_CONFLINE_SIZE];      // used to scan the file
    char  lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
    float tmp;                          // value is read as float
    
    
    fseek(infile, 0, SEEK_SET);         // go to beginning of file
    
    // read a line until the specified label is found at the beginning //
    do
      {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
          printf("   Utility> read_int(): ERROR reach EndOfFile without finding parameter >%s<\n", label);
          return ERROR;
       }
       sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.    //
   // Read the line and scan it for the value                        //
   fgets(line, (MAX_CONFLINE_SIZE-1), infile);
   sscanf(line,"%f",&tmp);
   *nRetVal = (int)(tmp);

   return OK;
} // read_int()

int read_int( FILE *infile,            // pointer to file
              char label[],            // marking label
              unsigned int* nRetVal)            // returned int val
{
   char  line[MAX_CONFLINE_SIZE];      // used to scan the file
   char  lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
   float tmp;                          // value is read as float


   fseek(infile, 0, SEEK_SET);         // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
          printf("   Utility> read_int(): ERROR reach EndOfFile without finding parameter >%s<\n", label);
          return ERROR;
       }
       sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.    //
   // Read the line and scan it for the value                        //
   fgets(line, (MAX_CONFLINE_SIZE-1), infile);
   sscanf(line,"%f",&tmp);
   *nRetVal = (unsigned)(tmp);

   return OK;
} // read_int()


/******************************************************************************/
/*
** Method: 	read_double()
**
** Description: read from a specified file a variable of type double marked
**              with the given label.
**
**              example
**                 if the file 'in.dat' looks like
**
**                 ...
**                 mylab
**                 33.45
**                 ...
**
**                 the following code:
**                    infile = fopen("in.dat","r");
**                    x = read_double(infile, "mylab");
**
**                 returns x=33.45
**
**    warnings: if label is present twice in the file,
**              the first occurrence is used
**
** Prototype:
**
*/
int read_double( FILE *infile,        // pointer to file
                 char label[],        // marking label
                 double* retVal)      // returned double val
{
   char line[MAX_CONFLINE_SIZE];      // used to scan the file
   char lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
   double tmp;                         // value is read as float and put in tmp


   fseek(infile, 0, SEEK_SET);        // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
         printf("   Utility> read_double(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
         return ERROR;
      }
      sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.     //
   // Read the line and scan it for the value                         //
   fgets(line, (MAX_CONFLINE_SIZE-1), infile);
   sscanf(line,"%lf",&tmp);
   *retVal = (tmp);

   return OK;
}  // read_double()


int read_float( FILE *infile,        // pointer to file
                 char label[],        // marking label
                 float* retVal)      // returned double val
{
   char line[MAX_CONFLINE_SIZE];      // used to scan the file
   char lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
   float tmp;                         // value is read as float and put in tmp


   fseek(infile, 0, SEEK_SET);        // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
         printf("   Utility> read_float(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
         return ERROR;
      }
      sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.     //
   // Read the line and scan it for the value                         //
   fgets(line, (MAX_CONFLINE_SIZE-1), infile);
   sscanf(line,"%f",&tmp);
   *retVal = (tmp);

   return OK;
}  // read_float()


int ReadDoubleArray( FILE*      infile,        // pointer to file
                      char       label[],        // marking label
                      unsigned   nCol,
                      double     *retMatrix)     // returned double val
{
   char   line[MAX_CONFLINE_SIZE];      // used to scan the file
   char   lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
   double tmp[MAX_LOAD_MATRIX_COL];          // value is read as float and put in tmp
   unsigned nIndex;
   unsigned nIndexCol;

   fseek(infile, 0, SEEK_SET);        // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
         printf("   ReadDoubleMatrix> read_double(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
         return ERROR;
      }
      sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.     //
   // Read the line and scan it for the value                         //
   for ( nIndex=0; nIndex<1; nIndex++ )
   {
      fgets(line, (MAX_CONFLINE_SIZE-1), infile);
      sscanf(line,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
         &tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4], &tmp[5], &tmp[6], &tmp[7], &tmp[8], &tmp[9],
         &tmp[10], &tmp[11], &tmp[12], &tmp[13], &tmp[14], &tmp[15], &tmp[16], &tmp[17], &tmp[18], &tmp[19],
         &tmp[20], &tmp[21], &tmp[22], &tmp[23], &tmp[24]);
   }

   //   printf("LOAD_MATRIX: \n");

      for ( nIndexCol=0; nIndexCol<nCol; nIndexCol++ )
      {
          retMatrix[nIndexCol] = tmp[nIndexCol];
	  //          printf(" %lf", retMatrix[nIndexCol]);
      }

      //      printf(" \n");
      return OK;
}  // read_double()


int ReadFloatArray( FILE*      infile,        // pointer to file
char       label[],        // marking label
unsigned   nCol,
float     *retMatrix)     // returned double val
{
char   line[MAX_CONFLINE_SIZE];      // used to scan the file
char   lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
float tmp[MAX_LOAD_MATRIX_COL];          // value is read as float and put in tmp
unsigned nIndex;
unsigned nIndexCol;

fseek(infile, 0, SEEK_SET);        // go to beginning of file

// read a line until the specified label is found at the beginning //
do
{
if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
{
printf("   ReadFloatMatrix> read_double(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
return ERROR;
}
sscanf(line,"%s", lineTmp);
}
while (strcmp(lineTmp,label) != 0);

// label has been found: next line contains the desired value.     //
// Read the line and scan it for the value                         //
for ( nIndex=0; nIndex<1; nIndex++ )
{
fgets(line, (MAX_CONFLINE_SIZE-1), infile);
sscanf(line,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
&tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4], &tmp[5], &tmp[6], &tmp[7], &tmp[8], &tmp[9],
&tmp[10], &tmp[11], &tmp[12], &tmp[13], &tmp[14], &tmp[15], &tmp[16], &tmp[17], &tmp[18], &tmp[19],
&tmp[20], &tmp[21], &tmp[22], &tmp[23], &tmp[24]);
}

//printf("LOAD_MATRIX: \n");

for ( nIndexCol=0; nIndexCol<nCol; nIndexCol++ )
{
retMatrix[nIndexCol] = tmp[nIndexCol];
//printf(" %f", retMatrix[nIndexCol]);
}

//printf(" \n");
return OK;
}  // read_float()


int ReadString( FILE*      infile,      // pointer to file
                char       label[],     // marking label
                char       retValue[])     // returned string
{
   char   line[MAX_CONFLINE_SIZE];      // used to scan the file
   char   lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value

   fseek(infile, 0, SEEK_SET);        // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
         printf("   ReadString> ReadString(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
         return ERROR;
      }
      sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.     //
   // Read the line and scan it for the value                         //
   fgets(line, (MAX_CONFLINE_SIZE-1), infile);

   sscanf(line,"%s", retValue);

   return OK;
}  // read_double()
/******************************************************************************/
/*
** Method: 	ReadDoubleMatrix()
**
** Description: read from a specified file a variable of type double marked
**              with the given label.
**
**              example
**                 if the file 'in.dat' looks like
**
**                 ...
**                 mylab
**                 33.45
**                 ...
**
**                 the following code:
**                    infile = fopen("in.dat","r");
**                    x = read_double(infile, "mylab");
**
**                 returns x=33.45
**
**    warnings: if label is present twice in the file,
**              the first occurrence is used
**
** Prototype:
**
*/
int readDblMatrix(    FILE*      infile,         // pointer to file
                      char       label[],        // marking label
                      int   nRow,
                      int   nCol,
                      double    returnMatrix[][MAX_LOAD_MATRIX_COL])     // returned double val
{
   char   line[MAX_CONFLINE_SIZE];      // used to scan the file
   char   lineTmp[MAX_CONFLINE_SIZE];   // and read the requested value
   double tmp[MAX_LOAD_MATRIX_ROW][MAX_LOAD_MATRIX_COL];          // value is read as double and put in tmp
   int nIndex, nIndexCol;

   fseek(infile, 0, SEEK_SET);        // go to beginning of file

   // read a line until the specified label is found at the beginning //
   do
   {
      if ( fgets(line, (MAX_CONFLINE_SIZE-1), infile) == NULL)
      {
         printf("   ReadDoubleMatrix> read_double(): ERROR reach EndOfFile can not find parameter >%s<\n", label);
         return ERROR;
      }
      sscanf(line,"%s", lineTmp);
   }
   while (strcmp(lineTmp,label) != 0);

   // label has been found: next line contains the desired value.     //
   // Read the line and scan it for the value                         //
   for ( nIndex=0; nIndex<nRow; nIndex++ )
   {
      fgets(line, (MAX_CONFLINE_SIZE-1), infile);
      sscanf(line,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &tmp[nIndex][0], &tmp[nIndex][1], &tmp[nIndex][2], &tmp[nIndex][3], &tmp[nIndex][4], &tmp[nIndex][5], &tmp[nIndex][6], &tmp[nIndex][7], &tmp[nIndex][8], &tmp[nIndex][9]);
   }

      //*retVal = (double)(tmp);
   //   printf(   "ReadDblMatrix: \n");
   //   printf(   "Loaded variable %s : \n",label);
   for ( nIndex=0; nIndex<nRow; nIndex++ )
   {
     //      printf("         %d: [", nIndex);
      for ( nIndexCol=0; nIndexCol<nCol; nIndexCol++ )
      {
    	    returnMatrix[nIndex][nIndexCol] = tmp[nIndex][nIndexCol];
	    //            printf(" %lf", tmp[nIndex][nIndexCol]);
      }
      //      printf(" ]\n");
   }

   return OK;
}  // ReadDblMatrix()


//******************************************************************************/
/*
** Method:  Interp2DMatrix()
**
** Description: interpolates to find f(argx;argy) where values of f() are tabulated in a table as follows
**
**ROW 0		N/A	y1			y2			...			yn
**ROW 1		x1	f(x1,y1)	f(x1,y2)	...			f(x1,yn)
**
**ROW N		xn	f(xn,y1)	f(xn,y2)	...			f(xn,yn)
**
*/
int Interp2DMatrix(double matrix[INTERP_MATRIX_MAX_SIZE+1][INTERP_MATRIX_MAX_SIZE+1], double argx, double argy, int nx, int ny, double* retVal )
{
   int i=0;
   int j=0;
   double newmatrix1[INTERP_MATRIX_MAX_SIZE][MAX_MATRIC_COL];
   double newmatrix2[INTERP_MATRIX_MAX_SIZE][MAX_MATRIC_COL];
   double newmatrix3[MAX_MATRIC_COL][MAX_MATRIC_COL];
   double x1;
   double x2;
   double x3;

   //Error checking
   if (nx>INTERP_MATRIX_MAX_SIZE)
      {
         printf("   Interp2DMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, nx);
         *retVal = -9999999.0;
         return ERROR;
      }
   if (ny>INTERP_MATRIX_MAX_SIZE)
      {
         printf("   Interp2DMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, ny);
         *retVal = -9999999.0;
         return ERROR;
      }


   j=1; // first column skipped as reteins x reference values
   // finds rightmost closest column and build first matrix
   while ( (argy > matrix[0][j]) && (j < ny-1) ) j++ ;
   newmatrix3[0][0]=matrix[0][j];
   while (i<nx) {
      newmatrix1[i][0]=matrix[i][0];
      newmatrix1[i][1]=matrix[i][j];
      i++;
   }
   j=ny-1;
   // finds leftmost closest column and build second matrix
   while ( (argy < matrix[0][j]) && (j > 1) ) j-- ;
   newmatrix3[1][0]=matrix[0][j];
   i=0;
   while (i<nx) {
      newmatrix2[i][0]=matrix[i][0];
      newmatrix2[i][1]=matrix[i][j];
      i++;
   }

   // interpolate first value
   if ( InterpMatrix( nx, newmatrix1, argx, 1, &x1 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   // interpolate second value
   newmatrix3[0][1]=x1;
   if ( InterpMatrix( nx, newmatrix2, argx, 1, &x2 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   newmatrix3[1][1]=x2;
   // interpolate and get result
   if ( InterpMatrix( 2, newmatrix3, argy, 1, &x3 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   *retVal = x3;
   return OK;
}
int Interp2DMatrix(float matrix[INTERP_MATRIX_MAX_SIZE+1][INTERP_MATRIX_MAX_SIZE+1], float argx, float argy, int nx, int ny, float* retVal )
{
   int i=0;
   int j=0;
   float newmatrix1[INTERP_MATRIX_MAX_SIZE][MAX_MATRIC_COL];
   float newmatrix2[INTERP_MATRIX_MAX_SIZE][MAX_MATRIC_COL];
   float newmatrix3[MAX_MATRIC_COL][MAX_MATRIC_COL];
   float x1;
   float x2;
   float x3;

   //Error checking
   if (nx>INTERP_MATRIX_MAX_SIZE)
      {
         printf("   Interp2DMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, nx);
         *retVal = -9999999.0;
         return ERROR;
      }
   if (ny>INTERP_MATRIX_MAX_SIZE)
      {
         printf("   Interp2DMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, ny);
         *retVal = -9999999.0;
         return ERROR;
      }


   j=1; // first column skipped as reteins x reference values
   // finds rightmost closest column and build first matrix
   while ( (argy > matrix[0][j]) && (j < ny-1) ) j++ ;
   newmatrix3[0][0]=matrix[0][j];
   while (i<nx) {
      newmatrix1[i][0]=matrix[i][0];
      newmatrix1[i][1]=matrix[i][j];
      i++;
   }
   j=ny-1;
   // finds leftmost closest column and build second matrix
   while ( (argy < matrix[0][j]) && (j > 1) ) j-- ;
   newmatrix3[1][0]=matrix[0][j];
   i=0;
   while (i<nx) {
      newmatrix2[i][0]=matrix[i][0];
      newmatrix2[i][1]=matrix[i][j];
      i++;
   }

   // interpolate first value
   if ( InterpMatrix( nx, newmatrix1, argx, 1, &x1 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   // interpolate second value
   newmatrix3[0][1]=x1;
   if ( InterpMatrix( nx, newmatrix2, argx, 1, &x2 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   newmatrix3[1][1]=x2;
   // interpolate and get result
   if ( InterpMatrix( 2, newmatrix3, argy, 1, &x3 )== ERROR ) {
      printf("   Interp2DMatrix() error");
      *retVal = -9999999.0;
      return ERROR;
   }
   *retVal = x3;
   return OK;
}
/******************************************************************************/
/*
** Method:  InterpMatrix()
**
** Description:
**
*/
int InterpMatrix(int nr, double (*matrixx)[2], double arg, int n, double* retVal )
{
   int    i;
   double x[INTERP_MATRIX_MAX_SIZE];
   double fx[INTERP_MATRIX_MAX_SIZE];

   if (nr>INTERP_MATRIX_MAX_SIZE)
   {
      printf("   InterpMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, nr);
      *retVal = -9999999.0;
      return ERROR;
   }

   for (i=0 ; i<nr ; i++)
   {
      x[i]=matrixx[i][0];
      fx[i]=matrixx[i][1];
   }

   *retVal = Interp(nr, x , fx , arg , n );
   return OK;
} //InterpMatrix()
int InterpMatrix(int nr, float (*matrixx)[2], float arg, int n, float* retVal )
{
   int    i;
   float x[INTERP_MATRIX_MAX_SIZE];
   float fx[INTERP_MATRIX_MAX_SIZE];

   if (nr>INTERP_MATRIX_MAX_SIZE)
   {
      printf("   InterpMatrix() matrix size out of range (max allowed=%d, size req=%d)\n", INTERP_MATRIX_MAX_SIZE, nr);
      *retVal = -9999999.0;
      return ERROR;
   }

   for (i=0 ; i<nr ; i++)
   {
      x[i]=matrixx[i][0];
      fx[i]=matrixx[i][1];
   }

   *retVal = Interp(nr, x , fx , arg , n );
   return OK;
} //InterpMatrix()
/******************************************************************************/
/*
** Method:  ProfileIndex()
**
** Description:
**
*/

int ProfileIndex(double arg, double *profilearray, int nDimOfArray)
{
   //find the index of the element in the range less than or equal to arg, profilearray is 1D array
   int  i = 0;

   while (profilearray[i] < arg)
   {
      if (i > nDimOfArray) return nDimOfArray;
      i++;
   }

   if (profilearray[i] == arg) return i;
   return (i - 1);
} //ProfileIndex()

int ProfileIndex(float arg, float *profilearray, int nDimOfArray)
{
   //find the index of the element in the range less than or equal to arg, profilearray is 1D array
   int  i = 0;

   while (profilearray[i] < arg)
   {
      if (i > nDimOfArray) return nDimOfArray;
      i++;
   }

   if (profilearray[i] == arg) return i;
   return (i - 1);
} //ProfileIndex()
/******************************************************************************/
/*
** Method:  InterpNoExtra()
**
** Description: Interpolates but without extrapolating, keeps extreme values
**
*/
/*
  Interpolation function by GiP, use at your own RISK !
   Nc is the array lenght
    x is the x array of numbers to be used -
    fx is the array corresponding values of f(x) -
   arg is the x argument
    The return is the value of f(arg)
   n is the order of interpolation 1 for Linear, 2 for second order
   */

double InterpNoExtra(int nc, double *x, double *fx, double arg, int n )
   {
      if (arg <= x[0]) return fx[0];
      if (arg >= x[nc-1]) return fx[nc-1];
      return Interp( nc, x, fx, arg, n );
   } //InterpNoExtra
/******************************************************************************/
/*
** Method:  Interp()
**
** Description:
**
*/
   /*
   Interpolation function by GiP, use at your own RISK !
   Nc is the array lenght
    x is the x array of numbers to be used -
    fx is the array corresponding values of f(x) -
   arg is the x argument
    The return is the value of f(arg)
   n is the order of interpolation 1 for Linear, 2 for second order
   */

   double Interp(int nc, double *x, double *fx, double arg, int n )
   {

      double xarg;
      int num ;
      double x1;
      double x2;
      double x3;
      double fx1;
      double fx2;
      double fx3;
      double term1;
      double term2;
      double term3;

      xarg = arg;

      if (xarg < x[0])
         num = 0;
      else if ( (xarg >= x[nc-1]) && (n == 1) )
         num = nc - 2; //nc is the total array length
      else if ( (xarg >= x[nc-1]) && (n == 2) )
         num = nc - 3;
      else
         num = ProfileIndex(arg,x,nc);

      //Num is the index of the element in the range less than or equal to arg

      if (n == 2 && nc < 3)
      { // array too short for 2 order interpolation, switch to 1st order
         n=1;
      }

      if (n == 1 && nc < 2)
      { // array too short for 1 order interpolation, give back the only array element
         return x[0];
      }

      xarg = arg;
      x1 = x[num];
      fx1 = fx[num];
      x2 = x[num + 1];
      fx2 = fx[num + 1];

      // Selected same value (may happen in automatic calculation of initial values)
      if ((fabs((x1 - x2))<1e-10 ) && (fabs((fx1 - fx2))<1e-10 ))
      {
    	  return fx1;
      }
      // The same x value has 2 corresponding f(x) : error it shall never happen
      else if ((fabs((x1 - x2))<1e-10 ) && (fabs((fx1 - fx2))>1e-10 ))
      {
    	  printf("   Utility.c> Error in function Interp: the same x value returns two f(x) \n");
    	  exit(-1);
      }
      // linear interpolation
      if (n == 1)
      {
         term1 = (xarg - x2) / (x1 - x2);
         term2 = (xarg - x1) / (x2 - x1);
         return (term1 * fx1 + term2 * fx2);
      }

   // second order with at least 4 elements in the array
      if ((n == 2)&&( nc >= num + 2 ))
      {
         x3 = x[num + 2];
         fx3 = fx[num + 2];
      }
      if ((n == 2)&&( nc < num + 2 ))
      {
         x1 = x[nc - 2];
         fx1 = fx[nc - 2];
         x2 = x[nc - 1];
         fx2 = fx[nc - 1];
         x3 = x[nc];
         fx3 = fx[nc];
      }

      term1 = (xarg - x2) * (xarg - x3) / ((x1 - x2) * (x1 - x3));
      term2 = (xarg - x1) * (xarg - x3) / ((x2 - x1) * (x2 - x3));
      term3 = (xarg - x1) * (xarg - x2) / ((x3 - x1) * (x3 - x2));
      return (term1 * fx1 + term2 * fx2 + term3 * fx3);

   } //interp
   float Interp(int nc, float *x, float *fx, float arg, int n )
      {

	   float xarg;
       int num ;
       float x1;
       float x2;
       float x3;
       float fx1;
       float fx2;
       float fx3;
       float term1;
       float term2;
       float term3;

         xarg = arg;

         if (xarg < x[0])
            num = 0;
         else if ( (xarg >= x[nc-1]) && (n == 1) )
            num = nc - 2; //nc is the total array length
         else if ( (xarg >= x[nc-1]) && (n == 2) )
            num = nc - 3;
         else
            num = ProfileIndex(arg,x,nc);

         //Num is the index of the element in the range less than or equal to arg

         if (n == 2 && nc < 3)
         { // array too short for 2 order interpolation, switch to 1st order
            n=1;
         }

         if (n == 1 && nc < 2)
         { // array too short for 1 order interpolation, give back the only array element
            return x[0];
         }

         xarg = arg;
         x1 = x[num];
         fx1 = fx[num];
         x2 = x[num + 1];
         fx2 = fx[num + 1];

         // Selected same value (may happen in automatic calculation of initial values)
         if ((fabs((x1 - x2))<1e-10 ) && (fabs((fx1 - fx2))<1e-10 ))
         {
       	  return fx1;
         }
         // The same x value has 2 corresponding f(x) : error it shall never happen
         else if ((fabs((x1 - x2))<1e-10 ) && (fabs((fx1 - fx2))>1e-10 ))
         {
       	  printf("   Utility.c> Error in function Interp: the same x value returns two f(x) \n");
       	  exit(-1);
         }
         // linear interpolation
         if (n == 1)
         {
            term1 = (xarg - x2) / (x1 - x2);
            term2 = (xarg - x1) / (x2 - x1);
            return (term1 * fx1 + term2 * fx2);
         }

      // second order with at least 4 elements in the array
         if ((n == 2)&&( nc >= num + 2 ))
         {
            x3 = x[num + 2];
            fx3 = fx[num + 2];
         }
         if ((n == 2)&&( nc < num + 2 ))
         {
            x1 = x[nc - 2];
            fx1 = fx[nc - 2];
            x2 = x[nc - 1];
            fx2 = fx[nc - 1];
            x3 = x[nc];
            fx3 = fx[nc];
         }

         term1 = (xarg - x2) * (xarg - x3) / ((x1 - x2) * (x1 - x3));
         term2 = (xarg - x1) * (xarg - x3) / ((x2 - x1) * (x2 - x3));
         term3 = (xarg - x1) * (xarg - x2) / ((x3 - x1) * (x3 - x2));
         return (term1 * fx1 + term2 * fx2 + term3 * fx3);

      } //interp

/******************************************************************************/
/*
** Method:  secondDegree()
**
** Description: solves second degree equations in the form
** a * x^2 + b * x + c = 0
**
*/

int secondDegree(double a , double b, double c, double *x1,double *x2)
{
   *x1 = ( - b + sqrt(b*b-4.0*a*c))/(2.0*a);
   *x2 = ( - b - sqrt(b*b-4.0*a*c))/(2.0*a);

   return OK;
} //secondDegree()

/******************************************************************************/
/*
** Method:  thirdDegree()
**
** Description: solves third degree equations in the form
** x^3 + a * x^2 + b * x + c = 0
**
*/

int thirdDegree(double a , double b, double c,complex <double> *x1, complex <double> *x2, complex <double> *x3)
{
   double p,q,discr,teta;
   complex <double> u;
   complex <double> v;
   complex <double> _complex_I (0,1);
   complex <double> y1,y2,y3;
   double const rad3mezzi = 0.8660254037844386;
   p = - a*a/3.0 + b;
   q = 2.0*a*a*a/27.0-a*b/3.0 + c;

   discr=q*q/4.0+p*p*p/27.0;

   if (discr>=0)
   {
      u = pow( ( (-q/2.0)+sqrt(q*q/4.0+p*p*p/27.0) ),0.333333333333333333);
      v = pow( ( (-q/2.0)-sqrt(q*q/4.0+p*p*p/27.0) ),0.333333333333333333);

      if (abs(abs(u*v) - (-p/3.0))>0.001)
      {
         v = -p/3.0/u;
      }

      y1 = u+v;
      y2 = -(u+v)/2.0 + _complex_I * (u-v)*rad3mezzi;
      y3 = -(u+v)/2.0 - _complex_I * (u-v)*rad3mezzi;
   }
   else
   {
      teta=atan(-2.0*sqrt(-discr)/q);
      y1 = 2.0*sqrt(-p/3.0)*cos(teta/3.0);
      y2 = 2.0*sqrt(-p/3.0)*cos((teta+2.0*M_PI)/3.0);
      y3 = 2.0*sqrt(-p/3.0)*cos((teta+4.0*M_PI)/3.0);
   }

   *x1 =  y1  - a/3.0;
   *x2 =  y2  - a/3.0;
   *x3 =  y3  - a/3.0;

   return OK;
} //thirdDegree()

/******************************************************************************/
/*
** Method:  fourthDegree()
**
** Description: solves fourth degree equations in the form
** x^4 + a * x^3 + b * x^2 + c * x + d = 0
**
*/
int fourthDegree(double a,double b,double c,double d, complex <double> *z1, complex <double> *z2, complex <double> *z3, complex <double> *z4)
{
   double alfa,beta,gamma;
   complex <double> p,q,r,u,y,w;

   alfa = b - 0.375*a*a;
   beta = a*a*a/8.0 - a*b/2.0 +c;
   gamma = -(0.01171875)*a*a*a*a + 0.0625*a*a*b - 0.25*a*c + d;

   p = -alfa*alfa/12.0 - gamma;
   q = -alfa*alfa*alfa/108.0 + alfa*gamma/3.0 - beta*beta/8;
   r = -q/2.0 + sqrt(q*q/4.0+p*p*p/27.0);

   u = pow(r,0.333333333333333333333333333333);

   if (abs(u)<1e-16)
   {
       y = -(0.8333333333333333333333333333333)*alfa - pow(q,0.33333333333333333333333333333);
   }
   else
   {
       y = -(0.8333333333333333333333333333333)*alfa + u -p/u/3.0;
   }

   w = sqrt(alfa +2.0*y);

   *z1 = ( + w + sqrt(-(3.0*alfa+2.0*y+2.0*beta/w)))/2.0 - a/4.0;
   *z2 = ( + w - sqrt(-(3.0*alfa+2.0*y+2.0*beta/w)))/2.0 - a/4.0;

   *z3 = ( - w + sqrt(-(3.0*alfa+2.0*y-2.0*beta/w)))/2.0 - a/4.0;
   *z4 = ( - w - sqrt(-(3.0*alfa+2.0*y-2.0*beta/w)))/2.0 - a/4.0;

   return OK;
} //fourthDegree()

/******************************************************************************/
/*
** Method:      CheckOutDValue()
**
** Description: Checks that double value does not
**              exceed min and max thresholds.
**
** Prototype:
**
*/

int CheckOutDValue( double value,double minValue,double maxValue)
{
   if( value < minValue )
   {
      printf("   PowerMdl> CheckOutDValue: ERROR load parameter= %lf (min allowed = %lf)\n", value,minValue);
      return ERROR;
   }

   if( value > maxValue )
   {
      printf("   PowerMdl> CheckOutDValue: ERROR load parameter=%lf (max allowed = %lf)\n", value,maxValue);
      return ERROR;
   }
   else
      return OK;
}

// ****************************************************************************************** //
// *************************    loggerClass LOGGER       ************************************ //
// ****************************************************************************************** //

loggerClass::loggerClass(char *FileName)
{
	*configFileName=*FileName;
	outfile.open(FileName, std::ios::out);

	sprintf( separator, "%s", ";");
	outputInt=1.0;
	dispHeader=true;
	dispFooter=true;

	if (!outfile) {
		std::cerr << " loggerClass failed to open outputfile : " << FileName << std::endl;
	}
}

loggerClass::~loggerClass()
{
	double elapsedTime,perform;
	int hh,mm,ddd,hhh;
	double ss,mmm;
	char szMsg[256];

	if (dispFooter)
	{

	elapsedTime=clock()/CLOCKS_PER_SEC;
	hh= (int) floor(elapsedTime/3600.0);
	mm= (int) floor((elapsedTime-hh*3600.0)/60.0);
	ss=elapsedTime-hh*3600.0-mm*60.0;

	ddd= (int) floor(elapsedTimeSeconds/86400.0);
	hhh= (int) floor((elapsedTimeSeconds-ddd*86400.0)/3600.0);
	mmm= (elapsedTimeSeconds - ddd*86400.0 - hhh*3600.0)/60.0;

	perform=elapsedTimeSeconds/elapsedTime;

	sprintf( szMsg, "\n  ******************************************************************************************************************  \n");
	outfile << szMsg ;
	sprintf( szMsg, "\n  SIMULATION ENDED CORRECTLY  --- Elapsed cpu time :          hh = %4d mm = %2d ss = %6.4lf \n",hh,mm,ss);
	outfile << szMsg ;
	sprintf( szMsg, "\n  SIMULATED TIME              --- Elapsed real time: dd = %4d hh =   %2d mm = %6.4lf \n",ddd,hhh,mmm);
	outfile << szMsg ;
	sprintf( szMsg, "\n  SIMULATION PERFORMANCE      --- %8.2lfx  --- faster than real time\n",perform);
	outfile << szMsg ;
	sprintf( szMsg, "\n  ******************************************************************************************************************  \n");
	outfile << szMsg ;

	}
	outfile.close();
}


void loggerClass::setSeparator(char* separatorChar)
{
	sprintf( separator, "%s", separatorChar);
}

void loggerClass::displayHeader(bool display)
{
	dispHeader=display;
}
void loggerClass::displayFooter(bool display)
{
	dispFooter=display;
}
void loggerClass::setOutputInterval(double outInt)
{
	outputInt=outInt;
}

int loggerClass::loggerHeader(double simStartJulianDate , double ls ,
        double roverInitialLatitude, double roverInitialLongitude)
{

	char szMsg[1024];

	firstJD = simStartJulianDate;

	if (dispHeader)
	{
		time(&startTime);
		sprintf( szMsg, "\n  SIMULATION RESULTS GENERATED ON  %s\n", ctime(&startTime));
		outfile << szMsg;
		sprintf( szMsg, "Starting JD =  %lf \t", simStartJulianDate);
		outfile << szMsg;
		sprintf( szMsg, "\t MJD =  %lf \n", simStartJulianDate-2400000.5);
		outfile << szMsg;
		sprintf( szMsg, "Starting ls =  %lf \n", ls);
		outfile << szMsg;
		sprintf( szMsg, "Starting Rover Position =  Latitude = %lf --- longitude = %lf \n\n", roverInitialLatitude,roverInitialLongitude);
		outfile << szMsg;
	}
	return OK;
}
void loggerClass::writeInitVars(void)
{
	char szMsg[1024];

	for (int i=0; i<variablesNumber ; i++)
	{
		if (i==0) sprintf( szMsg, "%s",logVariables[variableNames[i]].description);
		else sprintf( szMsg, " %s %s",separator,logVariables[variableNames[i]].description);
		outfile << szMsg;
	}
	outfile << std::endl ;
	for (int i=0; i<variablesNumber ; i++)
	{
		if (i==0) sprintf( szMsg, "%s",logVariables[variableNames[i]].measUnit);
//		else sprintf( szMsg, "%s %s %s", szMsg,separator,logVariables[variableNames[i]].measUnit);
		else sprintf( szMsg, " %s %s", separator,logVariables[variableNames[i]].measUnit);
		outfile << szMsg;
	}
	outfile << std::endl ;
	//outfile << szMsg << std::endl ;
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1)
{
	variablesNumber=2;
	variableNames[0]=v0;
	variableNames[1]=v1;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2)
{
	variablesNumber=3;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3)
{
	variablesNumber=4;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4)
{
	variablesNumber=5;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	variableNames[4]=v4;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5)
{
	variablesNumber=6;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	variableNames[4]=v4;
	variableNames[5]=v5;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6)
{
	variablesNumber=7;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	variableNames[4]=v4;
	variableNames[5]=v5;
	variableNames[6]=v6;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								 variableNamesEnum v7)
{
	variablesNumber=8;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	variableNames[4]=v4;
	variableNames[5]=v5;
	variableNames[6]=v6;
	variableNames[7]=v7;
	writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								 variableNamesEnum v7, variableNamesEnum v8)
{
	variablesNumber=9;
	variableNames[0]=v0;
	variableNames[1]=v1;
	variableNames[2]=v2;
	variableNames[3]=v3;
	variableNames[4]=v4;
	variableNames[5]=v5;
	variableNames[6]=v6;
	variableNames[7]=v7;
	variableNames[8]=v8;
	writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								 variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9)
{
variablesNumber=10;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10)
{
variablesNumber=11;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11)
{
variablesNumber=12;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12)
{
variablesNumber=13;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13)
{
variablesNumber=14;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14)
{
variablesNumber=15;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15)
{
variablesNumber=16;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16)
{
variablesNumber=17;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
writeInitVars();
}
void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17)
{
variablesNumber=18;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18)
{
variablesNumber=19;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19)
{
variablesNumber=20;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
variableNames[19]=v19;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20)
{
variablesNumber=21;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
variableNames[19]=v19;
variableNames[20]=v20;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
								variableNamesEnum v21)
{
variablesNumber=22;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
variableNames[19]=v19;
variableNames[20]=v20;
variableNames[21]=v21;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
								variableNamesEnum v21,variableNamesEnum v22)
{
variablesNumber=23;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
variableNames[19]=v19;
variableNames[20]=v20;
variableNames[21]=v21;
variableNames[22]=v22;
writeInitVars();
}

void loggerClass::loggerInitVars(variableNamesEnum v0, variableNamesEnum v1, variableNamesEnum v2, variableNamesEnum v3, variableNamesEnum v4, variableNamesEnum v5, variableNamesEnum v6,
								variableNamesEnum v7, variableNamesEnum v8, variableNamesEnum v9, variableNamesEnum v10, variableNamesEnum v11, variableNamesEnum v12, variableNamesEnum v13,
								variableNamesEnum v14, variableNamesEnum v15, variableNamesEnum v16, variableNamesEnum v17, variableNamesEnum v18, variableNamesEnum v19, variableNamesEnum v20,
								variableNamesEnum v21,variableNamesEnum v22,variableNamesEnum v23)
{
variablesNumber=24;
variableNames[0]=v0;
variableNames[1]=v1;
variableNames[2]=v2;
variableNames[3]=v3;
variableNames[4]=v4;
variableNames[5]=v5;
variableNames[6]=v6;
variableNames[7]=v7;
variableNames[8]=v8;
variableNames[9]=v9;
variableNames[10]=v10;
variableNames[11]=v11;
variableNames[12]=v12;
variableNames[13]=v13;
variableNames[14]=v14;
variableNames[15]=v15;
variableNames[16]=v16;
variableNames[17]=v17;
variableNames[18]=v18;
variableNames[19]=v19;
variableNames[20]=v20;
variableNames[21]=v21;
variableNames[22]=v22;
variableNames[23]=v23;
writeInitVars();
}

int loggerClass::writer(int numInputs, double elapSec)
{
	char szMsg[2048];
	char formatT[16];
	char numberT[64];

	elapsedTimeSeconds=elapSec;
	// only every outputInt intervals //
	if (fmod(elapSec,outputInt)!=0.0) return OK;

	if (variablesNumber!=numInputs)
	{
		outfile << "Number of inputs does not match number of variables declared in header definition" << std::endl;
		return ERROR;
	}

	for (int i=0; i<numInputs ; i++)
	{
		if (i==0)
		{
			sprintf(formatT, "%s%3.1f%s","% ",logVariables[variableNames[i]].dim,"lf");
			sprintf( szMsg, formatT, dblV[i]);
		}
		else
		{
			sprintf(formatT, "%s%3.1f%s","% ",logVariables[variableNames[i]].dim,"lf");
			sprintf(numberT, formatT,dblV[i]);
			//sprintf(formatB, "%s%s"," %s %s",formatT);
			sprintf( szMsg, "%s %s %s" , szMsg , separator , numberT);
		}
	}
	outfile << szMsg << std::endl;
	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1)
{
	const int numInputs = 2;
	dblV[0]=a0;
	dblV[1]=a1;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2)
{
	const int numInputs = 3;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3)
{
	const int numInputs = 4;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4)
{
	const int numInputs = 5;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5)
{
	const int numInputs = 6;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6)
{
	const int numInputs = 7;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7)
{
	const int numInputs = 8;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
	const int numInputs = 9;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9)
{
	const int numInputs = 10;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
						  double a10)
{
	const int numInputs = 11;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11)
{
	const int numInputs = 12;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12)
{
	const int numInputs = 13;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;

	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13)
{
	const int numInputs = 14;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12, double a13,double a14)
{
	const int numInputs = 15;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15)
{
	const int numInputs = 16;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16)
{
	const int numInputs = 17;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17)
{
	const int numInputs = 18;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}
int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18)
{
	const int numInputs = 19;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19)
{
	const int numInputs = 20;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	dblV[19]=a19;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20)
{
	const int numInputs = 21;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	dblV[19]=a19;
	dblV[20]=a20;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,double a21)
{
	const int numInputs = 22;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	dblV[19]=a19;
	dblV[20]=a20;
	dblV[21]=a21;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,double a21,double a22)
{
	const int numInputs = 23;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	dblV[19]=a19;
	dblV[20]=a20;
	dblV[21]=a21;
	dblV[22]=a22;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}

int loggerClass::loggerLog(double elapSec, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9,
		  double a10,double a11,double a12,double a13,double a14,double a15,double a16,double a17,double a18,double a19,double a20,double a21,double a22,
		  double a23)
{
	const int numInputs = 24;
	dblV[0]=a0;
	dblV[1]=a1;
	dblV[2]=a2;
	dblV[3]=a3;
	dblV[4]=a4;
	dblV[5]=a5;
	dblV[6]=a6;
	dblV[7]=a7;
	dblV[8]=a8;
	dblV[9]=a9;
	dblV[10]=a10;
	dblV[11]=a11;
	dblV[12]=a12;
	dblV[13]=a13;
	dblV[14]=a14;
	dblV[15]=a15;
	dblV[16]=a16;
	dblV[17]=a17;
	dblV[18]=a18;
	dblV[19]=a19;
	dblV[20]=a20;
	dblV[21]=a21;
	dblV[22]=a22;
	dblV[23]=a23;
	if (writer(numInputs, elapSec)!=OK) return ERROR;

	return OK;
}



void loggerClass::setLogVariablesList(logVariablesListType logList)
{
	logVariablesList=logList;
}

}
