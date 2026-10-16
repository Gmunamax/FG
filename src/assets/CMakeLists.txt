add_library(assets STATIC)
target_link_libraries(assets PUBLIC engine)
target_include_directories(assets PUBLIC include)
add_subdirectory(src)
