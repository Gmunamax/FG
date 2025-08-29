#include <iostream>
#include "main/main.hpp"
#include "scenes/scene1.hpp"
#include "config.hpp"
#include "scenes/buffer.hpp"
#include "window/window.hpp"

void test(){
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* t1 = SDL_CreateWindow("1",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600, SDL_WINDOW_OPENGL);
	SDL_Window* t2 = SDL_CreateWindow("2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600, SDL_WINDOW_OPENGL);

	SDL_GLContext glcon = SDL_GL_CreateContext(nullptr);
	std::cout << glcon << SDL_GetError() << std::endl;

	SDL_GLContext glcon2 = SDL_GL_CreateContext(t1);
	SDL_GLContext glcon3 = SDL_GL_CreateContext(t1);
	std::cout << glcon2 << std::endl;

	glViewport(0,0,800,600);
	glBegin(GL_TRIANGLES);
		glVertex2d(-0.9,-0.9);
		glVertex2d(0.9,-0.9);
		glVertex2d(0,0.9);
	glEnd();

	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

	std::cout << SDL_GL_GetSwapInterval() << std::endl;

	SDL_GL_SetSwapInterval(0);

	SDL_GL_MakeCurrent(t2,glcon3);
	std::cout << glcon2 << std::endl;

	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

	glViewport(0,0,800,600);
	glBegin(GL_TRIANGLES);
		glVertex2d(0.9,0.9);
		glVertex2d(-0.9,0.9);
		glVertex2d(-0,-0.9);
	glEnd();

	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

	SDL_Delay(10000);
}

int main(){

	init();

	Window w1;
	w1.SetTitle("Window N.1");
	w1.SetFlags(SDL_WINDOW_RESIZABLE);
	w1.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w1.SetSize({WINDOWW,WINDOWH});
	w1.SetFPS(GetSystemRefreshRate());
	w1.SetScene(Scene1::New());
	w1.SetMinSize({320,240});
	w1.Open();
	w1.Select();
	w1.Load();

	Window w2;
	w2.SetTitle("Window N.2");
	w2.SetFPS(GetSystemRefreshRate());
	w2.SetFlags(SDL_WINDOW_RESIZABLE);
	w2.SetPosition({SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED});
	w2.SetSize({320,240});
	w2.SetScene(Scene2::New());
	w2.SetMinSize({320,240});
	w2.Open();
	w2.Select();
	w2.Load();

	Log("Hello world!");
	Log("Starting");
	mainCycle();
	Log("Goodbye");
	
	return 0;
}