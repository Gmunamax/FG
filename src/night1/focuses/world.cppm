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

export module Night1:WorldFocus;
import :BreakersBoard;
import :FusesBoard;
import :FocusManager;
import :World;

using FGengine::VideoOutput::EventsPack;

namespace Night1::Focus{

	class World final: public EventsPack{
	public:
		World(::Night1::World& world, BreakersBoard& breakersBoard, FusesBoard& fusesBoard, FocusManager& focusManager):
			world{&world},
			breakersBoard{&breakersBoard},
			fusesBoard{&fusesBoard},
			focus{&focusManager}
		{}

		void KeyPress(Key key) override{
			HandleWorldKeyPress(key);
		}

		void KeyRelease(Key key) override{
			HandleWorldKeyRelease(key);
		}

		void Draw() override{}
		
	private:
		void HandleWorldKeyPress(Key key);
		void HandleWorldKeyRelease(Key key);

		::Night1::World* world;
		BreakersBoard* breakersBoard;
		FusesBoard* fusesBoard;
		FocusManager* focus;
	};

}
