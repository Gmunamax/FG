cmake_minimum_required(VERSION 2.8)

add_executable(FG main.cpp)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(FG FGengine)