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
#include <span>
#include <memory>
#include <stack>

export module Night1;
import :FocusManager;
import :BreakersBoard;
import :FusesBoard;
import :World;
import Logic;

using FGengine::VideoOutput::Window, FGengine::VideoOutput::EventsPack;
using namespace Logic;

namespace Night1{

	export class Scene: public EventsPack{

		virtual void KeyPress(Key key) override{
			focus.Get()->KeyPress(key);
		}

		virtual void KeyRelease(Key key) override{
			focus.Get()->KeyRelease(key);
		}

		virtual void Draw() override{
			FGengine::Graphics::Context::GetCurrentWindow().Clear();
			tb1.Update();
			player.Update();
			focus.Get()->Draw();
			win->Update();
		}

	public:
		Scene(Window* win):
			win{win}
		{
			// tb1.SetPosition({0, 3, 0});
			player.SetRotation({90, 0, 0});
		}
		
	private:
		TB1ai tb1{&door, &time};
		// Office office;
		Door door;
		Player player;
		Time time{7*60};

		static inline constexpr bool breakers[]{
			true, true,
			true, true,
			true, true,
			true, true,
			true, true
		};
		static inline constexpr bool fuses[]{
			false, false,
			false, false,
			true, false,
			false, false,
			false, false
		};
		Electricity electricity{breakers, fuses};
		BreakersBoard breakersBoard{electricity, focus};
		FusesBoard fusesBoard{electricity, focus};
		World world{door, electricity, breakersBoard, fusesBoard, focus};

		FocusManager focus{&world};
		Window* win;
	};

}
