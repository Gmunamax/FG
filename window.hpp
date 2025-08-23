#pragma once
#include <SDL2/SDL.h>
SDL_Window* win;
SDL_GLContext glcon;

namespace States{

	unsigned int windoww;
	unsigned int windowh;
	bool fullscreen = false;
	bool needresize = false;
	bool needupdate = true;
	short fps;

}

void initWindow(){
	using namespace States;
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	fps = a.refresh_rate;
	
}

void CloseWindow(){
	SDL_DestroyWindow(win);
}