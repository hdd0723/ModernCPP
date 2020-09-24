cmake_minimum_required(VERSION 3.10)

project(container)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(simple_container simple_container.cpp)
add_executable(other_container other_container.cpp)