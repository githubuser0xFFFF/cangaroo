# SocketCAN Driver for Linux
set(SOCKETCAN_SOURCES
    SocketCanInterface.cpp
    SocketCanDriver.cpp
)

set(SOCKETCAN_HEADERS
    SocketCanInterface.h
    SocketCanDriver.h
)

add_library(cangaroo_socketcan_driver STATIC ${SOCKETCAN_SOURCES} ${SOCKETCAN_HEADERS})

target_include_directories(cangaroo_socketcan_driver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${LIBNL_INCLUDE_DIRS}
    ${LIBNL_ROUTE_INCLUDE_DIRS}
)
target_link_libraries(cangaroo_socketcan_driver 
    cangaroo_core
    cangaroo_driver
    Qt6::Core
    ${LIBNL_LIBRARIES}
    ${LIBNL_ROUTE_LIBRARIES}
)