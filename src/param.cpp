//*******************************  Orccad *************************************
//
// File 		  : $ORCCAD_SRC/Src/Exec/param.C
// Author   	  : Roger Pissard-Gibollet and Konstantin Kapellos 
// Version  	  : 3.0 beta
// Creation 	  : 18 May 1994 
//
//***************************** Description ***********************************
//
//  		 Implementation for Orccad Exec Runtine 
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
#include "param.h"

Parameters::Parameters (int size)
{

	number = 0;
	SemTab = orcSemCreate( ORCFULL );

	if ( size > MAXPARAM )
		sizemax = MAXPARAM;
	else
		sizemax = size;

	Table = new PARAMETER[ sizemax ];

}

Parameters::~Parameters ()
{

	orcSemDelete( SemTab );

	if ( Table != NULL )
	{
		delete Table;
		Table = NULL;
	}

}

STATUS Parameters::add (char* name, int type, int sizex, int sizey, char* value)
{

  int index;
  
  if ( number == sizemax )
    return( ERROR );
  
  // If the parameters are correct ?
  if ( ( strlen( name ) > MAXCHARNAME ) || ( sizex < 0 ) || ( sizey < 0 ) || ( ( sizex == 0 ) && ( sizey > 0 ) ) )
    return( ERROR );
  
  if ( ( type != INTEGER ) && ( type != DOUBLE ) )
    return( ERROR );
  
  // If the symbol is in the table ?
  for ( index = 0; index < number; index++ )
    {
      if ( strcmp( name, Table[ index ].name ) == 0 )
	return( ERROR );
    }
  
  // if not Add it
  // Table multiple access protection
  orcSemTake( SemTab, ORCFOREVER );
  
  strcpy( Table[ index ].name, name );
  Table[ index ].type = type;
  Table[ index ].sizex = sizex;
  Table[ index ].sizey = sizey;
  
  // Compute the dimension type
  if ( ( sizex == 0 ) && ( sizey == 0 ) )
    Table[ index ].dimtype = SCALAR;
  else if ( ( sizex != 0 ) && ( sizey == 0 ) )
    Table[ index ].dimtype = VECTOR;
  else
    Table[ index ].dimtype = MATRIX;
  
  // VALUE
  Table[ index ].p = value;		// table points to variable
  number++;
  orcSemGive( SemTab );
  
  return( OK );
} 

STATUS Parameters::get (char* name, int type, int sizex, int sizey, char* value)
{
  int index, found, index1, index2, ligne, ligne1, addlig;
  
  // If the parameters are correct ?
  if ( ( strlen( name ) > MAXCHARNAME ) || ( sizex < 0 ) || ( sizey < 0 ) || ( ( sizex == 0 ) && ( sizey > 0 ) ) )
    return( ERROR );
  if ( ( type != INTEGER ) && ( type != DOUBLE ) )
    return( ERROR );
  
  // If the symbol is in the table ?
  found = FALSE;
  
  // Table multiple access protection
  orcSemTake( SemTab, ORCFOREVER );
  
  for ( index = 0; ( ( index < number ) && ( !found ) ); index++ )
    {
      if ( strcmp( name, Table[ index ].name ) == 0 )
	{
	  // the symbol is found
	  // then  verify type an size search
	  if ( ( Table[ index ].type != type ) ||
	       ( Table[ index ].sizex != sizex ) ||
	       ( Table[ index ].sizey != sizey ) ) {
	    return( ERROR );
	  }
	  // If all it is ok then you could Return the value
	  
	  switch ( Table[ index ].type )
	    {
	    case INTEGER:
	      switch ( Table[ index ].dimtype )
		{
		case SCALAR:
		  *( ( int * ) value ) = *( ( int * ) Table[ index ].p );
		  break;
		case VECTOR:
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      ( ( int * ) value )[ index1 ] = ( ( int * ) Table[ index ].p )[ index1 ];
		    }
		  break;
		case MATRIX:
		  /*
		  ligne = ( int ) ( Table[ index ].p );
		  ligne1 = ( int ) ( value );
		  addlig = sizeof( int ) * Table[ index ].sizey;
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      for ( index2 = 0; index2 < Table[ index ].sizey; index2++ )
			{
			  ( ( int * ) ligne1 )[ index2 ] = ( ( int * ) ligne )[ index2 ];
			}
		      ligne += addlig;ligne1 += addlig;
		    }*/
		  break;
		}
		  
	      break;
	    case DOUBLE:
	      switch ( Table[ index ].dimtype )
		{
		case SCALAR:
		  *( ( double * ) value ) = *( ( double * ) Table[ index ].p );
		  break;
		case VECTOR:
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      ( ( double * ) value )[ index1 ] = ( ( double * ) Table[ index ].p )[ index1 ];
		    }
		  break;
		case MATRIX:
		  std::cout << "param.cpp MATRIX type in comment" << std::endl;
		  /*
		  ligne = ( int ) ( Table[ index ].p );
		  ligne1 = ( int ) ( value );
		  addlig = sizeof( double ) * Table[ index ].sizey;
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      for ( index2 = 0; index2 < Table[ index ].sizey; index2++ )
			{
			  ( ( double * ) ligne1 )[ index2 ] = ( ( double * ) ligne )[ index2 ];
			}
		      ligne += addlig;ligne1 += addlig;
		    }
		  */
		  break;
		}
	    } 
	  
	  // interrupt the search
	  found = TRUE;
	}
      
    }
  orcSemGive( SemTab );
  
  if ( found )
    return( OK );
  else
    return( ERROR );
  
}

