# Driver base library
set(DRIVER_SOURCES
    CanInterface.cpp
    CanListener.cpp
    CanDriver.cpp
    CanTiming.cpp
    GenericCanSetupPage.cpp
)

set(DRIVER_HEADERS
    CanInterface.h
    CanListener.h
    CanDriver.h
    CanTiming.h
    GenericCanSetupPage.h
)

set(DRIVER_FORMS
    GenericCanSetupPage.ui
)

add_library(cangaroo_driver STATIC ${DRIVER_SOURCES} ${DRIVER_HEADERS} ${DRIVER_FORMS})

# Make both the driver directory and src directory available
target_include_directories(cangaroo_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_driver cangaroo_core Qt6::Core Qt6::Widgets Qt6::SerialPort)

# Platform-specific drivers
if(WIN32)
    add_subdirectory(CandleApiDriver)
    add_subdirectory(AsclCANWinServiceDriver)
endif()

if(UNIX AND NOT APPLE)
    add_subdirectory(SocketCanDriver)
endif()

# Optional cross-platform drivers (currently disabled)
# add_subdirectory(CANBlastDriver)
# add_subdirectory(SLCANDriver)