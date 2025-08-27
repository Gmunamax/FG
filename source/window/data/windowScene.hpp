#pragma once
#include <SDL2/SDL.h>
#include <chrono>
#include "scenes/scene.hpp"
#include "various/loging.hpp"

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
		if(scene == nullptr){
			Log("Bad scene pointer");
		}
	}

};

class WindowDrawing: virtual public WindowSceneCore{
	float frametime;
	Uint8 frameskip = 0;
protected:

	WindowDrawing(){}

	void Draw(){
		if(frameskip <= 0){
			if(needupdate){
				std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

				GetScene()->cam.StartDrawing();
				GetScene()->Drawing();
				SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
				//needupdate = false;

				std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

				auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
				frameskip = t.count()/frametime;
				if(frameskip == 1)
					frameskip--; /* to avoid false positives */
			}
		}
		else{
			FastLog("Frameskip: " + std::string{(char)frameskip} + " left\n");
			frameskip--;
		}
	}

public:
	

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
	// void EventPlacing(){
	// 	if(scene != nullptr){
	// 		scene->Placing();
	// 	}
	// }
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