#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "various/loging.hpp"
#include "windowBase.hpp"

SDL_GLContext con;
int GetSystemRefreshRate(){
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	return a.refresh_rate;
}

class Window: public WindowBase{

	static inline std::vector<Window*> allwindows;
	std::vector<Window*>::size_type vectorpos;

	void AddSelf(){
		allwindows.push_back(this);
		vectorpos = allwindows.size() - 1;
	}

	void RemoveSelf(){
		allwindows.erase(allwindows.begin() + vectorpos);
	}

public:

	Window(){
		AddSelf();
		if(allwindows.size() == 0){
			con = SDL_GL_CreateContext(win);
		}
	}
	~Window(){
		RemoveSelf();
		Close();
		if(allwindows.size() == 0){
			SDL_GL_DeleteContext(con);
		}
	}

	void Load(){
		scene->Loading(this);
	}

	static void CloseAll(){
		for(Window* w : allwindows){
			w->Close();
		}
	}

	static void SendEvent(SDL_Event event){
		switch(event.type){

		case SDL_KEYDOWN:
			GetWindowFromID(event.key.windowID)->EventKeyPressed(event.key);
			break;

		case SDL_KEYUP:	
			GetWindowFromID(event.key.windowID)->EventKeyReleased(event.key);
			break;

		case SDL_WINDOWEVENT:

			switch(event.window.event){

			case SDL_WINDOWEVENT_RESIZED:
				GetWindowFromID(event.window.windowID)->Resize({event.window.data1,event.window.data2});
				break;
			}
			break;
		}
	}
	static void DrawAll(){
		for(Window* w : allwindows){
			w->Select();
			w->GetScene()->Cycle();
			w->Apply();

			w->Draw();
		}
	}
};