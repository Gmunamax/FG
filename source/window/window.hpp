#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "scenes/scene.hpp"
#include "various/loging.hpp"
#include "main/events.hpp"
#include "data/windowScene.hpp"
#include "data/windowPosition.hpp"

int GetSystemRefreshRate(){
	SDL_DisplayMode a;
	SDL_GetDesktopDisplayMode(0,&a);
	return a.refresh_rate;
}

// //TODO: Clear THIS class
// class WindowData: virtual public WindowUpdating{

// 	using PointType = Point2i;
// 	bool needresize = true;


// 	std::string title;
// 	Uint32 windowflags = SDL_WINDOW_OPENGL;
// 	PointType position;
// 	PointType size;
// 	PointType minimumsize;

// 	SDL_WindowFlags fullscreenmode = SDL_WINDOW_FULLSCREEN_DESKTOP;

// protected:

// 	WindowData(){}

// 	void Resize(){
// 		if(needresize){
// 			GetScene()->cam.Resize({0,0,size.x,size.y});
// 			Update();
// 		}
// 	}

// public:
// 	void SetTitle(std::string newtitle){
// 		title = newtitle;
// 	}
// 	void SetWindowFlags(Uint32 flags){
// 		windowflags = windowflags | flags;
// 	}

// 	PointType& GetPosition(){
// 		return position;
// 	}
// 	void SetPosition(PointType newposition){
// 		position = newposition;
// 	}

// 	PointType& GetSize(){
// 		return size;
// 	}
// 	void SetSize(PointType newscale){
// 		size = newscale;
// 		needresize = true;
// 	}

// 	void SetMinimumSize(PointType newminimumsize){
// 		minimumsize = newminimumsize;
// 	}

// 	void EnterFullscreen(){
// 		SDL_SetWindowFullscreen(win,fullscreenmode);
// 	}
// 	void ExitFullscreen(){
// 		SDL_SetWindowFullscreen(win,0);
// 	}

// 	void Open(){
// 		win = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, windowflags);
// 		SDL_SetWindowMinimumSize(win, minimumsize.x, minimumsize.y);
// 		ApplyScene(win);
// 		glcon = SDL_GL_CreateContext(win);
// 		InitBackend();
// 	}
// 	void Close(){
// 		SDL_GL_DeleteContext(glcon);
// 		SDL_DestroyWindow(win);
// 	}

// 	~WindowData(){
// 		Close();
// 	}
// };

class WindowSize: virtual public WindowScene{
	using PointType = Point2i;

	PointType size {0,0};
	bool needupdate = false;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowSize(SDL_GL_GetCurrentWindow(), size.x, size.y);
			Resize(size);
			needupdate = false;
		}

	}

	void Resize(PointType newsize){
		size = newsize;
		GetScene()->cam.Resize({0,0,newsize.x,newsize.y});
		Update();
	}

public:
	void SetSize(PointType newsize){
		size = newsize;
		needupdate = true;
	}
	PointType GetSize(){
		return size;
	}
};

class WindowFlags{
	Uint32 flags = SDL_WINDOW_OPENGL;

public:
	void SetFlags(Uint32 newflags){
		flags = SDL_WINDOW_OPENGL | newflags;
	}
	Uint32 GetFlags(){
		return flags;
	}
};

class WindowTitle{
	std::string title;
	bool needupdate = true;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(),title.c_str());
			needupdate = false;
		}
	}

public:
	void SetTitle(std::string newtitle){
		title = newtitle;
	}
	std::string GetTitle(){
		return title;
	}
};



class WindowBase: public WindowPosition, public WindowFlags, public WindowTitle, public WindowSize{
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
		}
	}

	void Select(){
		if(opened){
			SDL_GL_MakeCurrent(win,glcon);
			if(SDL_GL_GetCurrentWindow() != win){
				Log(SDL_GetError());
			};
		}
	}

public:
	void Open(){
		if(not opened){
			win = SDL_CreateWindow(GetTitle().c_str(),GetPosition().x,GetPosition().y,GetSize().x,GetSize().y,GetFlags());
			glcon = SDL_GL_CreateContext(win);
			InitBackend();
			SDL_SetWindowData(SDL_GL_GetCurrentWindow(),windowdataname,this);
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
	}
	~Window(){
		RemoveSelf();
		Close();
	}

	void Load(){
		scene->Loading(this);
	}

	static void CloseAll(){
		for(Window* w : allwindows){
			w->Close();
		}
	}

	static void UpdateAll(SDL_Event event){
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