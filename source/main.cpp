#include <iostream>
#include "main/main.hpp"
#include "scenes/scene1.hpp"
#include "config.hpp"
//#include "scenes/buffer.hpp"
#include "window/window.hpp"

int main(){

	init();

	Window w1;
	w1.SetTitle("Window N.1");
	w1.SetWindowFlags(SDL_WINDOW_RESIZABLE);
	w1.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w1.SetSize({WINDOWW,WINDOWH});
	w1.SetFPS(10);
	w1.Open();
	w1.SetScene(Scene1::New());

	Window w2;
	w2.SetTitle("Window N.2");
	w2.SetFPS(GetSystemRefreshRate());
	w2.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w2.SetSize({320,240});
	w2.Open();
	w2.SetScene(Scene1::New());

	Log("Hello world!");
	Log("Starting");
	mainCycle();
	Log("Goodbye");
	
	return 0;
}