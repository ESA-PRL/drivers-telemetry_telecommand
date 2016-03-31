rock_library(telemetry_telecommand
    SOURCES comm.cpp tmgeneration.cpp simplethread.cpp rt.cpp param.cpp prr.cpp rt_ade.cpp rt_mast.cpp rt_pancam.cpp rt_sa.cpp
    HEADERS comm.h ctrl_state.h simplethread.h linuxOrcc.h rt.h param.h prr.h utils.h RobotProcedure.h)

include_directories( 
  /usr/include/SDL/
  ./
  ) 

TARGET_LINK_LIBRARIES(telemetry_telecommand
  SDL SDL_net pthread dl  
  )

rock_executable(telemetry_telecommand_bin main.cpp
    DEPS telemetry_telecommand)


