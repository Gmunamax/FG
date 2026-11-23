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
#include <FGengine/graphics/model.hpp>
#include <FGengine/graphics/structures/uniform.hpp>

export module Meshes:Breaker;

using FGengine::Graphics::Mesh, FGengine::Uvec4f;

namespace Meshes{

	export class Breaker: public Mesh{
	public:
		Breaker():
			Mesh(GetMesh())
		{}

	private:
		std::span<float> GetMesh();
	};

}
