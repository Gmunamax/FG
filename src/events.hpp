#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "window/window.hpp"

namespace Events{
	SDL_Event currentevent;
	bool appfree = true;
}

bool PollEvent(){
	using namespace Events;

	if(SDL_PollEvent(&currentevent)){
		appfree = false;
	}
	else 
		appfree = true;
	return not appfree;
}

void ProceedEvents(){
	using namespace Events;

	if(PollEvent()){
		Window::SendEvent(currentevent);
	}
}