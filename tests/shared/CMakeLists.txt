add_library(shared STATIC)
target_include_directories(shared PUBLIC include)
target_sources(shared PRIVATE
	main.cpp
)
