#pragma once
#include <SDL2/SDL.h>
#include <chrono>

#include "../structures/structures.hpp"
#include "../objects/objects.hpp"
#include "drawing.hpp"

void mainCycle(){
	using namespace States;

	onsceneloading();

	while (run) {

		ProceedEvents();

		oncycle();

		if(needresize){
			currentcamera->Resize({0,0,(int)windoww,(int)windowh});
			needupdate = true;
		}

		DrawScreen();

		if(vsync) SDL_Delay((1.0/75)*1000);
	}
	
	onclosingscene();
	CloseWindow();
	SDL_Quit();
}

void init(unsigned int w, unsigned int h){
	using namespace States;
	SDL_Init(SDL_INIT_EVERYTHING);

	windoww = w;
	windowh = h;
	win = SDL_CreateWindow(" a ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windoww,windowh,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	SDL_SetWindowMinimumSize(win,160,120);

	glcon = SDL_GL_CreateContext(win);
	GLenum glewres = glewInit();
	if(glewres != GLEW_OK)
		std::cout << glewGetErrorString(glewres) << std::endl;
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);
	// glEnable(GL_COLOR_MATERIAL);
	// glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_CLAMP);
	glDepthRange(0.5,100);

	initWindow();
}