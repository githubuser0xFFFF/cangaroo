# CandleAPI Driver for Windows
set(CANDLEAPI_SOURCES
    CandleApiDriver.cpp
    CandleApiInterface.cpp
    CandleApiTiming.cpp
    api/candle.c
    api/candle_ctrl_req.c
)

set(CANDLEAPI_HEADERS
    CandleApiDriver.h
    CandleApiInterface.h
    CandleApiTiming.h
    api/candle.h
    api/candle_ctrl_req.h
    api/candle_defs.h
    api/ch_9.h
)

add_library(cangaroo_candle_driver STATIC ${CANDLEAPI_SOURCES} ${CANDLEAPI_HEADERS})

target_include_directories(cangaroo_candle_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(cangaroo_candle_driver 
    cangaroo_core
    cangaroo_driver
    Qt6::Core 
    SetupApi 
    Ole32 
    winusb
)