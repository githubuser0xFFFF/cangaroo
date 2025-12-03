# CANBlaster Driver (cross-platform)
set(CANBLAST_SOURCES
    CANBlasterDriver.cpp
    CANBlasterInterface.cpp
)

set(CANBLAST_HEADERS
    CANBlasterDriver.h
    CANBlasterInterface.h
)

add_library(cangaroo_canblast_driver STATIC ${CANBLAST_SOURCES} ${CANBLAST_HEADERS})

target_include_directories(cangaroo_canblast_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(cangaroo_canblast_driver cangaroo_core cangaroo_driver Qt6::Core Qt6::Network)