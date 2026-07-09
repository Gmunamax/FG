// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#include "FGengine/main.hpp"
#include "special/defaults.hpp"

namespace FGengine{

static bool run = true;
static double cycletime = 0;

void quit(){
	run = false;
}

void setCycleRate(int hz){
	cycletime = 1.0f/hz * 1000;
}

static void quitOnEndOfMainCycle(){
	SDL_Quit();
}

void mainCycle(){

	while (run) {

		SDL_Delay(cycletime);
	}
	
	quitOnEndOfMainCycle();
}

void init(){
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	Defaults::init();
}

}
