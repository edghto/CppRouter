cmake_minimum_required(VERSION 3.0)


file(GLOB_RECURSE SRC *.cpp *.hpp)

include_directories(".")
add_definitions(-std=c++14)
add_executable(main ${SRC})
