rock_library(telemetry_telecommand
    SOURCES comm.cpp tmgeneration.cpp simplethread.cpp rt.cpp param.cpp prr.cpp rt_ade.cpp  rt_mast.cpp rt_pancam.cpp rt_sa.cpp ActiveMQAdmin.cpp  ActiveMQTCReceiver.cpp  ActiveMQTMSender.cpp GeneralSupportLibrary.cpp
    HEADERS comm.h ctrl_state.h simplethread.h linuxOrcc.h rt.h param.h prr.h utils.h  RobotProcedure.h ActiveMQAdmin.h ActiveMQTCReceiver.h ActiveMQTMSender.h GeneralSupportLibrary.h Messages.hpp
    DEPS_PKGCONFIG SDL_net activemq-cpp)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

rock_executable(telemetry_telecommand_bin main.cpp
    DEPS telemetry_telecommand)

