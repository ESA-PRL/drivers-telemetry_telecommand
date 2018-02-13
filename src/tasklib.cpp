
#include "tasklib.h"

extern "C" { 
  int activityPlanExec(const char *); 
}
TaskLib::TaskLib (std::string name) {	 

  Name = name;
  libHandler = NULL;

  State = 0;

}

TaskLib::~TaskLib () {	

}
std::string TaskLib::GetName() {
  return Name;
}
int TaskLib::loadTaskLib() {
  char *error;
  //
  // open the task library
  // 
  std::string libdirname("/home/kk/ROSEX2/ExoMarsOperations/RoverCtrl/bin/RoverCtrl/lib");
  std::string libname = libdirname + Name + ".so";
  
  libHandler = dlopen(libname.c_str(), RTLD_LAZY);
  if (!libHandler) {
    error = dlerror();
    fprintf(stderr, "Error on loading ./lib%s.so: %s\n", Name.c_str(), error);
    Status = ERROR;
    return ERROR;
  }
  else {
    fprintf(stderr, "Task library ./lib%s.so loaded\n", Name.c_str());
  }
  return OK;
}
FUNCPTR TaskLib::getFunction(const char* funcname) {
  char *error;
  // check if we have a valid handler
  if (libHandler == NULL) {
    fprintf(stderr, "Library '%s' is not loaded\n", Name.c_str());
    return NULL;
  }

  // reset the error
  dlerror();
  FUNCPTR func = (FUNCPTR) dlsym(libHandler, funcname);
  const char *dlym_error1 = dlerror();
  if (dlym_error1) {
    error = dlerror();
    fprintf(stderr, "Function: '%s' not loaded from library '%s'\n", funcname, Name.c_str());
    func = NULL;
  }
  else {
    fprintf(stderr, "Function '%s' loaded from library '%s'\n", funcname, Name.c_str());
  }
  return func; 
}
int TaskLib::callFunction(const char* funcname) {
  FUNCPTR func = getFunction(funcname);
  if (func == NULL) {
    return ERROR;
  }
  func(); 
  fprintf(stderr, "Function '%s' called from the library '%s'\n", funcname, Name.c_str()); 
  
  return OK;
}

int TaskLib::getState() {
  
  return State;
}

int TaskLib::insertSol (std::string sol)
{
	solFiles.push_back( sol); 

	return 1;

}

int TaskLib::ExecuteActivityPlan() {
  // create the thread that manages the Activity Plan
  if (createThread() == ERROR) {
    return ERROR;
  }

  return OK;

}
void* TaskLib::thread()
{
  std::list<std::string>::iterator pr; 
  for ( pr = solFiles.begin(); pr != solFiles.end(); pr++ ) {
    std::cerr << "Executing: " << (*pr).c_str() << std::endl;
    
    if (activityPlanExec((*pr).c_str()) == 0) {
      
    }
  }
  State = 0;
}

