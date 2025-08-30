#pragma once
#include <SDL2/SDL.h>
#include "FGengine/scene/scene.hpp"
#include "FGengine/structures/point.hpp"

class WindowSize: virtual public WindowScene{
	using PointType = Point2i;

	PointType size {0,0};
	bool needupdate = false;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowSize(SDL_GL_GetCurrentWindow(), size.x, size.y);
			Resize(size);
			needupdate = false;
		}

	}

	void Resize(PointType newsize){
		size = newsize;
		GetScene()->cam.Resize({0,0,newsize.x,newsize.y});
		Update();
	}

public:
	void SetSize(PointType newsize){
		size = newsize;
		needupdate = true;
	}
	PointType GetSize(){
		return size;
	}
};