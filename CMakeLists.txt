# FGengine - a free and open-source library for game development
# Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.25)

project(FGengine)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(FGengine SHARED)
add_compile_options(-fPIC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(deps/glad)
add_subdirectory(modules)
add_subdirectory(src)

find_package(SDL2 2.32 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(FGengine PRIVATE SDL2::SDL2 OpenGL::GL glad)