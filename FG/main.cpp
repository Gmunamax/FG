#include <iostream>
#include "FGengine/FGengine.hpp"
#include "config.hpp"
#include "shaders.hpp"
//#include "scenes/rotatingCube.hpp"
//#include "scenes/landspace.hpp"
#include "scenes/fg.hpp"
#include <fstream>

int GetSystemRefreshRate(){
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	return a.refresh_rate;
}

// Window w1;
// Window w2;
Window fgwin;

// void LoadWindow1(){
// 	w1.SetTitle("Window N.1");
// 	w1.SetFlags(SDL_WINDOW_RESIZABLE);
// 	w1.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
// 	w1.SetSize({WINDOW1W,WINDOW1H});
// 	w1.SetFPS(GetSystemRefreshRate());
// 	w1.SetScene(Landspace::New());
// 	w1.SetMinSize({320,240});
// 	w1.Open();
// 	w1.Select();
// 	w1.Load();
// }

// void LoadWindow2(){
// 	w2.SetTitle("Window N.2");
// 	w2.SetFPS(GetSystemRefreshRate());
// 	w2.SetFlags(0);
// 	w2.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
// 	w2.SetSize({WINDOW2W,WINDOW2H});
// 	w2.SetScene(RotatingCube::New());
// 	w2.SetMinSize({320,240});
// 	w2.Open();
// 	w2.Select();
// 	w2.Load();
// }

void LoadFGWindow(){
	fgwin.SetTitle("FG");
	fgwin.SetFPS(GetSystemRefreshRate());
	fgwin.SetFlags(SDL_WINDOW_RESIZABLE);
	fgwin.SetPosition({SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED});
	fgwin.SetSize({800,600});
	fgwin.SetMinSize({320,240});
	fgwin.SetScene(FgScene::New());
	fgwin.Open();
	fgwin.Select();
	fgwin.Load();
}

int main(){

	init();

	LoadFGWindow();
	//GLuint s1 = LoadShader("../resources/shaders/sth.vert", GL_VERTEX_SHADER);
	//GLuint s2 = LoadShader("../resources/shaders/sth.frag", GL_FRAGMENT_SHADER);
	//GLuint prog = LinkProgram(s1,s2);
	//glUseProgram(prog);
	
	
	std::cout << "Hello world!" << std::endl;
	mainCycle();
	std::cout << "Goodbye" << std::endl;
	
	return 0;
}