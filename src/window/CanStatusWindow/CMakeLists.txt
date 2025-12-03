# CanStatusWindow module
set(CAN_STATUS_WINDOW_SOURCES
    CanStatusWindow.cpp
)

set(CAN_STATUS_WINDOW_HEADERS
    CanStatusWindow.h
)

set(CAN_STATUS_WINDOW_FORMS
    CanStatusWindow.ui
)

add_library(cangaroo_can_status_window STATIC ${CAN_STATUS_WINDOW_SOURCES} ${CAN_STATUS_WINDOW_HEADERS} ${CAN_STATUS_WINDOW_FORMS})

target_include_directories(cangaroo_can_status_window PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_can_status_window cangaroo_core Qt6::Core Qt6::Widgets)