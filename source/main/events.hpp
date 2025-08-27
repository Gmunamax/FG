#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "window/window.hpp"

namespace States{
	SDL_Event currentevent;
	bool appbusy = true;
}

bool PollEvent(){
	using namespace States;

	if(SDL_PollEvent(&currentevent)){
		appbusy = true;
		return true;
	}
	else 
		appbusy = false;
		return false;
}

void ProceedEvents(){
	using namespace States;

	if(PollEvent()){
		Window::UpdateAll(currentevent);
	}
}