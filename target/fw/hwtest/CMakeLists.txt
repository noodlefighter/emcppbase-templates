add_executable(hwtest-eink hwtest-eink.cpp ${TOP_SOURCES})
target_link_libraries(hwtest-eink bsp)

add_executable(hwtest-ble hwtest-ble.cpp ${TOP_SOURCES})
target_link_libraries(hwtest-ble bsp)

add_executable(hwtest-led hwtest-led.cpp ${TOP_SOURCES})
target_link_libraries(hwtest-led bsp)
