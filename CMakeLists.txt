cmake_minimum_required(VERSION 3.10)
project(ababiu VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# -g
set(CMAKE_BUILD_TYPE Debug)
# -DDEBUG
add_compile_definitions(DEBUG)
# set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SRC_FILES "src/*.cc")

add_executable(ababiu ${SRC_FILES})
