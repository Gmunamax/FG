#pragma once
#include "models/cube.hpp"
#include "models/floor.hpp"
#include "objects/camera.hpp"
// #include "mechanics/walk.hpp"
// #include "mechanics/camRotation.hpp"
#include "config.hpp"
#include "main/drawing.hpp"
#include "config.hpp"
#include "scene.hpp"

class Scene1 : public Scene{

	Model3d cube;
	Model3d floor;

	virtual void Loading(Window* window) override{
		win = window;
		
		#ifdef DEBUG
		std::cout << "Loading scene" << std::endl;
		#endif

		floor.Load(Floor::Load());
		cube.Load(Cube::Load());

		cam.Resize({0,0,WINDOWW,WINDOWH});
		cam.SetFrustum();

		#ifdef DEBUG
		std::cout << "Done" << std::endl;
		#endif
	}

	virtual void Drawing() override{
		floor.Draw();
 		cube.Draw();
	}

	virtual void Closing() override{
		
	}

	virtual void KeyPressed(SDL_KeyboardEvent key) override{
		if(key.keysym.sym == SDLK_b){
			States::run = false;
		}
	}

	Scene1() {}
	~Scene1(){
		FastLog("Scene1 Destr");
	}
public:
	static Scene1* New(){
		return new Scene1{};
	}
	void Delete() override{
		delete this;
	}
};

// namespace Scene1{

// 	Window* win;
// 	Camera cam;
// 	Model3d cube;
// 	Model3d floor;

// 	bool rotatex = false;
// 	bool rotatey = false;
// 	bool rotatez = false;

// 	void DrawScene(){

// 		Point3d& cuberotation = cube.GetRotation();
// 		if(rotatex){
// 			cuberotation.x++;
// 			if(cuberotation.x == 360)
// 				cuberotation.x = 0;
// 			win->Update();
// 		}
// 		if(rotatey){
// 			cuberotation.y++;
// 			if(cuberotation.y == 360)
// 				cuberotation.y = 0;
// 			win->Update();
// 		}
// 		if(rotatez){
// 			cuberotation.z++;
// 			if(cuberotation.z == 360)
// 				cuberotation.z = 0;
// 			win->Update();
// 		}
// 		floor.Draw();
// 		cube.Draw();
// 	}


// 	void LoadScene(){

// 		#ifdef DEBUG
// 		std::cout << "Loading scene" << std::endl;
// 		#endif

// 		floor.Load(Floor::Load());
// 		//cube.Load(Cube::Load());

// 		cam.Resize({0,0,WINDOWW,WINDOWH});
// 		cam.SetFrustum();

// 		#ifdef DEBUG
// 		std::cout << "Done" << std::endl;
// 		#endif
// 	}

// 	void PlaceScene(){
// 		using namespace States;

// 		#ifdef DEBUG
// 		std::cout << "Placing scene" << std::endl;
// 		#endif

// 		cam.SetPosition({0,0,0});
// 		cube.SetPosition({0,0,-1});

// 		// forwardkey = SDLK_w;
// 		// backwardkey = SDLK_s;
// 		// leftkey = SDLK_a;
// 		// rightkey = SDLK_d;

// 		// lookupkey = SDLK_UP;
// 		// lookdownkey = SDLK_DOWN;
// 		// lookleftkey = SDLK_LEFT;
// 		// lookrightkey = SDLK_RIGHT;

// 		win->SetScene(&cam, DrawScene);

// 		Scene1::floor.SetPosition({
// 			-Floor::cellcountw * Floor::cellsize / 2,
// 			-Floor::cellcounth * Floor::cellsize / 2,
// 			-1
// 		});

// 		#ifdef DEBUG
// 		std::cout << "Done" << std::endl;
// 		#endif
// 	}

// 	void KeyPressed(SDL_KeyboardEvent& key){

// 		using namespace States;
// 		switch (key.keysym.sym){
// 		case SDLK_b:
// 			run = false;
// 			break;
// 		case SDLK_1:
// 			rotatex = !rotatex;
// 			break;
// 		case SDLK_2:
// 			rotatey = !rotatey;
// 			break;
// 		case SDLK_3:
// 			rotatez = !rotatez;
// 			break;

// 		case SDLK_v:
// 			vsync = !vsync;
// 			break;


// 		case SDLK_F11:
// 			if(win->GetID() == key.windowID){
// 				static bool fullscreen = false;
// 				if(fullscreen){
// 					win->EnterFullscreen();
// 					SDL_ShowCursor(SDL_DISABLE);
// 				}
// 				else{ 
// 					win->ExitFullscreen();
// 					SDL_ShowCursor(SDL_ENABLE);
// 				}
// 				break;
// 			}

// 		case SDLK_i:
// 			// speed+=0.1;
// 			break;
// 		case SDLK_o:
// 			// speed-=0.1;
// 			break;

// 		case SDLK_c:
// 			cam.SetFocusDistance(3);
// 			win->Update();
// 			break;
// 		case SDLK_r:
// 			linesxray = !linesxray;
// 			if(linesxray)
// 				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
// 			else
// 				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// 			win->Update();
// 			break;
// 		default:
// 			break;
// 		}

// 	}

// 	void KeyReleased(SDL_KeyboardEvent& key){
// 		using namespace States;

// 		switch (key.keysym.sym){
// 		case SDLK_c:
// 			cam.SetFocusDistance(1.1);
// 			win->Update();
// 			break;
// 		}
// 	}

// 	void Cycle(){
// 		// Walk();
// 		// lookAround();
// 	}

	
// 	void Scene1(Window* w){
// 		using namespace States;

// 		win = w;
// 		LoadScene();
// 		win->SetScene(&cam,DrawScene);
// 		win->onsceneloading = PlaceScene;
// 		//onclosingscene = [](){};
// 		oncycle = Cycle;
// 		onkeypressed = KeyPressed;
// 		onkeyreleased = KeyReleased;
// 	}
// }