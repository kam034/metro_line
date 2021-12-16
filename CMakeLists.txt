cmake_minimum_required(VERSION 3.17)
project(metro_line)

set(CMAKE_CXX_STANDARD 20)

add_executable(metro_line main.cpp STATION/station.cpp STATION/station.h LINE/line.cpp LINE/line.h MENU/dialog.cpp MENU/dialog.h LIST/list.h)


add_subdirectory(Google_tests)