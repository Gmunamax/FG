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
#include <FGengine/graphics/shader.hpp>
#include <memory>

export module Shaders:Breaker;

using FGengine::Graphics::Shader;

namespace Shaders{

	export class Breaker: public Shader{
	public:
		Breaker():
			Shader(vertex, fragment)
		{}

	private:
		static inline constexpr const char* vertex = "\
			#version 330\n\
			\n\
			layout (location = 0) in vec3 pos;\n\
			\n\
			uniform mat4 model;\n\
			layout(std140) uniform camera{\n\
				mat4 projection;\n\
				mat4 view;\n\
			};\n\
			\
			void main(){\n\
			\t	gl_Position = projection * view * model * vec4(pos, 1.0);\n\
			}\
		";

		static inline constexpr const char* fragment = "\
			#version 330\n\
			\n\
			out vec4 fragColor;\n\
			uniform vec4 color;\n\
			\n\
			void main(){\n\
			\t	fragColor = color;\n\
			}\n\
		";

	};

}
