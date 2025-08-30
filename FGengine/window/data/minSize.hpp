#pragma once
#include <SDL2/SDL.h>
#include "FGengine/structures/point.hpp"

class WindowMinSize{
	using PointType = Point2i;
	PointType minsize {0};
	bool needupdate = true;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowMinimumSize(SDL_GL_GetCurrentWindow(),minsize.x,minsize.y);
			needupdate = false;
		}
	}

public:
	void SetMinSize(PointType newminsize){
		minsize = newminsize;
		needupdate = true;
	}
	PointType GetMinSize(){
		return minsize;
	}
};