cmake_minimum_required(VERSION 3.19)

add_library(FGengine SHARED main.cpp)
add_compile_options(-fPIC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(window)
add_subdirectory(objects)
add_subdirectory(shaders)

# add_subdirectory(mechanics/walking)
# add_subdirectory(mechanics/camRotation)

# target_link_libraries(FGengine window)
# target_link_libraries(FGengine camera)
# target_link_libraries(FGengine model)
# target_link_libraries(FGengine shaders)
# target_link_libraries(FGengine walking)
# target_link_libraries(FGengine camRotation)
target_link_libraries(FGengine SDL2 GL GLEW)