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
	double frametime;
	Uint8 frameskip = 0;

	double stepsize;

	int frames = 0;
	std::chrono::time_point<std::chrono::steady_clock> secs;

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point t2;
protected:

	WindowDrawing(){}

	void Draw(){
		if(frameskip <= 0){
			if(needupdate){

				t1 = std::chrono::steady_clock::now();

				glPushMatrix();
				GetScene()->cam.StartDrawing();
				GetScene()->Drawing();
				glPopMatrix();
				SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

				t2 = std::chrono::steady_clock::now();
				std::chrono::nanoseconds t = (t2 - t1);


				needupdate = false;

				glFlush();

				// if(std::chrono::time_point_cast<std::chrono::seconds>(t2) != secs){
				// 	secs = std::chrono::time_point_cast<std::chrono::seconds>(t2);
				// 	// Log(std::string{});
				// 	std::cout << SDL_GetWindowTitle(SDL_GL_GetCurrentWindow()) << "\n";
				// 	std::cout << frames << std::endl;
				// 	frames = 0;
				// }
				frameskip = std::chrono::duration_cast<std::chrono::milliseconds>(t).count()/frametime;

				long long f = (frametime *1000 *1000); //nanoseconds
				stepsize = ((double)t.count()/frametime)*(frameskip+1);
				stepsize = stepsize /1000 /1000; //to miliseconds

				/* to avoid false positives */
				if(frameskip == 1)
					frameskip = 0;

				frames++;
			}
		}
		else{
			std::cout << "Frameskip: " << (int)frameskip << " left\n" << std::endl;
			frameskip--;
		}
	}

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