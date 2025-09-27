cmake_minimum_required(VERSION 2.8)

set(properties

	buffer
	transform)

#add_subdirectory(${properties})

add_subdirectory(buffer)
add_subdirectory(transform)

add_library(properties INTERFACE)
target_link_libraries(${properties})