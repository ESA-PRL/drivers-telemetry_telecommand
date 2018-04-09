rock_library(telemetry_telecommand

    SOURCES
    comm.cpp
    tmgeneration.cpp
    simplethread.cpp
    rt.cpp
    param.cpp
    prr.cpp
    rt_ade.cpp
    rt_mast.cpp
    rt_pancam.cpp
    rt_sa.cpp
    ActiveMQAdmin.cpp
    ActiveMQTCReceiver.cpp
    ActiveMQTMSender.cpp
    GeneralSupportLibrary.cpp
    rapdgrammar_tab.c
    tasklib.cpp
    lex.yy.c
    interface.cpp
    aa.c
    module_MAST_DEP_Deploy.cpp
    module_MAST_DEP_Initialise.cpp
    module_MAST_PAN_Initialise.cpp
    module_MAST_TILT_Initialise.cpp
    module_MAST_DEP_MoveTo.cpp
    module_MAST_PAN_MoveTo.cpp
    module_MAST_TILT_MoveTo.cpp
    module_MAST_DEP_SwitchOff.cpp
    module_MAST_PAN_SwitchOff.cpp
    module_MAST_TILT_SwitchOff.cpp
    module_MAST_PTU_MoveTo.cpp

    HEADERS
    comm.h
    ctrl_state.h
    simplethread.h
    linuxOrcc.h
    rt.h
    param.h
    prr.h
    utils.h
    RobotProcedure.h
    ActiveMQAdmin.h
    ActiveMQTCReceiver.h
    ActiveMQTMSender.h
    GeneralSupportLibrary.h
    Messages.hpp
    rapdGrammar_tab.h
    tasklib.h
    aa.h
    module_MAST_DEP_Deploy.h
    module_MAST_DEP_Deploy_Inc.h
    module_MAST_DEP_Initialise.h
    module_MAST_DEP_Initialise_Inc.h
    module_MAST_PAN_Initialise.h
    module_MAST_PAN_Initialise_Inc.h
    module_MAST_TILT_Initialise.h
    module_MAST_TILT_Initialise_Inc.h
    module_MAST_DEP_MoveTo.h
    module_MAST_DEP_MoveTo_Inc.h
    module_MAST_PAN_MoveTo.h
    module_MAST_PAN_MoveTo_Inc.h
    module_MAST_TILT_MoveTo.h
    module_MAST_TILT_MoveTo_Inc.h
    module_MAST_DEP_SwitchOff.h
    module_MAST_DEP_SwitchOff_Inc.h
    module_MAST_PAN_SwitchOff.h
    module_MAST_PAN_SwitchOff_Inc.h
    module_MAST_TILT_SwitchOff.h
    module_MAST_TILT_SwitchOff_Inc.h
    module_MAST_PTU_MoveTo.h
    module_MAST_PTU_MoveTo_Inc.h

    DEPS_PKGCONFIG
    SDL_net activemq-cpp)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

rock_executable(telemetry_telecommand_bin main.cpp
    DEPS telemetry_telecommand)
