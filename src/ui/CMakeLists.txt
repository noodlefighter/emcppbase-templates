target_sources(src PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/HomeForm.cpp

    ${CMAKE_CURRENT_LIST_DIR}/u8ui/U8Ui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/u8ui/U8UiForm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/u8ui/U8UiLabel.cpp

    ${CMAKE_CURRENT_LIST_DIR}/res/ui_res.c

)
target_include_directories(src PUBLIC ${CMAKE_CURRENT_LIST_DIR})
