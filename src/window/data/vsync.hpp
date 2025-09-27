#pragma once
#include <SDL2/SDL.h>

class WindowVsync{
	bool vsync = false;
	bool adaptive = true;

	bool needupdate = true;

protected:
	void Apply(){
		if(needupdate){
			SDL_GL_SetSwapInterval((-1*adaptive)*vsync);
			needupdate = false;
		}
	}

public:
	bool GetVsync(){
		return vsync;
	}
};