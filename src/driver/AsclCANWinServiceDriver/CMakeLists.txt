# ASCL CAN Windows Service Driver
set(ASCLCAN_SOURCES
    AsclCANWinServiceInterface.cpp
    AsclCANWinServiceDriver.cpp
    SocketWorker.cpp
)

set(ASCLCAN_HEADERS
    AsclCANWinServiceInterface.h
    AsclCANWinServiceDriver.h
    SocketWorker.h
    CANServiceDef.h
)

add_library(cangaroo_asclcan_driver STATIC ${ASCLCAN_SOURCES} ${ASCLCAN_HEADERS})

target_include_directories(cangaroo_asclcan_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(cangaroo_asclcan_driver cangaroo_core cangaroo_driver Qt6::Core Qt6::Network)