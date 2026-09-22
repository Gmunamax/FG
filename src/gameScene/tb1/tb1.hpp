#pragma once
#include <span>
#include <engine/graphics/model.hpp>
#include <engine/utils/player.hpp>
#include <engine/utils/pathWalker.hpp>
#include "ai.hpp"

class TB1{
public:
	TB1(const glm::vec3& startPosition){
		model.SetPosition(startPosition);
	}

	void Update(){
		static Timer timer;
		float timeDelta = timer.GetTime();
		timer.Reset();

		ai.Update(timeDelta);
		model.Draw();
	}

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

	static Shader GetShader(){
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

		Shader shader{vertex, fragment};

		return shader;
	}

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(GetShader());
	Model model{GetModel(), shader};
	TB1ai ai{model};
};
