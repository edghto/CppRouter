project(CppRouter)
cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE SRC *.cpp *.hpp)

include_directories("include" ".")
add_definitions(-std=gnu++14 -O0 -Wgnu-string-literal-operator-template)
add_executable(main ${SRC})

target_link_libraries(main
    boost_regex)
