#pragma once
#include <FGengine/special/window.hpp>
#include "../events.hpp"
#include "player.hpp"
#include "floor.hpp"

class GameScene final: public EventsPack{

	struct Map{
		// Model floor;
		// Model cube;
	};

	Player player;
	Map gameMap;
	Floor floor;

	FGengine::Window* win;
public:

	void Draw() override{
		win->Clear();
		floor.Draw();
		player.Draw();
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
	{}
};
