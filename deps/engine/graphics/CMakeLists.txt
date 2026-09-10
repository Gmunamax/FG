add_library(engineGraphics STATIC)
target_include_directories(engineGraphics PUBLIC include)
target_link_libraries(engineGraphics PRIVATE FGengine loader)
add_subdirectory(src)
