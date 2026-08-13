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
#include <SDL2/SDL_video.h>
#include "FGengine/backend/window.hpp"

namespace FGengine{

#define GetSdlHandle (SDL_Window*)GetHandle

namespace Backend{

	Window::Window(TitleType title, SizeType size): Handle(SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.w, size.h, SDL_WINDOW_OPENGL)) {}

	void Window::Update(){
		SDL_GL_SwapWindow(GetSdlHandle());
	}

	void Window::Destroy(){
		if(GetHandle() != nullptr)
			SDL_DestroyWindow(GetSdlHandle());
	}

	void Window::SetPosition(PositionType newPosition){
		SDL_SetWindowPosition(GetSdlHandle(), newPosition.x, newPosition.y);
	}

	Window::PositionType Window::GetPosition() const{
		PositionType position;
		SDL_GetWindowPosition(GetSdlHandle(), &position.x, &position.y);
		return position;
	}

	void Window::SetTitle(TitleType newTitle){
		SDL_SetWindowTitle(GetSdlHandle(), newTitle);
	}

	Window::TitleType Window::GetTitle() const{
		return SDL_GetWindowTitle(GetSdlHandle());
	}

	void Window::SetSize(SizeType newSize){
		SDL_SetWindowSize(GetSdlHandle(), newSize.w, newSize.h);
	}

	Window::SizeType Window::GetSize() const{
		SizeType size;
		SDL_GetWindowSize(GetSdlHandle(), &size.w, &size.h);
		return size;
	}

	void Window::SetMinimumSize(MinimumSizeType newMinSize){
		SDL_SetWindowMinimumSize(GetSdlHandle(), newMinSize.w, newMinSize.h);
	}

	Window::MinimumSizeType Window::GetMinimumSize() const{
		MinimumSizeType minSize;
		SDL_GetWindowMinimumSize(GetSdlHandle(), &minSize.w, &minSize.h);
		return minSize;
	}

}

}
