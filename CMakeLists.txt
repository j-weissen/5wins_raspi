cmake_minimum_required(VERSION 3.17)
project(5wins_raspi)

set(CMAKE_CXX_STANDARD 14)

add_executable(5wins_raspi main.cpp Game.cpp Field.cpp Cell.cpp)