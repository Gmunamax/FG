#pragma once
#include <SDL2/SDL.h>
#include <chrono>
#include "FGengine/scene/scene.hpp"

class WindowSceneCore{
protected:
	Scene* scene = nullptr;
	bool needupdate = true;

public:
	void Update(){
		needupdate = true;
	}

	Scene* GetScene(){
		return scene;
	}
	void SetScene(Scene* newscene){
		scene = newscene;
	}

};

class WindowDrawing: virtual public WindowSceneCore{
	double frametime;
	Uint8 frameskip = 0;
	Colord bgcolor;

	double stepsize;

	std::chrono::time_point<std::chrono::steady_clock> secs;

	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
protected:

	WindowDrawing(){}

	void Draw();

public:
	double GetStepCoefficient(){
		return stepsize;
	}
	
	void SetFPS(short fps){
		frametime = 1.0/fps*1000;
	}

	
};

class WindowEvents: virtual public WindowSceneCore{
protected:

	void EventDelete(){
		if(scene != nullptr){
			scene->Deleting();
		}
	}
	void EventDrawing(){
		if(scene != nullptr){
			scene->Drawing();
		}
	}
	void EventKeyPressed(SDL_KeyboardEvent& key){
		if(scene != nullptr){
			scene->KeyPressed(key);
		}
	}
	void EventKeyReleased(SDL_KeyboardEvent& key){
		if(scene != nullptr){
			scene->KeyReleased(key);
		}
	}
	void EventCycle(){
		if(scene != nullptr){
			scene->Cycle();
		}
	}
};

class WindowScene: public WindowDrawing, public WindowEvents{

};