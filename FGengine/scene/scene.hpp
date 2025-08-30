//Idk where to put this file again

#pragma once
#include <SDL2/SDL.h>
#include "FGengine/objects/camera/camera.hpp"

class Window;

struct Scene{

	Camera cam;

	virtual void Loading(Window* window) {
		this->win = window;
	};
	//virtual void Placing() {};
	virtual void Drawing() {};
	virtual void KeyPressed(SDL_KeyboardEvent&) {};
	virtual void KeyReleased(SDL_KeyboardEvent&) {};
	virtual void Cycle() {};

	virtual void Deleting() = 0;

protected:
	Window* win;
	Scene() {};
};