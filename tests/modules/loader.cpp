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
#include <boost/test/unit_test.hpp>
#include <gl/gl.hpp>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

struct PfnsFixture{
public:
	PfnsFixture(){
		SDL_Init(SDL_INIT_VIDEO);
		win = SDL_CreateWindow("FGengine's OpenGL loader test", 320, 240, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
		ctx = SDL_GL_CreateContext(win);
		gladLoadGLContext(&pfns, SDL_GL_GetProcAddress);
	}
	~PfnsFixture(){
		SDL_GL_DestroyContext(ctx);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}

	GladGLContext pfns;

private:
	SDL_Window* win;
	SDL_GLContext ctx;
};

BOOST_FIXTURE_TEST_CASE(initialization, PfnsFixture){
	FGengine::SetCurrentPfns(pfns);
	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	BOOST_TEST(buffer != 0);
}
