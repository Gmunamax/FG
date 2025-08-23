#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../events.hpp"
#include "../window.hpp"
#include "../objects/camera.hpp"

namespace States {
	
	
	bool linesxray = false;
	bool vsync = false;
	bool run = true;
	short frameskip = 0;

}

void DrawScreen(){
	using namespace States;

	float frametime = 1.0/fps*1000;
		
	if(frameskip <= 0){
		if(needupdate){
			std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

			glPushMatrix();
				currentcamera->StartDrawing();
				onscenedrawing();
			glPopMatrix();

			SDL_GL_SwapWindow(win);

			needupdate = false;

			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
			
			auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
			frameskip = t.count()/frametime;
			frameskip--;
		}
	}
	else{
		std::cout << "Frameskip: " << frameskip << " left\n";
		frameskip--;
	} 
}