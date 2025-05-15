cmake_minimum_required(VERSION 3.30)
project(MonkeyTyperProject)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        11.1.4
)

FetchContent_MakeAvailable(fmt)

add_executable(MonkeyTyperProject
        main.cpp
        Background.cpp
        Background.h
        Logic.cpp
        Logic.h
        Preview.cpp
        Preview.h
        Resources.cpp
        Resources.h
        GameEnd.cpp
        GameEnd.h
        GameMenu.cpp
        GameMenu.h
        Instruction.cpp
        Instruction.h
        Panel.cpp
        Panel.h
        Scores.cpp
        Scores.h
        Shortcut.cpp
        Shortcut.h
        Typing.cpp
        Typing.h
        Word.cpp
        Word.h)

target_link_libraries(MonkeyTyperProject PRIVATE SFML::Graphics SFML::Audio fmt)
