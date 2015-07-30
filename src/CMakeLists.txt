rock_library(data_handling
    SOURCES comm.cpp tmgeneration.cpp simplethread.cpp
    HEADERS comm.h ctrl_state.h simplethread.h linuxOrcc.h)

include_directories( 
  /usr/include/SDL/
  ./
  ) 

TARGET_LINK_LIBRARIES(data_handling
  SDL SDL_net pthread dl  
  )

rock_executable(data_handling_bin main.cpp
    DEPS data_handling)


