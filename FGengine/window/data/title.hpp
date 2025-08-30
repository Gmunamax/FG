#pragma once
#include <SDL2/SDL.h>
#include <string>

class WindowTitle{
	std::string title;
	bool needupdate = true;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(),title.c_str());
			needupdate = false;
		}
	}

public:
	void SetTitle(std::string newtitle){
		title = newtitle;
	}
	std::string GetTitle(){
		return title;
	}
};
