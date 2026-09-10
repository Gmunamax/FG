cmake_minimum_required(VERSION 3.31)

project(FG)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FG)

add_subdirectory(deps)
add_subdirectory(module)
add_subdirectory(src)
