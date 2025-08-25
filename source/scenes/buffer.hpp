#include <iostream>
#include <vector>
#include "structures/point.hpp"
#include "objects/model/model.hpp"
#include "objects/camera.hpp"
#include "models/cube.hpp"
// #include "mechanics/walk.hpp"
// #include "mechanics/camRotation.hpp"

namespace BufferTests{
	std::vector<Point3d> vv2 = {
		{-0.9,1,-1},
		{1,1,-1},
		{0,0,-1},

		{-0.9,-1,-1},
		{1,-1,-1},
		{0,0,-1}
	};

	Camera cam;
	Model3d& cube = Scene1::cube;
	Window* win;

	void drawBuffer(){
		cube.Draw();
	}

	void buffer(Window* w){
		win = w;
		// States::lookupkey = SDLK_UP;
		// States::lookdownkey = SDLK_DOWN;
		// States::lookleftkey = SDLK_LEFT;
		// States::lookrightkey = SDLK_RIGHT;
		// States::forwardkey = SDLK_w;
		// States::backwardkey = SDLK_s;
		// States::leftkey = SDLK_a;
		// States::rightkey = SDLK_d;

		cube.Load(Cube::Load());
		w->SetScene(&cam, drawBuffer);
	}

	void delBuffers(){
		
	}
}