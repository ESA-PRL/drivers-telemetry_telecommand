
#ifndef ORC_MACROS_H
#define ORC_MACROS_H

#ifdef PRINT1_DISPLAY
#define PRINT1( message ) \
std::cerr << message << std::endl;
#else
#define PRINT1( message ) 
#endif

#ifdef PRINT2_DISPLAY
#define PRINT2( message ) \
std::cerr << message << std::endl;
#else
#define PRINT2( message ) 
#endif

#ifdef PRINT3_DISPLAY
#define PRINT3( message ) \
std::cerr << message << std::endl;
#else
#define PRINT3( message ) 
#endif

#endif
