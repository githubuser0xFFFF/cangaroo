# DBC Parser module
set(DBC_PARSER_SOURCES
    DbcParser.cpp
    DbcTokens.cpp
)

set(DBC_PARSER_HEADERS
    DbcParser.h
    DbcTokens.h
)

add_library(cangaroo_dbc_parser STATIC ${DBC_PARSER_SOURCES} ${DBC_PARSER_HEADERS})

target_include_directories(cangaroo_dbc_parser PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(cangaroo_dbc_parser cangaroo_core Qt6::Core)