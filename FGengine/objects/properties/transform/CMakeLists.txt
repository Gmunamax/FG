cmake_minimum_required(VERSION 2.8)

add_library(transform transform.cpp ${PROJECT_SOURCE_DIR}/structures/point.hpp)
target_include_directories(transform PRIVATE ${PROJECT_SOURCE_DIR})