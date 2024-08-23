cmake_minimum_required(VERSION 3.16)
project(main)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

include(cmake/compilers.cmake)

if (DEFINED ENV{CMAKE_C_COMPILER} AND DEFINED ENV{CMAKE_CXX_COMPILER})
    message(STATUS "Setting C and C++ compiler from environment variables")
    set(CMAKE_C_COMPILER $ENV{CMAKE_C_COMPILER})
    set(CMAKE_CXX_COMPILER $ENV{CMAKE_CXX_COMPILER})
endif()

if (CMAKE_CXX_COMPILER AND CMAKE_C_COMPILER)
    message(STATUS "Using specifed C++ compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "Using specifed C compiler: ${CMAKE_C_COMPILER}")
else()
    message(STATUS "No C or C++ compiler specified, defaulting to Clang-17")
    FIND_AND_SET_CLANG17()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Ray installation directory
execute_process(
    COMMAND ray cpp --show-library-path
    OUTPUT_VARIABLE RAY_CPP_INFO
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX MATCH "Ray C\\+\\+ include path ([^\n]+)" _ ${RAY_CPP_INFO})
set(RAY_CPP_INCLUDE_DIR ${CMAKE_MATCH_1})

string(REGEX MATCH "Ray C\\+\\+ library path ([^\n]+)" _ ${RAY_CPP_INFO})
set(RAY_CPP_LIB_DIR ${CMAKE_MATCH_1})

message(STATUS "Ray C++ include directory: ${RAY_CPP_INCLUDE_DIR}")
message(STATUS "Ray C++ library directory: ${RAY_CPP_LIB_DIR}")
find_library(RAY_LIB ray_api PATHS ${RAY_CPP_LIB_DIR})

if(NOT RAY_LIB)
    message(FATAL_ERROR "Ray library not found. Make sure it's installed correctly.")
endif()

include_directories(src ${RAY_CPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_library(remote_functions SHARED src/remote_functions.cpp)
target_link_libraries(remote_functions PRIVATE ${RAY_LIB})

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${RAY_LIB} remote_functions)
