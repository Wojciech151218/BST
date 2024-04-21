cmake_minimum_required(VERSION 3.27)
project(algi2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Include directory containing header files
include_directories(/home/wojciech/CLionProjects/TimeCounter)

# Link against the library
add_executable(algi2 main.cpp Tree.cpp Tree.h AVLTree.cpp AVLTree.h)
target_link_libraries(algi2 /home/wojciech/CLionProjects/TimeCounter/cmake-build-debug/libTimeCounter.a)