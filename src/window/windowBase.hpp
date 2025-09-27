#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "scene/windowScene.hpp"
#include "data/position.hpp"
#include "data/flags.hpp"
#include "data/title.hpp"
#include "data/size.hpp"
#include "data/vsync.hpp"
#include "data/minSize.hpp"

class WindowBase: public WindowPosition, public WindowFlags, public WindowTitle, public WindowSize, public WindowVsync, public WindowMinSize{
	friend class Window;
	static inline const char* windowdataname = "Scene";

	SDL_GLContext glcon;
	SDL_Window* win;
	bool opened = false;

	void InitBackend();

protected:
	static WindowBase* GetWindowFromID(Uint32 id);

	void Apply();

public:
	void Select();

	void Open();
	void Close();
};