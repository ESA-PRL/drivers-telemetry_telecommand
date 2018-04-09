#include "prr.h"
#include "ctrl_state.h"
//#include "sys_state.h"  // TODO This should not be here, s/s parameters shall not be in sys_state 
//#include "power_lines.h"

//#include "PhR_Mast.h"

// reference to the global task
extern RobotProcedure *theRobotProcedure;

#define ACTION_MAST_IS_DEP_INITIALISE 1
#define ACTION_MAST_IS_PTU_INITIALISE 2

