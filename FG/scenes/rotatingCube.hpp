#include <iostream>
#include <vector>
#include "FGengine/FGengine.hpp"
#include "FG/models/cube.hpp"
#include "FGengine/scene/scene.hpp"

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
	bool linesxray = false;

	virtual void Drawing() override{
		cube.Draw();
	}

	virtual void Loading(Window* w) override{
		win = w;

		cam.SetFrustum();

		cube.Load(Cube::Load());
		cube.SetPosition({0,0,-10});
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
	static Scene2* New(){
		return new Scene2{};
	}
	void Delete(){
		delete this;
	}
};