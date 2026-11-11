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
#include <format>
#include <FGengine/graphics/shader.hpp>

export module Models:BasicShader;
using FGengine::Graphics::Shader;

namespace Models{

	export class BasicShader: public Shader{
	public:
		BasicShader(float r, float g, float b):
			Shader(GenVertexShader(), GenFragmentShader(r, g, b))
		{}

	private:
		static std::string_view GenVertexShader(){
			static const char* vertex = "\
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

			return vertex;
		}

		static std::string GenFragmentShader(float r, float g, float b){
			auto color = std::format("{}, {}, {}, 0", r, g, b);

			std::string shader = std::format("\
				#version 330\n\
				\n\
				out vec4 fragColor;\n\
				\n\
				void main(){{\n\
				\t	fragColor = vec4({});\n\
				}}\n\
				",
				color
			);

			return shader;
		}

	};

}
