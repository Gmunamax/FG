#pragma once
#include <SDL2/SDL.h>
#include <engine/videoOutput/eventsPack.hpp>

class EventsWorker{
public:
	EventsWorker(EventsPack* starterPack){
		MakePackCurrent(starterPack);
	}

	void MakePackCurrent(EventsPack* starterPack){
		currentPack = starterPack;
	}

	void MainCycle(){
		bool run = true;
		SDL_Event event;
		while(run){
			while(SDL_PollEvent(&event)){
				if(event.type == SDL_QUIT){
					run = false;
				}
				else if(event.type == SDL_KEYDOWN){
					currentPack->KeyPress(SdlToKey(event.key.keysym.sym));
				}
				else if(event.type == SDL_KEYUP){
					currentPack->KeyRelease(SdlToKey(event.key.keysym.sym));
				}
			}
			currentPack->Draw();
		}
	}

private:
	EventsPack::Key SdlToKey(SDL_Keycode keycode){
		EventsPack::Key key;
		switch(keycode){
		case SDLK_w:
			key = EventsPack::Key::W;
			break;
		case SDLK_a:
			key = EventsPack::Key::A;
			break;
		case SDLK_s:
			key = EventsPack::Key::S;
			break;
		case SDLK_d:
			key = EventsPack::Key::D;
			break;
		case SDLK_UP:
			key = EventsPack::Key::Up;
			break;
		case SDLK_LEFT:
			key = EventsPack::Key::Left;
			break;
		case SDLK_DOWN:
			key = EventsPack::Key::Down;
			break;
		case SDLK_RIGHT:
			key = EventsPack::Key::Right;
			break;
		case SDLK_SPACE:
			key = EventsPack::Key::Space;
			break;
		case SDLK_b:
			key = EventsPack::Key::B;
			break;
		}
		return key;
	}
	EventsPack* currentPack;
};
