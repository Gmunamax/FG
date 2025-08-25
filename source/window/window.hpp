#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <map>
//#include "windowBackend.hpp"
#include "scenes/scene.hpp"
#include "various/loging.hpp"
#include "main/events.hpp"

int GetSystemRefreshRate(){
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	return a.refresh_rate;
}

//TODO: Clear this class
class Window{

	static inline std::vector<Window*> allwindows;
	std::vector<Window*>::size_type vectorpos;

	float frametime;
	Uint32 frameskip = 0;
	
	std::string title;
	Uint32 windowflags = SDL_WINDOW_OPENGL;
	SDL_WindowFlags fullscreenmode = SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_Window* win;
	SDL_GLContext glcon;

	void InitBackend(){
		GLenum glewres = glewInit();
		if(glewres != GLEW_OK)
			std::cout << glewGetErrorString(glewres) << std::endl;

		glEnable(GL_DEPTH_TEST);
		// glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT0);
		// glEnable(GL_COLOR_MATERIAL);
		// glEnable(GL_NORMALIZE);
		glEnable(GL_DEPTH_CLAMP);
		glDepthRange(0.5,100);
	}

	void Draw(){
		if(frameskip <= 0){
			if(needupdate){
				std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

				scene->Drawing();
				SDL_GL_SwapWindow(win);
				needupdate = false;

				std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

				auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
				frameskip = t.count()/frametime;

				frameskip--; /* to avoid false positives */
			}
		}
		else{
			FastLog("Frameskip: " + std::string{(char)frameskip} + " left\n");
			frameskip--;
		}
	}

	using PointType = Point2i;

	PointType position;
	PointType size;

	Scene* scene;

	bool needresize = true;
	bool needupdate = true;

public:
	static inline const char* windowdataname = "Window";

	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}

	PointType& GetSize(){
		return size;
	}
	void SetSize(PointType newscale){
		size = newscale;
		needresize = true;
	}
	void SetMinimumSize(Point2i newminsize){
		SDL_SetWindowMinimumSize(win,newminsize.x,newminsize.y);
	}

	void SetWindowFlags(Uint32 flags){
		windowflags = windowflags | flags;
	}

	void Select(){
		SDL_GL_MakeCurrent(win,glcon);
	}

	void Close(){
		SDL_GL_DeleteContext(glcon);
		SDL_DestroyWindow(win);
	}
	void Open(){
		win = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, windowflags);
		SDL_SetWindowData(win,windowdataname,this);
		glcon = SDL_GL_CreateContext(win);
		InitBackend();
	}

	void SetFPS(short fps){
		frametime = 1.0/fps*1000;
	}

	Window(){
		allwindows.push_back(this);
		vectorpos = allwindows.size() - 1;
		Select();
	}
	~Window(){
		Close();
		allwindows.erase(allwindows.begin() + vectorpos);
		scene->Closing();
		scene->Delete();
	}

	
	void EnterFullscreen(){
		SDL_SetWindowFullscreen(win,fullscreenmode);
	}
	void ExitFullscreen(){
		SDL_SetWindowFullscreen(win,0);
	}

	void SetTitle(std::string newtitle){
		title = newtitle;
	}

	void SetScene(Scene* newscene){	
		scene = newscene;
		scene->Loading(this);
	}

	void Update(){
		needupdate = true;
	}

	static void CloseAll(){
		for(Window* w : allwindows){
			w->Close();
		}
	}

	static void ProceedEvent(SDL_Event event){
		switch(event.type){

		case SDL_KEYDOWN:

			static_cast<Window*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), Window::windowdataname))->scene->KeyPressed(event.key);
			break;
			
		case SDL_WINDOWEVENT:
				
			static_cast<Window*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), Window::windowdataname))->scene->KeyReleased(event.key);
			break;

		}

		for(Window* w : allwindows){
			w->scene->Cycle();
			w->Select();
			if(w->needresize){
				w->scene->cam.Resize({0,0,w->size.x,w->size.y});
				w->Update();
			}
			w->Draw();
		}
	}
};