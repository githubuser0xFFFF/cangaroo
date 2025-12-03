# TraceWindow module
set(TRACE_WINDOW_SOURCES
    TraceFilterModel.cpp
    LinearTraceViewModel.cpp
    AggregatedTraceViewModel.cpp
    BaseTraceViewModel.cpp
    AggregatedTraceViewItem.cpp
    TraceWindow.cpp
)

set(TRACE_WINDOW_HEADERS
    LinearTraceViewModel.h
    AggregatedTraceViewModel.h
    BaseTraceViewModel.h
    AggregatedTraceViewItem.h
    TraceFilterModel.h
    TraceWindow.h
    TraceViewTypes.h
)

set(TRACE_WINDOW_FORMS
    TraceWindow.ui
)

add_library(cangaroo_trace_window STATIC ${TRACE_WINDOW_SOURCES} ${TRACE_WINDOW_HEADERS} ${TRACE_WINDOW_FORMS})

target_include_directories(cangaroo_trace_window PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_trace_window cangaroo_core cangaroo_driver Qt6::Core Qt6::Widgets)