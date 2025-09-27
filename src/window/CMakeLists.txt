cmake_minimum_required(VERSION 2.8)

set(base

	data/position.hpp
	data/flags.hpp
	data/title.hpp
	data/size.hpp
	data/vsync.hpp
	data/minSize.hpp
	
	${PROJECT_SOURCE_DIR}/scene/scene.hpp)

set(self

	window.cpp
	windowBase.cpp 
	windowBase.hpp)

add_library(window ${self} ${base})

add_subdirectory(scene)
target_link_libraries(window scene)