cmake_minimum_required(VERSION 2.8)

add_library(model model.cpp ../properties/buffer/buffer.hpp ../properties/transform/transform.hpp)
add_subdirectory(../properties/buffer ${CMAKE_CURRENT_BINARY_DIR}../properties/buffer)
target_link_libraries(model buffer)