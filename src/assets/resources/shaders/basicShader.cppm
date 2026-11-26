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
#include <string>
#include <string_view>
#include <FGengine/graphics/shader.hpp>

export module Shaders:BasicShader;
using FGengine::Graphics::Shader;

namespace Shaders{

	export class BasicShader: public Shader{
	public:
		BasicShader(float r, float g, float b):
			Shader(GenVertexShader(), GenFragmentShader(r, g, b))
		{}

	private:
		static std::string_view GenVertexShader();

		static std::string GenFragmentShader(float r, float g, float b);

	};

}
