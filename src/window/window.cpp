#include "FGengine/window/window.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void Window::AddSelf(){
	allwindows.push_back(this);
	vectorpos = allwindows.size() - 1;
}

void Window::RemoveSelf(){
	allwindows.erase(allwindows.begin() + vectorpos);
}

Window::Window(){
	AddSelf();
}

Window::~Window(){
	RemoveSelf();
	Close();
}

void Window::Load(){
	scene->Loading(this);
}

void Window::CloseAll(){
	for(Window* w : allwindows){
		w->Close();
	}
}

bool needupdateevent = true;
SDL_Event event;
void Window::SendEvent(){

	WindowBase* windowptr;
	while(SDL_PollEvent(&event)){
		
		switch(event.type){

		case SDL_KEYDOWN:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr) 
				windowptr->EventKeyPressed(event.key);
			break;

		case SDL_KEYUP:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr)
				windowptr->EventKeyReleased(event.key);
			break;

		case SDL_WINDOWEVENT:
			windowptr = GetWindowFromID(event.window.windowID);
			windowptr->Select();

			switch(event.window.event){

			case SDL_WINDOWEVENT_RESIZED:
				windowptr->Resize({event.window.data1,event.window.data2});
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				windowptr->Update();
				break;
			}
			break;
			
		}
	}
}

void Window::DrawAll(){
	for(Window* w : allwindows){
		w->Select();
		w->GetScene()->Cycle();
		w->Apply();

		w->Draw();
	}		
}