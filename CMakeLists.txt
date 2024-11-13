cmake_minimum_required(VERSION 3.10)
project(tuia)

set(CMAKE_INSTALL_PREFIX "build")
set(CMAKE_CXX_COMPILER g++)
set(CXX_STANDARD 20)

# add_compile_options(-std=c++20 -O3)
add_compile_options(-pg -g -std=c++20 -O3)
add_link_options(-pg -g -O3)

set(SOURCES source/color.cpp
    source/image.cpp
    source/point.cpp
    source/terminal_color.cpp
    source/text_image.cpp
    source/tuia.cpp)

add_library(tuia ${SOURCES})
include_directories(source)

# tests
add_executable(testcolor tests/testcolor.cpp)
target_link_libraries(testcolor tuia)

add_executable(testtuia tests/testtuia.cpp)
target_link_libraries(testtuia tuia)

## tests/draw.cpp
add_executable(draw tests/draw.cpp)
target_link_libraries(draw tuia)

## tests/screen.cpp
add_executable(screen tests/screen.cpp)
target_link_libraries(screen tuia)

## tests/change_screens.cpp
add_executable(change_screens tests/change_screens.cpp)
target_link_libraries(change_screens tuia)

## tests/moved_point.cpp
add_executable(moved_point tests/moved_point.cpp)
target_link_libraries(moved_point tuia)

## tests/ui.cpp
add_executable(ui tests/ui.cpp)
target_link_libraries(ui tuia)

## tests/text_image.cpp
add_executable(text_image tests/text_image.cpp)
target_link_libraries(text_image tuia)
