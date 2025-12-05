cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GetGitRevisionDescription)

get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_DESCRIBE "--tags")

if(NOT GIT_SHA1)
    set(GIT_SHA1 "unknown")
endif()

message(STATUS "Commit: ${GIT_SHA1}")
message(STATUS "Describe: ${GIT_DESCRIBE}")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/src/version.h
)

project(cangaroo
    VERSION 1.0.0
    DESCRIPTION "Open source CAN bus analyzer"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Xml SerialPort Network)

# Platform-specific settings
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBNL REQUIRED libnl-3.0)
    pkg_check_modules(LIBNL_ROUTE REQUIRED libnl-route-3.0)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set compiler flags
if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Prefer dynamic linking over static
set(BUILD_SHARED_LIBS OFF)  # Our own libraries are static
option(Qt6_USE_STATIC_LIBS "Use static Qt libraries" OFF)

# Add subdirectories
add_subdirectory(src)
