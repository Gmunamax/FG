#include <iostream>
#include "FGengine/FGengine.hpp"
#include "config.hpp"
#include "scenes/rotatingCube.hpp"
#include "scenes/landspace.hpp"

int GetSystemRefreshRate(){
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	return a.refresh_rate;
}

Window w1;
Window w2;

void LoadWindow1(){
	w1.SetTitle("Window N.1");
	w1.SetFlags(SDL_WINDOW_RESIZABLE);
	w1.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w1.SetSize({WINDOW1W,WINDOW1H});
	w1.SetFPS(GetSystemRefreshRate());
	w1.SetScene(Landspace::New());
	w1.SetMinSize({320,240});
	w1.Open();
	w1.Select();
	w1.Load();
}

void LoadWindow2(){
	w2.SetTitle("Window N.2");
	w2.SetFPS(GetSystemRefreshRate());
	w2.SetFlags(SDL_WINDOW_RESIZABLE);
	w2.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w2.SetSize({WINDOW2W,WINDOW2H});
	w2.SetScene(Scene2::New());
	w2.SetMinSize({320,240});
	w2.Open();
	w2.Select();
	w2.Load();
}

int main(){

	init();

	LoadWindow1();
	LoadWindow2();

	std::cout << "Hello world!" << std::endl;
	mainCycle();
	std::cout << "Goodbye" << std::endl;
	
	return 0;
}