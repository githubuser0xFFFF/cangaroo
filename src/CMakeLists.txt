# Main cangaroo application
cmake_minimum_required(VERSION 3.16)

set(WIN_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/app.rc)

# Add subdirectories for all modules
add_subdirectory(core)
add_subdirectory(driver)
add_subdirectory(parser/dbc)
add_subdirectory(window/TraceWindow)
add_subdirectory(window/SetupDialog)
add_subdirectory(window/LogWindow)
add_subdirectory(window/CanStatusWindow)
add_subdirectory(window/RawTxWindow)

# Main application sources
set(CANGAROO_SOURCES
    main.cpp
    mainwindow.cpp
)

set(CANGAROO_HEADERS
    mainwindow.h
)

set(CANGAROO_FORMS
    mainwindow.ui
)

set(CANGAROO_RESOURCES
    cangaroo.qrc
)

# Create the main executable
if(WIN32)
    add_executable(cangaroo WIN32
        ${CANGAROO_SOURCES} 
        ${CANGAROO_HEADERS} 
        ${CANGAROO_FORMS}
        ${CANGAROO_RESOURCES}
        ${WIN_RESOURCES}
    )
else()
    add_executable(cangaroo 
        ${CANGAROO_SOURCES} 
        ${CANGAROO_HEADERS} 
        ${CANGAROO_FORMS}
        ${CANGAROO_RESOURCES}
    )
endif()

# Link Qt libraries first in correct order
target_link_libraries(cangaroo
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Xml
    Qt6::SerialPort
    Qt6::Network
)

# Then link all the application libraries
target_link_libraries(cangaroo
    cangaroo_core
    cangaroo_driver
    cangaroo_dbc_parser
    cangaroo_trace_window
    cangaroo_setup_dialog
    cangaroo_log_window
    cangaroo_can_status_window
    cangaroo_raw_tx_window
)

# Platform-specific driver libraries
if(WIN32)
    target_link_libraries(cangaroo
        cangaroo_candle_driver
        cangaroo_asclcan_driver
    )
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(cangaroo
        cangaroo_socketcan_driver
        ${LIBNL_LIBRARIES}
        ${LIBNL_ROUTE_LIBRARIES}
    )
    target_include_directories(cangaroo PRIVATE 
        ${LIBNL_INCLUDE_DIRS}
        ${LIBNL_ROUTE_INCLUDE_DIRS}
    )
endif()

# Include directories
target_include_directories(cangaroo PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Set output directory
set_target_properties(cangaroo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
