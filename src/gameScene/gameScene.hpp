#pragma once
#include <FGengine/special/window.hpp>
#include <engine/videoOutput/eventsPack.hpp>
#include <engine/utils/player.hpp>
#include <engine/graphics/model.hpp>
#include <memory>

class GameScene final: public EventsPack{

	Player player;
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShader, fragmentShader);
	Model floor{floorVertexes, shader};

	static inline const char* vertexShader = "\
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
	static inline const char* fragmentShader = "\
	#version 330\n\
	\n\
	out vec4 fragColor;\n\
	\n\
	void main(){\n\
	\t	fragColor = vec4(1,1,0,0);\n\
	}\n\
	";

	static inline float floorVertexes[] {
		-1, 1, 0,
		1, 1, 0,
		-1, -1,0,
		-1, -1, 0
	};

	FGengine::Window* win;
public:

	void Draw() override{
		win->Clear();
		floor.Draw();
		player.Update();
		win->Update();
	}

	void KeyPress(Key key) override{
		if(key == Key::Space){
			player.Jump();
		}
	}
	
	void KeyRelease(Key key) override{

	}

	GameScene(FGengine::Window* win):
		win(win)
	{
		floor.SetPosition({0,0,-1});
	}
};
