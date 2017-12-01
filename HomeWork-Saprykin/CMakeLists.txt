cmake_minimum_required(VERSION 3.0.0)
project(HWAlgorithm VERSION 0.3.2)

include(CTest)
enable_testing()
set(homeWork_SOURCES main.cpp map.cpp AStar.cpp)
SET(CMAKE_C_COMPILER gcc) #define your compiler
SET(CMAKE_CXX_COMPILER g++) #define your compiler

add_executable(hw ${homeWork_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
