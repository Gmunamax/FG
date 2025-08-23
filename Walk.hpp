#pragma once
#include "structures/point.hpp"
#include "objects/camera.hpp"
#include "states.hpp"
#include <iostream>
#include <math.h>
#include "events.hpp"

//Why nobody didn't add this value to default definitions
#define degtorad 0.017453293

namespace States{

	bool walkw = false;
	SDL_KeyCode forwardkey;
	bool walka = false;
	SDL_KeyCode backwardkey;
	bool walks = false;
	SDL_KeyCode leftkey;
	bool walkd = false;
	SDL_KeyCode rightkey;

	bool rtup = false;
	SDL_KeyCode lookupkey;
	bool rtdown = false;
	SDL_KeyCode lookdownkey;
	bool rtleft = false;
	SDL_KeyCode lookleftkey;
	bool rtright = false;
	SDL_KeyCode lookrightkey;

	bool walkslide = false;
	double friction = 0;
	double startpower = 2;
	bool move2d = true;
	bool walkmoving = false;
	bool lookmoving = false;
	float speed = 0.1;
}

void lookAround(){
	using namespace States;

	if(currentcamera == nullptr){
		std::cout << "No active camera" << "\n";
		return;
	}

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

	Point3d& rotation = currentcamera->GetRotation();

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

		needupdate = true;
		//std::cout << "{\n\t" << rotation.x << "\n\t" << rotation.y << "\n\t" << rotation.z << "\n" << "}";
	}

}

Point3d MakeStep(){

	enum AxisRotators{
		MoveForward = 0,
		MoveLeft = 1,
		MoveBackward = 2,
		MoveRight = 3,
	};
	short axisangle = 90;
	
	using namespace States;
	double walkaxisrotation = 0;
	unsigned short keyspressed;

	static double fpower = 0;
	static double bpower = 0;
	static double lpower = 0;
	static double rpower = 0;

	static double realspeed = 0;
	//static Point2d movevector {0,0};

	if(walkslide){
		
	}
	else{
		//movevector = {0,0};

		fpower = walkw * speed;
		bpower = walks * speed;
		lpower = walka * speed;
		rpower = walkd * speed;

		realspeed = speed;
	}

	//TODO: разобрать управление всем по хедерам, намеспейсам, чтобы было модульно и основной цикл был чистенький.

	keyspressed+= walkw;
	keyspressed+= walks;
	keyspressed+= walka;
	keyspressed+= walkd;
	
	//std::cout << "[{\n\t " << walkw << "\n\t" << walka << walks << walkd << "\n}\n";

	Point3d movevector {
		(-1*lpower) + (1*rpower),
		(1*fpower) + (-1*bpower),
		0
	};

	// std::cout << "{\n\t" << movevector.x << "\n\t" << movevector.y << "\n}\n";

	// walkaxisrotation += walkw*MoveForward*axisangle;
	// walkaxisrotation += walks*MoveBackward*axisangle;
	// walkaxisrotation += walka*MoveLeft*axisangle;
	// walkaxisrotation += walkd*MoveRight*axisangle;

	// std::cout << walkaxisrotation << "\n";

	// walkaxisrotation = keyspressed == 0 ? 0 : walkaxisrotation/keyspressed;

	Point3d step{
		std::cos(currentcamera->GetRotation().z * degtorad) * movevector.x + std::sin(currentcamera->GetRotation().z * degtorad) * movevector.y,
		std::cos(currentcamera->GetRotation().z * degtorad) * movevector.y - std::sin(currentcamera->GetRotation().z * degtorad) * movevector.x,
		std::sin(currentcamera->GetRotation().x * degtorad) * movevector.z
	};

	double mx = movevector.x < 0? -movevector.x : movevector.x;
	double my = movevector.y < 0? -movevector.y : movevector.y;

	// bool f = mx > my ? true : false;
	// double m = f ? movevector.x : movevector.y;

	// std::cout << m << "\n";

	// double z = currentcamera->GetRotation().z;

	//std::cout << movevector.x << " / " << movevector.y << "\n";

	if(keyspressed == 0)
		walkmoving = false;
	
	
	return {-step.x,-step.y,0};
}

void Walk(){
	using namespace States;
	Point3d& position = currentcamera->GetPosition();

	if(currentcamera == nullptr) 
		return;

	bool newval;
	bool changeflags = false;
	if(currentevent.type == SDL_KEYDOWN){
		if(currentevent.key.repeat == 0){
			changeflags = true;
			newval = true;
		}
	}
	else if(currentevent.type == SDL_KEYUP){
		changeflags = true;
		newval = false;
	}

	if(changeflags){
		if(currentevent.key.keysym.sym == forwardkey)
			walkw = newval;
		else if(currentevent.key.keysym.sym == backwardkey)
			walks = newval;
		else if(currentevent.key.keysym.sym == leftkey)
			walka = newval;
		else if(currentevent.key.keysym.sym == rightkey)
			walkd = newval;
		if(walkw or walka or walks or walkd)
			walkmoving = true;
	}
	
	if(walkmoving){

		currentcamera->SetPosition(currentcamera->GetPosition() + MakeStep());
		// std::cout << "[\n\t" << currentcamera->GetPosition().x << "\n\t" << currentcamera->GetPosition().y << "\n]\n";
		needupdate = true;
	}
}