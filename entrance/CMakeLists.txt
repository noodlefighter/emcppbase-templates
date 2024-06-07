add_executable(app app.cpp ${TOP_SOURCES})
target_link_libraries(app src)
generate_fw_files(app)

add_executable(app2 app2.cpp ${TOP_SOURCES})
target_link_libraries(app2 src)
