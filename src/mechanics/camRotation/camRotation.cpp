#include <iostream>
#include "FGengine/structures/point.hpp"
#include "FGengine/objects/camera/camera.hpp"
#include "FGengine/window/window.hpp"
#include "camRotation.hpp"

void CamRotation::UpdateFlags(SDL_KeyboardEvent& key, bool newval){
	if(key.keysym.sym == up){
		rtup = newval;
	}
	else if(key.keysym.sym == down){
		rtdown = newval;
	}
	else if(key.keysym.sym == lookleftkey){
		rtleft = newval;
	}
	else if(key.keysym.sym == lookrightkey){
		rtright = newval;
	}

	if(rtup or rtdown or rtleft or rtright){
		lookmoving = true;
	}
	else
		lookmoving = false;
}

CamRotation::CamRotation() {}

void CamRotation::SetRotationKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right){
	this->up = up;
	this->down = down;
	this->lookleftkey = left;
	this->lookrightkey = right;
}

void CamRotation::CamRotationStart(SDL_KeyboardEvent& key){
	UpdateFlags(key, true);
}

void CamRotation::CamRotationMove(){
	Point3d& rotation = cam.GetRotation();
	double step = win->GetStepCoefficient() * 180;

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
			rotation.z-=step;
			if(rotation.z < -180)
				rotation.z = 179;
		}
		if(rtright){
			rotation.z+=step;
			if(rotation.z > 180)
				rotation.z = -179;
		}

		win->Update();
	}
}

void CamRotation::CamRotationEnd(SDL_KeyboardEvent& key){
	UpdateFlags(key, false);
}