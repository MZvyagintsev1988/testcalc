cmake_minimum_required(VERSION 2.8)
project(topcalc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

add_library(math.base STATIC "error.hpp" "math.base.cpp")
add_library(math.func STATIC "error.hpp" "math.func.cpp")
add_library(math.util STATIC "error.hpp" "math.util.cpp")

target_link_libraries(math.base math.func)
target_link_libraries(math.base math.util)
target_link_libraries(math.base "m")

target_link_libraries(math.func math.util)

target_link_libraries(math.util math.base)
target_link_libraries(math.util math.base)


add_executable(${PROJECT_NAME} "error.hpp" "main.cpp" "test.cpp")
target_link_libraries(${PROJECT_NAME} math.util)
