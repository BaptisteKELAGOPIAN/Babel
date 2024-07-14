# CMake dependencies
cmake_minimum_required(VERSION 3.20.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(babel)


# Source
add_subdirectory("./Server/")
add_subdirectory("./Client/")
