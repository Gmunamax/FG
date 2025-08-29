#pragma once
#include "models/cube.hpp"
#include "models/floor.hpp"
#include "objects/camera.hpp"
#include "mechanics/walk.hpp"
#include "mechanics/camRotation.hpp"
#include "config.hpp"
#include "main/drawing.hpp"
#include "config.hpp"
#include "scene.hpp"

class Scene1 : virtual public Scene, public CamRotation, public Walking{

	Model3d cube;
	Model3d floor;

	virtual void Loading(Window* window) override{
		win = window;
		
		#ifdef DEBUG
		std::cout << "Loading scene" << std::endl;
		#endif

		floor.Load(Floor::Load());
		floor.SetPosition({0,0,-1});

		cam.Resize({0,0,WINDOWW,WINDOWH});
		cam.SetFrustum();
		SetRotationKeys(SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT);
		WalkSetKeys(SDLK_w,SDLK_s,SDLK_a,SDLK_d);

		#ifdef DEBUG
		std::cout << "Done" << std::endl;
		#endif
	}

	virtual void Drawing() override{
		floor.Draw();
	}
	virtual void Cycle() override{
		CamRotationMove();
		WalkMove();
	}

	virtual void KeyPressed(SDL_KeyboardEvent& key) override{
		CamRotationStart(key);
		WalkStart(key);
		if(key.keysym.sym == SDLK_b){
			States::run = false;
		}
	}

	virtual void KeyReleased(SDL_KeyboardEvent& key) override{
		CamRotationEnd(key);
		WalkEnd(key);
	}

	Scene1() {}
	~Scene1(){
		FastLog("Scene1 Destr");
	}

public:
	static Scene1* New(){
		return new Scene1{};
	}
	void Deleting() override{
		delete this;
	}
};



// Those things should be remade in new scene

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