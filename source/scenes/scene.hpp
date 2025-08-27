#pragma once
#include "objects/camera.hpp"
//#include "mechanics/camRotation.hpp"

class Window;

struct Scene{

	Camera cam;

	virtual void Loading(Window* window) {
		win = window;
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