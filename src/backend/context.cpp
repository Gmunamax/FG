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
#include <SDL3/SDL_video.h>
#include "FGengine/backend/context.hpp"
#include "handleControl.hpp"

namespace FGengine{

namespace Backend{

	GLContext::GLContext(const Window& win): Handle(SDL_GL_CreateContext((SDL_Window*)Internal::CastToHandle(win).GetHandle())) {}

	void GLContext::MakeCurrent(const Window& win){
		SDL_GL_MakeCurrent((SDL_Window*)Internal::CastToHandle(win).GetHandle(), (SDL_GLContext)GetHandle());
	}
	
	void GLContext::MakeCurrent(){
		SDL_GL_MakeCurrent(SDL_GL_GetCurrentWindow(), (SDL_GLContext)GetHandle());
	}

	GLContext::Proc GLContext::GetProcAddress(const char* procName){
		return (Proc)SDL_GL_GetProcAddress(procName);
	}
	
	void GLContext::Destroy(){
		if(GetHandle() != nullptr)
			SDL_GL_DestroyContext((SDL_GLContext)GetHandle());
	}

	void GLContext::SetVSyncMode(VSyncModes newVSyncMode){
		SDL_GL_SetSwapInterval((int)newVSyncMode);
	}

	GLContext::VSyncModes GLContext::GetVSyncMode(){
		int mode;
		SDL_GL_GetSwapInterval(&mode);
		return (VSyncModes)mode;
	}

}

}
