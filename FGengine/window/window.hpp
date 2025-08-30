#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "windowBase.hpp"



class Window: public WindowBase{

	static inline std::vector<Window*> allwindows;
	std::vector<Window*>::size_type vectorpos;

	void AddSelf();

	void RemoveSelf();

public:

	Window();
	~Window();

	static void CloseAll();

	void Load();

	static void SendEvent(SDL_Event event);
	static void DrawAll();
};