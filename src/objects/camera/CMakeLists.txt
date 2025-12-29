cmake_minimum_required(VERSION 2.8)

set(camera_sources
	${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp)

target_sources(FGengine PRIVATE ${camera_sources})

# add_subdirectory(../properties/transform ${CMAKE_CURRENT_BINARY_DIR}../properties/transform)
# target_link_libraries(camera transform)
