#include <iostream>
#include <vector>
#include "FGengine/FGengine.hpp"
#include "FG/models/cube.hpp"
#include "FGengine/scene/scene.hpp"

class RotatingCube: public Scene{
	std::vector<Point3d> vv2 = {
		{-0.9,1,-1},
		{1,1,-1},
		{0,0,-1},

		{-0.9,-1,-1},
		{1,-1,-1},
		{0,0,-1}
	};

	Model cube;
	bool linesxray = false;

	virtual void Drawing() override{
		cube.Draw();
	}

	virtual void Loading(Window* w) override{
		win = w;

		cam.SetFrustum();

		cube.Load(Cube::Load());
		cube.SetPosition({0,0,-3});
	}

	virtual void KeyPressed(SDL_KeyboardEvent& key) override{
		switch (key.keysym.sym) {
		case SDLK_r:
			linesxray = !linesxray;
				if(linesxray)
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				win->Update();
			break;
		}
	}

	Point3d& r = cube.GetRotation();

	virtual void Cycle() override{
		r.x++;
		r.y++;
		win->Update();
	}

	virtual void Deleting() override{
		Delete();
	}

public:
	static RotatingCube* New(){
		return new RotatingCube{};
	}
	void Delete(){
		delete this;
	}
};