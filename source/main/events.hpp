#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "window/window.hpp"

namespace States{
	SDL_Event currentevent;
	bool appfree = true;
}

bool PollEvent(){
	using namespace States;

	if(SDL_PollEvent(&currentevent)){
		appfree = false;
	}
	else 
		appfree = true;
	return not appfree;
}

void ProceedEvents(){
	using namespace States;

	if(PollEvent()){
		Window::SendEvent(currentevent);
	}
}