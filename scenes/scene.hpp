#pragma once
#include "../models/cube.hpp"
#include "../models/floor.hpp"
#include "../objects/camera.hpp"
#include "../Walk.hpp"
#include "../config.hpp"
#include "../Main/drawing.hpp"

namespace Scene{

	using namespace States;

	Camera cam;
	Model3d cube;
	Model3d floor;

	bool rotatex = false;
	bool rotatey = false;
	bool rotatez = false;

	void LoadScene(){

		std::cout << "Loading scene" << std::endl;


		//auto t = ;
		floor.Load(Floor::Load());
		//cube.Load(Cube::Load());

		cam.Resize({0,0,WINDOWW,WINDOWH});
		cam.SetFrustum();
		States::currentcamera = &cam;

		std::cout << "Done" << std::endl;
	}

	void PlaceScene(){
		using namespace States;

		std::cout << "Placing scene" << std::endl;

		cam.SetPosition({0,0,0});
		cube.SetPosition({0,0,-1});
		States::currentcamera = &cam;

		forwardkey = SDLK_w;
		backwardkey = SDLK_s;
		leftkey = SDLK_a;
		rightkey = SDLK_d;

		lookupkey = SDLK_UP;
		lookdownkey = SDLK_DOWN;
		lookleftkey = SDLK_LEFT;
		lookrightkey = SDLK_RIGHT;

		

		Scene::floor.SetPosition({
			-Floor::cellcountw * Floor::cellsize / 2,
			-Floor::cellcounth * Floor::cellsize / 2,
			-1
		});

		std::cout << "Done" << std::endl;
	}

	void KeyPressed(SDL_KeyboardEvent& key){

		using namespace States;
		switch (key.keysym.sym){
		case SDLK_b:
			run = false;
			break;
		case SDLK_1:
			rotatex = !rotatex;
			break;
		case SDLK_2:
			rotatey = !rotatey;
			break;
		case SDLK_3:
			rotatez = !rotatez;
			break;

		case SDLK_v:
			vsync = !vsync;
			break;


		case SDLK_F11:
			fullscreen = !fullscreen;
			if(fullscreen){
				SDL_SetWindowFullscreen(win,SDL_WINDOW_FULLSCREEN_DESKTOP);
				SDL_ShowCursor(SDL_DISABLE);
			}
			else{ 
				SDL_SetWindowFullscreen(win,0);
				SDL_ShowCursor(SDL_ENABLE);
			}
			break;

		case SDLK_i:
			speed+=0.1;
			break;
		case SDLK_o:
			speed-=0.1;
			break;

		case SDLK_c:
			currentcamera->SetFocusDistance(3);
			needupdate = true;
			break;
		case SDLK_r:
			linesxray = !linesxray;
			if(linesxray)
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			needupdate = true;
			break;
		default:
			break;
		}

	}

	void KeyReleased(SDL_KeyboardEvent& key){
		using namespace States;

		switch (key.keysym.sym){
		case SDLK_c:
			currentcamera->SetFocusDistance(1.1);
			needupdate = true;
			break;
		}
	}

	void Cycle(){
		Walk();
		lookAround();
	}

	void DrawScene(){

		Point3d& cuberotation = cube.GetRotation();
		if(rotatex){
			cuberotation.x++;
			if(cuberotation.x == 360)
				cuberotation.x = 0;
			needupdate = true;
		}
		if(rotatey){
			cuberotation.y++;
			if(cuberotation.y == 360)
				cuberotation.y = 0;
			needupdate = true;
		}
		if(rotatez){
			cuberotation.z++;
			if(cuberotation.z == 360)
				cuberotation.z = 0;
			needupdate = true;
		}
		floor.Draw();
		cube.Draw();
	}

	void Scene(){
		using namespace States;

		LoadScene();
		onsceneloading = PlaceScene;
		onscenedrawing = DrawScene;
		onclosingscene = [](){};
		oncycle = Cycle;
		onkeypressed = KeyPressed;
		onkeyreleased = KeyReleased;
	}
}