cmake_minimum_required(VERSION 3.16)

project(yt-dlp-qt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(yt-dlp-qt
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
)

target_link_libraries(yt-dlp-qt PRIVATE
    Qt6::Core
    Qt6::Widgets
)