STATUS Parameters::set (char* name, int type, int sizex, int sizey, char* value)
{ 
  int index, found, index1, index2, ligne, ligne1, addlig;
  
  // If the parameters are correct ?
  if ( ( strlen( name ) > MAXCHARNAME ) || ( sizex < 0 ) || ( sizey < 0 ) || ( ( sizex == 0 ) && ( sizey > 0 ) ) )
    return( ERROR );
  if ( ( type != INTEGER ) && ( type != DOUBLE ) )
    return( ERROR );
  
  // If the symbol is in the table ?
  found = FALSE;
  
  // Table multiple access protection
  orcSemTake( SemTab, ORCFOREVER );
  
  for ( index = 0; ( ( index < number ) && ( !found ) ); index++ )
    {
      if ( strcmp( name, Table[ index ].name ) == 0 )
	{
	  // the symbol is found
	  // then  verify type an size search
	  if ( ( Table[ index ].type != type ) ||
	       ( Table[ index ].sizex != sizex ) ||
	       ( Table[ index ].sizey != sizey ) )
	    return( ERROR );
	  
	  //ALL is OK the VALUE could be set
	  switch ( Table[ index ].type )
	    {
	    case INTEGER:
	      switch ( Table[ index ].dimtype )
		{
		case SCALAR:
		  *( ( int * ) Table[ index ].p ) = *( ( int * ) value ) ;
		  break;
		case VECTOR:
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      ( ( int * ) Table[ index ].p )[ index1 ] = ( ( int * ) value )[ index1 ];
		    }
		  break;
		case MATRIX:
		  /*
		  ligne = ( int ) ( Table[ index ].p );
		  ligne1 = ( int ) ( value );
		  addlig = sizeof( int ) * Table[ index ].sizey;
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      for ( index2 = 0; index2 < Table[ index ].sizey; index2++ )
			{
			  ( ( int * ) ligne )[ index2 ] = ( ( int * ) ligne1 )[ index2 ] ;
			}
		      ligne += addlig;ligne1 += addlig;
		    }
		  */
		  break;
		}
	      break;
	    case DOUBLE:
	      switch ( Table[ index ].dimtype )
		{
		case SCALAR:
		  *( ( double * ) Table[ index ].p ) = *( ( double * ) value );
		  break;
		case VECTOR:
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      ( ( double * ) Table[ index ].p )[ index1 ] = ( ( double * ) value )[ index1 ];
		    }
		  break;
		case MATRIX:
		  /*
		  ligne = ( int ) ( Table[ index ].p );
		  ligne1 = ( int ) ( value );
		  addlig = sizeof( double ) * Table[ index ].sizey;
		  for ( index1 = 0; index1 < Table[ index ].sizex; index1++ )
		    {
		      for ( index2 = 0; index2 < Table[ index ].sizey; index2++ )
			{
			  ( ( double * ) ligne )[ index2 ] = ( ( double * ) ligne1 )[ index2 ];
			}
		      ligne += addlig;ligne1 += addlig;
		    }
		  */
		  break;
		}
	    } 
	  // interrupt the search
	  found = TRUE;
	}
    }
  orcSemGive( SemTab );
  
  if ( found )
    return( OK );
  else
    return( ERROR ); 
}

