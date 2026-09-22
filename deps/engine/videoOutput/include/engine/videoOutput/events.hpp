#pragma once
#include <SDL3/SDL.h>
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
				if(event.type == SDL_EVENT_QUIT){
					run = false;
				}
				else if(event.type == SDL_EVENT_KEY_DOWN){
					currentPack->KeyPress(SdlToKey(event.key.scancode));
				}
				else if(event.type == SDL_EVENT_KEY_UP){
					currentPack->KeyRelease(SdlToKey(event.key.scancode));
				}
			}
			currentPack->Draw();
		}
	}

private:
	EventsPack::Key SdlToKey(SDL_Scancode keycode){
		EventsPack::Key key;
		switch(keycode){
		case SDL_SCANCODE_W:
			key = EventsPack::Key::W;
			break;
		case SDL_SCANCODE_A:
			key = EventsPack::Key::A;
			break;
		case SDL_SCANCODE_S:
			key = EventsPack::Key::S;
			break;
		case SDL_SCANCODE_D:
			key = EventsPack::Key::D;
			break;
		case SDL_SCANCODE_UP:
			key = EventsPack::Key::Up;
			break;
		case SDL_SCANCODE_LEFT:
			key = EventsPack::Key::Left;
			break;
		case SDL_SCANCODE_DOWN:
			key = EventsPack::Key::Down;
			break;
		case SDL_SCANCODE_RIGHT:
			key = EventsPack::Key::Right;
			break;
		case SDL_SCANCODE_SPACE:
			key = EventsPack::Key::Space;
			break;
		case SDL_SCANCODE_RSHIFT:
			key = EventsPack::Key::Rshift;
			break;
		case SDL_SCANCODE_LSHIFT:
			key = EventsPack::Key::Lshift;
			break;
		case SDL_SCANCODE_B:
			key = EventsPack::Key::B;
			break;
		
		default:
			break;
		}
		return key;
	}
	EventsPack* currentPack;
};
