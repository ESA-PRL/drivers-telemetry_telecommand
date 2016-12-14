rock_library(telemetry_telecommand
    SOURCES comm.cpp tmgeneration.cpp simplethread.cpp rt.cpp param.cpp prr.cpp rt_ade.cpp  rt_mast.cpp rt_pancam.cpp rt_sa.cpp ActiveMQAdminClient.cpp ActiveMQClient.cpp ActiveMQMonitorClient.cpp ActiveMQFilesClient.cpp GeneralSupportLibrary.cpp
    HEADERS comm.h ctrl_state.h simplethread.h linuxOrcc.h rt.h param.h prr.h utils.h  RobotProcedure.h ActiveMQAdminClient.h ActiveMQClient.h ActiveMQMonitorClient.h ActiveMQFilesClient.h GeneralSupportLibrary.h)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories( 
  /usr/include/SDL/ 
  ./
  /usr/include/apr-1.0/ 
  /usr/local/include/activemq-cpp-3.9.3/
  ) 

TARGET_LINK_LIBRARIES(telemetry_telecommand
  SDL SDL_net activemq-cpp apr-1 ssl pthread dl
  )

rock_executable(telemetry_telecommand_bin main.cpp
    DEPS telemetry_telecommand)


