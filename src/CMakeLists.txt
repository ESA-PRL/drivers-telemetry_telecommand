rock_library(telemetry_telecommand
    SOURCES comm.cpp tmgeneration.cpp simplethread.cpp
    HEADERS comm.h ctrl_state.h simplethread.h linuxOrcc.h)

include_directories( 
  /usr/include/SDL/
  ./
  ) 

TARGET_LINK_LIBRARIES(telemetry_telecommand
  SDL SDL_net pthread dl  
  )

rock_executable(telemetry_telecommand_bin main.cpp
    DEPS telemetry_telecommand)


