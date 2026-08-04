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
#pragma once
#include "window.hpp"
#include "handle.hpp"

namespace FGengine{

namespace Backend{

	class GLContext: private Handle{
	public:
		enum class VSyncModes{
			Off = 0,
			On = 1,
			Adaptive = -1
		};

		GLContext(const Window&);
		GLContext(const GLContext&) = delete;
		GLContext(GLContext&&) = default;
		~GLContext(){
			Destroy();
		}

		GLContext& operator=(const GLContext&) = delete;
		GLContext& operator=(GLContext&& context){
			if(&context != this){
				Destroy();
				Handle::operator=(std::move(context));
			}
			return *this;
		}

		using Proc = void(*)(void);
		static Proc GetProcAddress(const char* procName);

		void MakeCurrent(const Window& window);
		void MakeCurrent();

		static void SetVSyncMode(VSyncModes mode);
		static VSyncModes GetVSyncMode();
	
	private:
		void Destroy();
		friend struct Internal;
	};

}

}
