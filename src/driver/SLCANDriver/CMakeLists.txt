# SLCAN Driver (cross-platform)
set(SLCAN_SOURCES
    SLCANInterface.cpp
    SLCANDriver.cpp
)

set(SLCAN_HEADERS
    SLCANInterface.h
    SLCANDriver.h
)

add_library(cangaroo_slcan_driver STATIC ${SLCAN_SOURCES} ${SLCAN_HEADERS})

target_include_directories(cangaroo_slcan_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(cangaroo_slcan_driver cangaroo_core cangaroo_driver Qt6::Core Qt6::SerialPort)