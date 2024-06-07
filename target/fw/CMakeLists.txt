set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
cmake_minimum_required(VERSION 3.20)

set(SDK_ROOT ${CMAKE_CURRENT_LIST_DIR}/ch32v208-sdk)

set(BUILD_WITH_BLE 1)
set(BUILD_WITH_LWNS 0)
set(BUILD_WITH_NETLIB 0)

# 工具链设置
set(TOOLPATH "/home/r/sdk/MRS_Toolchain_Linux_x64_V1.80/RISC-V Embedded GCC/bin/riscv-none-embed-")

if (WIN32)
    MESSAGE(STATUS "Now is windows!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++.exe)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_AR ${TOOLPATH}ar.exe)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy.exe)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump.exe)
    set(SIZE ${TOOLPATH}size.exe)
elseif (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_AR ${TOOLPATH}ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump)
    set(SIZE ${TOOLPATH}size)
else ()
    MESSAGE(FATAL_ERROR "Unsupported system!")
endif ()

# 项目设置
project(nypx07-fw C CXX ASM)

# 编译参数 一般不用改
add_compile_options(-march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore)
add_compile_options(-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common)

# 链接参数
add_link_options(-T ${SDK_ROOT}/Ld/Link.ld)
add_link_options(-march=rv32imac -mabi=ilp32 -nostartfiles -Xlinker --gc-sections --specs=nano.specs --specs=nosys.specs)

# 编译等级
if (NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
FORCE)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_options(-O0 -g)
    add_definitions(-DDEBUG=1)
else()
    add_compile_options(-Os -g)
endif()

# 编译信息等级
add_compile_options(-Wall)

# 源码文件
file(GLOB_RECURSE SOURCES
    "${SDK_ROOT}/Core/core_riscv.c"
    "${SDK_ROOT}/Peripheral/src/*.c"
    "${SDK_ROOT}/Startup/startup_ch32v20x_D8W.S"
)

# 宏定义
add_definitions(-DCH32V20x_D8W=1)

# bsp库
add_library(bsp
    debug.cpp
    broadcaster.c
    devinfoservice.c
    main.cpp
    system_ch32v20x.c
    MainGui-fw.cpp
    embase-port.cpp

    epaper/epaper.cpp

    drv_trf796x.cpp
    trf/iso15693.cpp
    trf/trf796x.cpp
    trf/spi.cpp

    ${SOURCES}
)

# 头文件路径
target_include_directories(bsp PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${SDK_ROOT}/Core
    ${SDK_ROOT}/Debug
    ${SDK_ROOT}/Peripheral/inc
)

# 一些需要在最后被链接的文件
set(
    TOP_SOURCES
    ${TOP_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/ch32v20x_it.c
)

# bsp
set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)
add_subdirectory(${PROJECT_ROOT} ${CMAKE_BINARY_DIR}/project-root)
target_link_libraries(bsp src embase::arduino)

# 使用BLE
target_include_directories(bsp PUBLIC
    ${SDK_ROOT}/BLE_LIB
    ${SDK_ROOT}/HAL/include
)
if(BUILD_WITH_BLE)
    file(GLOB_RECURSE HAL_SOURCES
        "${SDK_ROOT}/HAL/*.c"
    )
    target_sources(bsp PUBLIC ${HAL_SOURCES})
    target_link_libraries(bsp ${SDK_ROOT}/BLE_LIB/libwchble.a)
    target_compile_definitions(bsp PUBLIC -DCLK_OSC32K=0 -DBLE_MAC=1) # 无外部32K晶振
endif()

# 使用LWNS
if(BUILD_WITH_LWNS)
    target_include_directories(bsp PUBLIC ${SDK_ROOT}/LWNS)
    target_link_libraries(bsp ${SDK_ROOT}/LWNS/LIBWCHLWNS.a)
endif()

# 使用NETLIB
if(BUILD_WITH_NETLIB)
    target_include_directories(bsp PUBLIC ${SDK_ROOT}/NetLib)
    target_sources(bsp
                    PUBLIC
                        "${SDK_ROOT}/NetLib/eth_driver.c"
                    )
    target_link_libraries(bsp ${SDK_ROOT}/NetLib/libwchnet.a)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hwtest)
