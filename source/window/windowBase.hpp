#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "various/loging.hpp"
#include "data/windowScene.hpp"
#include "data/windowPosition.hpp"
#include "data/windowFlags.hpp"
#include "data/windowTitle.hpp"
#include "data/windowSize.hpp"
#include "data/windowVsync.hpp"
#include "data/windowMinSize.hpp"

class WindowBase: public WindowPosition, public WindowFlags, public WindowTitle, public WindowSize, public WindowVsync, public WindowMinSize{
	friend class Window;
	static inline const char* windowdataname = "Scene";

	SDL_GLContext glcon;
	SDL_Window* win;
	bool opened = false;

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

protected:
	static WindowBase* GetWindowFromID(Uint32 id){
		return static_cast<WindowBase*>(SDL_GetWindowData(SDL_GetWindowFromID(id), windowdataname));
	}

	void Apply(){
		if(opened){
			WindowTitle::Apply();
			WindowSize::Apply();
			WindowVsync::Apply();
			WindowMinSize::Apply();
		}
	}

public:
	void Select(){
		if(opened){
			SDL_GL_MakeCurrent(win,glcon);
			if(SDL_GL_GetCurrentWindow() != win){
				Log(SDL_GetError());
			};
		}
	}

	void Open(){
		if(not opened){
			win = SDL_CreateWindow(GetTitle().c_str(),GetPosition().x,GetPosition().y,GetSize().x,GetSize().y,GetFlags());
			glcon = SDL_GL_CreateContext(win);
			InitBackend();
			SDL_SetWindowData(win,windowdataname,this);
			opened = true;
		}
	}
	void Close(){
		if(opened){
			SDL_DestroyWindow(win);
			SDL_GL_DeleteContext(glcon);
			opened = false;
		}
	}
};