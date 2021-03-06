#include "prr.h"
#include "rt.h"

RobotProcedure::RobotProcedure (std::string name)
{
	Status = ERROR; 

	Name = name;

	GlobState = new Parameters(MAXPARAM);

    Clock = new MyClock();
    
	for (int i =0; i<MAX_STATE_SIZE; i++) {
	  State[i] = 0.0;
	  ADEState[i] = 0.0;
	  SAState[i] = 0.0;
	  MastState[i] = 0.0;
	  PanCamState[i] = 0.0;
	  GNCState[i] = 0.0;
	  TTCState[i] = 0.0;
	  DHSState[i] = 0.0;
	  LOCOMState[i] = 0.0;	  
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "State", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) State ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "AdeState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) ADEState ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "SolarArrayState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) SAState ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "MastState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) MastState ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "PanCamState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) PanCamState ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "LOCOMState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) LOCOMState ) == ERROR ) {
	  std::cout << "Error in OrcProcVimanco::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}
	//
	// add the default global state 
	// 
	if ( GetParameters()->add( "GNCState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) GNCState ) == ERROR ) {
	  std::cout << "Error in Prr::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR;
	}

	if ( GetParameters()->add( "CommsState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) TTCState ) == ERROR ) {
	  std::cerr << "Error in OrcProcXXX::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR; 
	}
	if ( GetParameters()->add( "DhsState", DOUBLE, MAX_STATE_SIZE, 0, ( char * ) DHSState ) == ERROR ) {
	  std::cerr << "Error in OrcProcXXX::Init() GetParameters()->add() failed" << std::endl;
	  Status = ERROR; 
	}

	Status = OK;

}

RobotProcedure::~RobotProcedure ()
{
}

int RobotProcedure::insertRT (RobotTask* RT)
{

	RobotTasks.push_back( RT ); 

	return 1;

}
std::list<RobotTask*> RobotProcedure::GetRobotTasks () {
  return RobotTasks;
}
RobotTask* RobotProcedure::GetRTFromName (char* name)
{

  std::list<RobotTask*>::iterator pr; 
  
  for ( pr = RobotTasks.begin(); pr != RobotTasks.end(); pr++ )
    {
      if ( !strcmp( (*pr)->GetName().c_str(), name ) ) 
	return (*pr);
    }
  return NULL;
  
}
char* RobotProcedure::GetName ()
{

	return (char*) Name.c_str();

}


Parameters* RobotProcedure::GetParameters ()
{

	return GlobState;

}


