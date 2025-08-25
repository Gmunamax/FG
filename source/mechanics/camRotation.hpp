#pragma once
#include <SDL2/SDL.h>
#include "structures/point.hpp"
#include "objects/camera.hpp"
#include "scenes/scene.hpp"
#include "main/events.hpp"

class Walking : virtual public Scene{
private:
	bool rtup = false;
	bool rtdown = false;
	bool rtleft = false;
	bool rtright = false;
	bool lookmoving = false;

protected:
	Walking(){}

public:
	
	SDL_KeyCode lookupkey;
	SDL_KeyCode lookdownkey;
	SDL_KeyCode lookleftkey;
	SDL_KeyCode lookrightkey;

	void lookAround(){

		bool newval;
		bool changeflags = false;
		if(currentevent.type == SDL_KEYDOWN){
			changeflags = true;
			newval = true;
		}
		else if(currentevent.type == SDL_KEYUP){
			changeflags = true;
			newval = false;
		}

		if(changeflags){
			if(currentevent.key.keysym.sym == lookupkey)
				rtup = newval;
			else if(currentevent.key.keysym.sym == lookdownkey)
				rtdown = newval;
			else if(currentevent.key.keysym.sym == lookleftkey)
				rtleft = newval;
			else if(currentevent.key.keysym.sym == lookrightkey)
				rtright = newval;

			if(rtup or rtdown or rtleft or rtright)
				lookmoving = true;
			else
				lookmoving = false;
		}

		Point3d& rotation = cam.GetRotation();

		if(lookmoving){

			if(rtup){
				rotation.x--;
				if(rotation.x < -180)
					rotation.x = -180;
			}
			if(rtdown){			
				rotation.x++;
				if(rotation.x > 0)
				 	rotation.x = 0;

			}
			if(rtleft){
				rotation.z--;
				if(rotation.z < -180)
					rotation.z = 179;
			}
			if(rtright){
				rotation.z++;
				if(rotation.z > 180)
					rotation.z = -179;
			}

			win->Update();
			//std::cout << "{\n\t" << rotation.x << "\n\t" << rotation.y << "\n\t" << rotation.z << "\n" << "}";
		}

	}
	
}