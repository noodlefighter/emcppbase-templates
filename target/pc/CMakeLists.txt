cmake_minimum_required(VERSION 3.20)
project(nypx-07-pc)

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)

add_library(
    bsp

    main.cpp
    u8x8_d_sdl_256x128.c
    u8x8_sdl_key.c
    MainGui-pc.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
target_include_directories(bsp PUBLIC ${SDL2_INCLUDE_DIRS})

add_subdirectory(${PROJECT_ROOT} ${CMAKE_BINARY_DIR}/project-root)

target_link_libraries(bsp ${SDL2_LIBRARIES} src)

# PC上运行的单元测试
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_BINARY_DIR}/test)
