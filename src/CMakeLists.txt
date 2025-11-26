cmake_minimum_required(VERSION 3.19)

add_library(FGengine SHARED main.cpp)
add_compile_options(-fPIC)

# target_include_directories(FGengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})   -  Why this not works??
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
add_subdirectory(window)

add_subdirectory(objects/camera)
add_subdirectory(objects/model)

add_subdirectory(shaders)

# add_subdirectory(mechanics/walking)
# add_subdirectory(mechanics/camRotation)

target_link_libraries(FGengine window)
target_link_libraries(FGengine camera)
# target_link_libraries(FGengine model)
target_link_libraries(FGengine shaderprogram)
# target_link_libraries(FGengine walking)
# target_link_libraries(FGengine camRotation)
target_link_libraries(FGengine SDL2 GL GLEW)