#pragma once
#include <SDL2/SDL.h>
#include "window.hpp"
#include <iostream>

namespace States{
	SDL_Event currentevent;
	bool appbusy = true;

	void(*onsceneloading)() = nullptr;
	void(*onscenedrawing)() = nullptr;
	void(*onclosingscene)() = nullptr;
	void(*onkeypressed)(SDL_KeyboardEvent&) = nullptr;
	void(*onkeyreleased)(SDL_KeyboardEvent&) = nullptr;
	void(*oncycle)() = nullptr;
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
		switch(currentevent.type){

		case SDL_KEYDOWN:

			onkeypressed(currentevent.key);
			break;
		case SDL_KEYUP:
			
			onkeyreleased(currentevent.key);
			break;

		case SDL_WINDOWEVENT:
				
			switch(currentevent.window.event){

			case SDL_WINDOWEVENT_RESIZED:
					
				needresize = true;
				windoww = currentevent.window.data1;
				windowh = currentevent.window.data2;
				break;
			}

			break;

		}
	}
}