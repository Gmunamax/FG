#pragma once
#include <SDL2/SDL.h>


class WindowFlags{
	Uint32 flags = SDL_WINDOW_OPENGL;

public:
	void SetFlags(Uint32 newflags){
		flags = SDL_WINDOW_OPENGL | newflags;
	}
	Uint32 GetFlags(){
		return flags;
	}
};