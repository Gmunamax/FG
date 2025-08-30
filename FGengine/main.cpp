#include "main.hpp"
#include "events.hpp"

static bool run = true;

void quit(){
	run = false;
}

void mainCycle(){

	while (run) {

		ProceedEvents();

		Window::DrawAll();

		SDL_Delay((1.0/60)*1000);
	}
	
	Window::CloseAll();
	SDL_Quit();
}

void init(){
	SDL_Init(SDL_INIT_EVERYTHING);
}