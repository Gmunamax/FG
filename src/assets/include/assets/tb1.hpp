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
#pragma once
#include <span>
#include <FGengine/graphics/model.hpp>

namespace Assets{

class TB1: public FGengine::Graphics::Model{
public:
	TB1():
		Model{GetModel(), GetShader()}
	{}

private:
	static std::span<float> GetModel(){
		static float vertexes[]{
			1, 0, -1,
			-1, 0, 1,
			-1, 0, -1,

			-1, 0, 1,
			1, 0, -1,
			1, 0, 1
		};

		return vertexes;
	}

	static const std::shared_ptr<FGengine::Graphics::Shader>& GetShader(){
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

		static const char* fragment = "\
			#version 330\n\
			\n\
			out vec4 fragColor;\n\
			\n\
			void main(){\n\
			\t	fragColor = vec4(0.5,0.5,0.5,0);\n\
			}\n\
		";

		static FGengine::Graphics::Shader shader{vertex, fragment};
		static std::shared_ptr<FGengine::Graphics::Shader> ptr{&shader};

		return ptr;
	}
};

}
