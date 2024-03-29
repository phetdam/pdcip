cmake_minimum_required(VERSION 3.16)

project(
    pdcip-cpp
    VERSION 0.1.0
    DESCRIPTION "C++ implementations of data structures and algorithms"
    HOMEPAGE_URL https://github.com/phetdam/pdcip
    LANGUAGES CXX
)

# update CMake module path. see ../tools/cmake for all relevant modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake")

# set default build type if not specified and set C++ project defaults
include(SetDefaultBuild)
include(SetCppDefaults)

# debug and release flags, handle MSVC case specifically
if(MSVC)
    add_compile_options(/Wall /wd5045 /wd4820)
    if(CMAKE_BUILD_TYPE STREQUAL Release)
        add_compile_options(/O2)
    else()
        add_compile_options(/Od /DEBUG)
    endif()
else()
    add_compile_options(-Wall -Wextra)
    if(CMAKE_BUILD_TYPE STREQUAL Release)
        add_compile_options(-O3)
    else()
        add_compile_options(-O0 -ggdb)
    endif()
endif()

include_directories(include)

add_subdirectory(src)

# build C++ tests using Google Test if minimum version of Google Test found
include(BuildGTestTests)
