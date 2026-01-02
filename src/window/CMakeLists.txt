cmake_minimum_required(VERSION 2.8)

# set(base

# 	${CMAKE_CURRENT_SOURCE_DIR}/data/position.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/data/flags.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/data/title.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/data/size.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/data/vsync.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/data/minSize.hpp
	
# 	${PROJECT_SOURCE_DIR}/scene/scene.hpp)

set(self

	)

target_sources(FGengine
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/windowBase.cpp
)

add_subdirectory(scene)
