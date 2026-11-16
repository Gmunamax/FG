// FG - a horror game
// Copyright (C) 2026 Gmunamax <https://github.com/Gmunamax/FG>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
module;
#include <FGengine/videoOutput/eventsPack.hpp>
#include <FGengine/videoOutput/window.hpp>
#include <FGengine/graphics/context.hpp>

export module Night1;
import :FocusManager;
import :BreakersBoard;
import :FusesBoard;
import :WorldFocus;
import :World;

using FGengine::VideoOutput::Window, FGengine::VideoOutput::EventsPack;

namespace Night1{

	export class Scene: public EventsPack{

		virtual void KeyPress(Key key) override{
			focus.Get()->KeyPress(key);
		}

		virtual void KeyRelease(Key key) override{
			focus.Get()->KeyRelease(key);
		}

		virtual void Draw() override{
			FGengine::Graphics::Context::GetCurrentContext().GetCurrentWindowViewport().Clear();
			world.door.Update();
			world.tb1.Update();
			world.player.Update();
			focus.Get()->Draw();
			win->Update();
		}

	public:
		Scene(Window* win):
			win{win}
		{}
		
	private:
		World world;

		Focus::BreakersBoard breakersBoard{world, focus};
		Focus::FusesBoard fusesBoard{world, focus};
		Focus::World worldFocus{world, breakersBoard, fusesBoard, focus};

		FocusManager focus{&worldFocus};
		Window* win;
	};

}
