#pragma once
#include "FGengine/FGengine.hpp"
#include "FGengine/mechanics/walking/walking.hpp"
#include "FGengine/mechanics/camRotation/camRotation.hpp"
#include "FG/models/cube.hpp"
#include "FG/models/floor.hpp"
#include "FG/config.hpp"

class Landspace : virtual public Scene, public CamRotation, public Walking{

	Model3d cube;
	Model3d floor;

	virtual void Loading(Window* window) override{
		win = window;
		
		floor.Load(Floor::Load());
		floor.SetPosition({0,0,-1});

		cam.SetFrustum();

		SetRotationKeys(SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT);
		WalkSetKeys(SDLK_w,SDLK_s,SDLK_a,SDLK_d);
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
			quit();
		}
	}

	virtual void KeyReleased(SDL_KeyboardEvent& key) override{
		CamRotationEnd(key);
		WalkEnd(key);
	}

	Landspace() {}
	~Landspace(){
		
	}

public:
	static Landspace* New(){
		return new Landspace{};
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