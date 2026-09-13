#include "gameScene.hpp"

const char* GameScene::vertexShader = "\
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

const char* GameScene::fragmentShader = "\
	#version 330\n\
	\n\
	out vec4 fragColor;\n\
	\n\
	void main(){\n\
	\t	fragColor = vec4(1,1,0,0);\n\
	}\n\
	";
