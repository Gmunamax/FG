#pragma once
#include <SDL2/SDL.h>
#include "FGengine/scene/scene.hpp"

class CamRotation: virtual public Scene{
private:
	bool rtup = false;
	bool rtdown = false;
	bool rtleft = false;
	bool rtright = false;
	bool lookmoving = false;

	SDL_KeyCode up;
	SDL_KeyCode down;
	SDL_KeyCode lookleftkey;
	SDL_KeyCode lookrightkey;

	float speed = 1;

	void UpdateFlags(SDL_KeyboardEvent& key, bool newval);
	

protected:
	CamRotation();

public:

	void SetRotationKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right);

	void CamRotationStart(SDL_KeyboardEvent& key);

	void CamRotationMove();

	void CamRotationEnd(SDL_KeyboardEvent& key);
};