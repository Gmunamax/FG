#pragma once
#include <SDL2/SDL.h>
#include <chrono>

#include "structures/structures.hpp"
#include "objects/objects.hpp"
#include "events.hpp"
#include "drawing.hpp"
#include "window/window.hpp"

SDL_GLContext glcon;

void mainCycle(){
	using namespace States;

	while (run) {

		ProceedEvents();

		Window::DrawAll();

		SDL_Delay((1.0/60)*1000);
		//if(appfree) SDL_Delay((1.0/75)*1000);
	}
	
	Window::CloseAll();
	SDL_Quit();
}

void init(){
	using namespace States;
	
	SDL_Init(SDL_INIT_EVERYTHING);
}