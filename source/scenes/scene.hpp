#pragma once
#include "objects/camera.hpp"
//#include "mechanics/camRotation.hpp"

class Window;

class Scene{
	friend class WindowScene;
	friend class Window;

protected:
	Window* win;
	Camera cam;

	virtual void Loading(Window* window) {
		win = window;
	};
	virtual void Placing() {};
	virtual void Drawing() {};
	virtual void KeyPressed(SDL_KeyboardEvent) {};
	virtual void KeyReleased(SDL_KeyboardEvent) {};
	virtual void Cycle() {};
	virtual void Closing() {};

	virtual void Delete() = 0;

	Scene() {};
};