#pragma once
#include "FGengine/structures/point.hpp"
#include <SDL2/SDL.h>

class WindowPosition{
	using PointType = Point2i;
	PointType position {SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED};
	bool needupdate = false;

protected:
	void Apply(){
		if(needupdate)
			SDL_SetWindowPosition(SDL_GL_GetCurrentWindow(), position.x, position.y);
	}

public:
	void SetPosition(PointType newposition){
		position = newposition;
	}
	PointType GetPosition(){
		return position;
	}
};