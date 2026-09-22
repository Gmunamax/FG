target_sources(FG PRIVATE main.cpp)
target_link_libraries(FG PRIVATE argParser pathFinder engine FGengine)
add_subdirectory(gameScene)
