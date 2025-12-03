# RawTxWindow module
set(RAW_TX_WINDOW_SOURCES
    RawTxWindow.cpp
)

set(RAW_TX_WINDOW_HEADERS
    RawTxWindow.h
)

set(RAW_TX_WINDOW_FORMS
    RawTxWindow.ui
)

add_library(cangaroo_raw_tx_window STATIC ${RAW_TX_WINDOW_SOURCES} ${RAW_TX_WINDOW_HEADERS} ${RAW_TX_WINDOW_FORMS})

target_include_directories(cangaroo_raw_tx_window PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_raw_tx_window cangaroo_core cangaroo_driver Qt6::Core Qt6::Widgets)