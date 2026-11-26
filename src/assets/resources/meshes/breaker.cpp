// FG - a horror game
// Copyright (C) 2026 Gmunamax <https://github.com/Gmunamax/FG>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
module;
#include <span>
#include <vector>
#include <glm/mat3x3.hpp>
#include <glm/ext/matrix_transform.hpp>

module Meshes;

using namespace Meshes;

std::span<float> Breaker::GetMesh(){
	static float vertexes[]{
		-0.028924, -0.029405, -0.103385,
		-0.028924, -0.029405, 0.103385,
		-0.028924, 0.039440, -0.103385,
		-0.028924, 0.039440, 0.103385,
		0.028924, -0.029405, -0.103385,
		0.028924, -0.029405, 0.103385,
		0.028924, 0.039440, -0.103385,
		0.028924, 0.039440, 0.103385
	};

	static unsigned indices[]{
		2, 3, 1,
		4, 7, 3,
		8, 5, 7,
		6, 1, 5,
		7, 1, 3,
		4, 6, 8,
		2, 4, 3,
		4, 8, 7,
		8, 6, 5,
		6, 2, 1,
		7, 5, 1,
		4, 2, 6,
	};

	static auto mesh = ConvertToVertexArray(vertexes, indices);
	return mesh;
}
