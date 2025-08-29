#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "structures/point.hpp"
#include "objects/camera.hpp"
#include "scenes/scene.hpp"

//Why nobody didn't add this value to default definitions
#define degtorad 0.017453293

class Walking: virtual public Scene{

	bool walkw = false;
	bool walka = false;
	bool walks = false;
	bool walkd = false;
	bool walkmoving = false;

	SDL_KeyCode forwardkey;
	SDL_KeyCode backwardkey;
	SDL_KeyCode leftkey;
	SDL_KeyCode rightkey;

	bool walkslide = false;
	double friction = 0;
	double startpower = 2;
	bool move2d = true;
	float speed = 0.1;
	
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

		static double realspeed = win->GetStepCoefficient();
		//static Point2d movevector {0,0};

		if(walkslide){

		}
		else{
			//movevector = {0,0};

			fpower = walkw * speed;
			bpower = walks * speed;
			lpower = walka * speed;
			rpower = walkd * speed;

			realspeed = realspeed * speed;
		}

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
			std::cos(cam.GetRotation().z * degtorad) * movevector.x + std::sin(cam.GetRotation().z * degtorad) * movevector.y,
			std::cos(cam.GetRotation().z * degtorad) * movevector.y - std::sin(cam.GetRotation().z * degtorad) * movevector.x,
			std::sin(cam.GetRotation().x * degtorad) * movevector.z
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

	void UpdateFlags(SDL_KeyboardEvent& key, bool newval){
		if(key.keysym.sym == forwardkey)
			walkw = newval;
		else if(key.keysym.sym == backwardkey)
			walks = newval;
		else if(key.keysym.sym == leftkey)
			walka = newval;
		else if(key.keysym.sym == rightkey)
			walkd = newval;

		if(walkw or walka or walks or walkd)
			walkmoving = true;
	}

public:

	void WalkSetKeys(SDL_KeyCode forward, SDL_KeyCode backward, SDL_KeyCode left, SDL_KeyCode right){
		forwardkey = forward;
		backwardkey = backward;
		leftkey = left;
		rightkey = right;
	}
	void WalkStart(SDL_KeyboardEvent& key){
		UpdateFlags(key, true);
	}

	void WalkEnd(SDL_KeyboardEvent& key){
		UpdateFlags(key, false);
	}

	void WalkMove(){
		Point3d& position = cam.GetPosition();

		if(walkmoving){

			//double rs = win->GetStepCoefficient() * 0.03;
			cam.SetPosition(cam.GetPosition() + MakeStep());
			//std::cout << "[\n\t" << cam.GetPosition().x << "\n\t" << cam.GetPosition().y << "\n]\n";
			win->Update();
		}
	}
};