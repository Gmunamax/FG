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
#include <FGengine/window.hpp>
#include <FGengine/context.hpp>

struct FGengineFixture{

	class Window: public FGengine::Window{
	public:
		Window(TitleType title, SizeType size): FGengine::Window(title, size){
			TestCreation();
		}

	private:
		void TestCreation();
	}
	win{"FGengine tests", {800, 600}};

	class Context: public FGengine::Context{
	public:
		Context(const FGengine::Backend::Window& win): FGengine::Context(win){
			TestCreation();
		}

	private:
		void TestCreation();
	}
	ctx{win};
};
