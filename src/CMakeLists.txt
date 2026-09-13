target_sources(FG PRIVATE main.cpp)
target_link_libraries(FG PRIVATE argParser engine FGengine SDL2)
add_subdirectory(gameScene)
