target_sources(FG PRIVATE main.cpp)
target_link_libraries(FG PRIVATE argParser FGengine SDL2 GL)
target_link_libraries(FG PRIVATE loader)
