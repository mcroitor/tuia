cmake_minimum_required(VERSION 3.10)
project(tuia)

set(CMAKE_INSTALL_PREFIX "build")
set(CMAKE_CXX_COMPILER g++)
set(CXX_STANDARD 20)

# add_compile_options(-std=c++20 -O3)
# enable support for multithreading, profiling and debugging 
add_compile_options(-pthread -pg -g -std=c++20 -O3)
add_link_options(-pthread -pg -g -O3)

set(SOURCES source/color.cpp
    source/background_color.cpp
    source/foreground_color.cpp
    source/image.cpp
    source/point.cpp
    source/text_image.cpp
    source/tuia.cpp)

add_library(tuia ${SOURCES})
include_directories(source)

# tests
add_executable(testcolor tests/testcolor.cpp)
target_link_libraries(testcolor tuia)

add_executable(testtuia tests/testtuia.cpp)
target_link_libraries(testtuia tuia)

## samples/draw.cpp
add_executable(draw samples/draw.cpp)
target_link_libraries(draw tuia)

## samples/draw_colors.cpp
add_executable(draw_colors samples/draw_colors.cpp)
target_link_libraries(draw_colors tuia)

## samples/screen.cpp
add_executable(screen samples/screen.cpp)
target_link_libraries(screen tuia)

## samples/change_screens.cpp
add_executable(change_screens samples/change_screens.cpp)
target_link_libraries(change_screens tuia)

## samples/moved_point.cpp
add_executable(moved_point samples/moved_point.cpp)
target_link_libraries(moved_point tuia)

## samples/ui.cpp
add_executable(ui samples/ui.cpp)
target_link_libraries(ui tuia)

## samples/text_image.cpp
add_executable(text_image samples/text_image.cpp)
target_link_libraries(text_image tuia)

## samples/ascii_painter.cpp
add_executable(ascii_painter samples/ascii_painter.cpp)
target_link_libraries(ascii_painter tuia)
