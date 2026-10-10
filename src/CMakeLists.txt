target_sources(FG PRIVATE main.cpp)
target_link_libraries(FG PRIVATE argParser pathFinder random engine FGengine)
add_subdirectory(gameScene)
