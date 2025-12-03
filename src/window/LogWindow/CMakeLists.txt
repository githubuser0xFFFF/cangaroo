# LogWindow module
set(LOG_WINDOW_SOURCES
    LogWindow.cpp
)

set(LOG_WINDOW_HEADERS
    LogWindow.h
)

set(LOG_WINDOW_FORMS
    LogWindow.ui
)

add_library(cangaroo_log_window STATIC ${LOG_WINDOW_SOURCES} ${LOG_WINDOW_HEADERS} ${LOG_WINDOW_FORMS})

target_include_directories(cangaroo_log_window PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_log_window cangaroo_core Qt6::Core Qt6::Widgets)