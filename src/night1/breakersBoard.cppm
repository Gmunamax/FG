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

export module Night1:BreakersBoard;
import :FocusManager;
import Logic;

using FGengine::VideoOutput::EventsPack;
using Logic::Electricity, Logic::Lock;

namespace Night1{

	class BreakersBoard final: public EventsPack{
	public:
		BreakersBoard(Electricity& electricity, FocusManager& focusManager):
			electricity{&electricity},
			focus{&focusManager}
		{}

		void KeyPress(Key key) override{
			if(breakersLock.IsLocked()){
				HandleBreakersLockKeyPress(key);
			}
			else{
				HandleBreakersKeyPress(key);
			}
		}

		void KeyRelease(Key key) override{}

		void Draw() override{
			breakersLock.Update();
		}

	private:
		void HandleBreakersLockKeyPress(Key key);
		void HandleBreakersKeyPress(Key key);
		void HandleBreakersNumberKey(Key key);

		Lock breakersLock{{90, 35}, true};
		Electricity* electricity;
		FocusManager* focus;
	};

}
