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
