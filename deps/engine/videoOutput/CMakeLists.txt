add_library(engineVideoOutput INTERFACE)
target_include_directories(engineVideoOutput INTERFACE include)
target_link_libraries(engineVideoOutput INTERFACE SDL3)

# add_subdirectory(src)
