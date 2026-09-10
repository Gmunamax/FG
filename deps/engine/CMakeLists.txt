add_library(engine INTERFACE)
add_subdirectory(deps)

add_subdirectory(graphics)
add_subdirectory(utils)
add_subdirectory(videoOutput)

target_link_libraries(engine INTERFACE engineGraphics engineUtils engineVideoOutput)
