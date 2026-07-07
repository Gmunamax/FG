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
#include "FGengine/special/window.hpp"
#include "./windowdatanames.hpp"

namespace FGengine{

void Window::UseFramebuffer(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::Select(){
	if(opened){
		SDL_GL_MakeCurrent(win,glcon);
	}
}

void Window::Open(){
	if(not opened){
		win = SDL_CreateWindow(GetTitle().c_str(), GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, GetSDLFlags());
		if(win == nullptr){
			throw SDL_GetError();
		}

		glcon = SDL_GL_CreateContext(win);
		if(glcon == nullptr){
			throw SDL_GetError();
		}

		GLenum glewres = glewInit();
		if(glewres != GLEW_OK){
			throw glewGetErrorString(glewres);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		glDepthRange(0.5,100);

		SDL_SetWindowData(win, WindowDataNames::thisclasspointer, this);
		if(scene != nullptr)
			scene->Load();
		opened = true;
	}
}

void Window::Close(){
	if(opened){
		SDL_GL_DeleteContext(glcon);
		SDL_DestroyWindow(win);
		opened = false;
	}
}

void Window::CloseAll(){
	for(Window* w : allwindows){
		w->Close();
	}
}


Window::Window(TitleType title, SizeType size): Backend::Window(title, size), scene(Defaults::scene), t1(std::chrono::steady_clock::now()){
	allwindows.emplace_front(this);
	elementBeforeThisInList = allwindows.before_begin();
	SetBuffersToClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

Window::~Window(){
	Close();
	allwindows.erase_after(elementBeforeThisInList);
}

}
