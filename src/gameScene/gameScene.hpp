#pragma once
#include <FGengine/special/window.hpp>
#include <engine/videoOutput/eventsPack.hpp>
#include <engine/utils/player.hpp>
#include <engine/graphics/model.hpp>
#include <memory>
#include "freeroamPlayer.hpp"

class GameScene final: public EventsPack{

	FreeroamPlayer player;
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
		switch(key){
		case Key::Space:
			player.Jump();
			break;
		
		case Key::W:
			player.SetWalkY(FreeroamPlayer::MovementType::On);
			break;
		
		case Key::A:
			player.SetWalkX(FreeroamPlayer::MovementType::Reverse);
			break;

		case Key::S:
			player.SetWalkY(FreeroamPlayer::MovementType::Reverse);
			break;
		
		case Key::D:
			player.SetWalkX(FreeroamPlayer::MovementType::On);
			break;

		case Key::Up:
			player.SetYaw(FreeroamPlayer::MovementType::On);
			break;

		case Key::Down:
			player.SetYaw(FreeroamPlayer::MovementType::Reverse);
			break;

		case Key::Left:
			player.SetPitch(FreeroamPlayer::MovementType::Reverse);
			break;

		case Key::Right:
			player.SetPitch(FreeroamPlayer::MovementType::On);
			break;

		default:
			break;
		}
	}
	
	void KeyRelease(Key key) override{
		switch(key){
		case Key::W:
			player.SetWalkY(FreeroamPlayer::MovementType::Off);
			break;

		case Key::A:
			player.SetWalkX(FreeroamPlayer::MovementType::Off);
			break;

		case Key::S:
			player.SetWalkY(FreeroamPlayer::MovementType::Off);
			break;

		case Key::D:
			player.SetWalkX(FreeroamPlayer::MovementType::Off);
			break;

		case Key::Up:
			player.SetYaw(FreeroamPlayer::MovementType::Off);
			break;
		
		case Key::Down:
			player.SetYaw(FreeroamPlayer::MovementType::Off);
			break;

		case Key::Left:
			player.SetPitch(FreeroamPlayer::MovementType::Off);
			break;

		case Key::Right:
			player.SetPitch(FreeroamPlayer::MovementType::Off);
			break;

		default:
			break;
		}
	}

	GameScene(FGengine::Window* win):
		win(win)
	{
		floor.SetPosition({0,0,-1});
	}
};
