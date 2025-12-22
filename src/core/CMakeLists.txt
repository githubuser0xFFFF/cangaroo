# Core library
set(CORE_SOURCES
    Backend.cpp
    CanMessage.cpp
    CanTrace.cpp
    CanDbMessage.cpp
    CanDb.cpp
    CanDbNode.cpp
    CanDbSignal.cpp
    MeasurementSetup.cpp
    MeasurementNetwork.cpp
    MeasurementInterface.cpp
    LogModel.cpp
    ConfigurableWidget.cpp
    Log.cpp
    Settings.cpp
)

set(CORE_HEADERS
    portable_endian.h
    Backend.h
    CanMessage.h
    CanTrace.h
    CanDbMessage.h
    CanDb.h
    CanDbNode.h
    CanDbSignal.h
    MeasurementSetup.h
    MeasurementNetwork.h
    MeasurementInterface.h
    LogModel.h
    ConfigurableWidget.h
    Log.h
    Settings.h
)

add_library(cangaroo_core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

# Make both the core directory and src directory available
target_include_directories(cangaroo_core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(cangaroo_core Qt6::Core Qt6::Widgets Qt6::Xml)
