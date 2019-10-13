cmake_minimum_required(VERSION 3.14.5)

set(This 52_food_distribution)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)

set(Sources 
52_food_distribution.cpp)

add_executable(${This} ${Sources})