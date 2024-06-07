cmake_minimum_required(VERSION 3.6)
project(nypx07-fw VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

set(EMBASE_ARDUINO ON)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/emcppbase EXCLUDE_FROM_ALL)
include("${CMAKE_CURRENT_LIST_DIR}/lib/emcppbase/cmake/c-utils.cmake")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/u8g2 EXCLUDE_FROM_ALL)
target_include_directories(u8g2 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/u8g2/cppsrc)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(src PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/async.h/async)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/entrance)
