#include <iostream>
#include <vector>
#include "objects/model/model.hpp"
#include "objects/camera.hpp"
#include "models/cube.hpp"
#include "scene.hpp"
// #include "mechanics/walk.hpp"
// #include "mechanics/camRotation.hpp"

class Scene2: public Scene{
	std::vector<Point3d> vv2 = {
		{-0.9,1,-1},
		{1,1,-1},
		{0,0,-1},

		{-0.9,-1,-1},
		{1,-1,-1},
		{0,0,-1}
	};

	Camera cam;
	Model3d cube;
	Window* win;

	virtual void Drawing() override{
		cube.Draw();
	}

	void Loading(Window* w){
		win = w;
		// States::lookupkey = SDLK_UP;
		// States::lookdownkey = SDLK_DOWN;
		// States::lookleftkey = SDLK_LEFT;
		// States::lookrightkey = SDLK_RIGHT;
		// States::forwardkey = SDLK_w;
		// States::backwardkey = SDLK_s;
		// States::leftkey = SDLK_a;
		// States::rightkey = SDLK_d;

		cam.Resize({0,0,WINDOWW,WINDOWH});
		cam.SetFrustum();

		cube.Load(Cube::Load());
	}

	virtual void Deleting() override{
		Delete();
	}

public:
	static Scene2* New(){
		return new Scene2{};
	}
	void Delete(){
		delete this;
	}

};