cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

include(FetchContent)

if(NOT DEFINED FTXUI_REPO)
    set(FTXUI_REPO https://github.com/ArthurSonzogni/ftxui.git)
endif ()

FetchContent_Declare(
        ftxui
        EXCLUDE_FROM_ALL
        GIT_REPOSITORY ${FTXUI_REPO}
        GIT_TAG v5.0.0
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(ftxui)