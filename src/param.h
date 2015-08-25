//*******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Inc/Exec/param.h
// Author   	  : Roger Pissard-Gibollet and Konstantin Kapellos 
// Version  	  : 3.0 beta
// Creation 	  : 18 May 1994 
//
//***************************** Description ***********************************
//
//  		 header for Orccad Exec Runtine 
//  		 of a Physical Ressource
//
// Class Definition: 
//    Parameters: manages parameters and symbolic table. 
//
// Errors:
//
//**************************** Modifications **********************************
//
// 6 November 1996  Integration in Orccad Exec
//
//*****************************************************************************
// (c) Copyright 1996, INRIA, all rights reserved
//*****************************************************************************
#ifndef ORC_PARAM_H
#define ORC_PARAM_H

#include		"utils.h"

class Parameters
{

public:

	Parameters (int size);
	virtual ~Parameters ();

	// Add a parameter on the table 
	// return ERROR or OK
	STATUS add (char* name, int type, int sizex, int sizey, char* value);

	// get pointeur on a parameter OK or ERROR
	// you must give its name, type and sizes and it returns the pointeur
	STATUS get (char* name, int type, int sizex, int sizey, char* value);

	// Change value of a parameter 
	STATUS set (char* name, int type, int sizex, int sizey, char* value);

	//void print ();
	
protected:
	PARAMETER* Table;	// Table of symbols 
	ORCSEM_ID SemTab;
	int number;
	int sizemax;

};

#endif
