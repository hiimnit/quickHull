cmake_minimum_required(VERSION 3.6)
project(quickHull)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.cpp Point.h quickHull.cpp quickHull.h NormalFormLine.cpp NormalFormLine.h randomizePoints.cpp randomizePoints.h Edge.cpp Edge.h)
add_executable(quickHull ${SOURCE_FILES})