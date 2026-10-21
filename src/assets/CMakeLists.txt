add_library(assets STATIC)
target_link_libraries(assets PUBLIC FGengine)
target_include_directories(assets PUBLIC include)
add_subdirectory(src)
