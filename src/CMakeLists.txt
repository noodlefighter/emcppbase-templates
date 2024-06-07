configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/main_config.h.in
    ${CMAKE_CURRENT_LIST_DIR}/main_config.h
)

add_library(
    src
    MainGui.cpp
    Application.cpp
    WatchdogTask.cpp
)
target_include_directories(src PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(src PUBLIC u8g2 embase-core bsp)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ui)
