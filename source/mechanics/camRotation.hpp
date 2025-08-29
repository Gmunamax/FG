#pragma once
#include <SDL2/SDL.h>
#include "structures/point.hpp"
#include "objects/camera.hpp"
#include "scenes/scene.hpp"
#include "main/events.hpp"

class CamRotation: virtual public Scene{
private:
	bool rtup = false;
	bool rtdown = false;
	bool rtleft = false;
	bool rtright = false;
	bool lookmoving = false;

	SDL_KeyCode up;
	SDL_KeyCode down;
	SDL_KeyCode lookleftkey;
	SDL_KeyCode lookrightkey;

	float speed = 1;

	void UpdateFlags(SDL_KeyboardEvent& key, bool newval){
		if(key.keysym.sym == up){
			rtup = newval;
			std::cout << "up" ;
		}
		else if(key.keysym.sym == down){
			rtdown = newval;
			std::cout << "down";
		}
		else if(key.keysym.sym == lookleftkey){
			rtleft = newval;
			std::cout << "left";
		}
		else if(key.keysym.sym == lookrightkey){
			rtright = newval;
			std::cout << "right";
		}

		if(rtup or rtdown or rtleft or rtright){
			lookmoving = true;
			std::cout << "start";
		}
		else
			lookmoving = false;
	}
	

protected:
	CamRotation(){}

public:

	void SetRotationKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right){
		this->up = up;
		this->down = down;
		this->lookleftkey = left;
		this->lookrightkey = right;
	}

	void CamRotationStart(SDL_KeyboardEvent& key){
		UpdateFlags(key, true);
	}

	void CamRotationMove(){
		Point3d& rotation = cam.GetRotation();
		double step = win->GetStepCoefficient() * 180;
		//std::cout << win->GetStepCoefficient() << std::endl;

		if(lookmoving){

			if(rtup){
				rotation.x-=step;
				if(rotation.x < -180)
					rotation.x = -180;
			}
			if(rtdown){
				rotation.x+=step;
				if(rotation.x > 0)
				 	rotation.x = 0;

			}
			if(rtleft){
				std::cout << "-" << std::endl;
				rotation.z-=step;
				if(rotation.z < -180)
					rotation.z = 179;
			}
			if(rtright){
				std::cout << "+" << std::endl;
				rotation.z+=step;
				if(rotation.z > 180)
					rotation.z = -179;
			}

			win->Update();
			//std::cout << "{\n\t" << rotation.x << "\n\t" << rotation.y << "\n\t" << rotation.z << "\n" << "}";
		}
	}

	void CamRotationEnd(SDL_KeyboardEvent& key){
		UpdateFlags(key, false);
	}
	
};