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
#include <array>

export module Night1:BreakersBoard;
import :FocusManager;
import Logic;
import Assets;

using FGengine::VideoOutput::EventsPack;
using Logic::Lock;

namespace Night1{

	class BreakersBoard final: public EventsPack{
	public:
		BreakersBoard(FocusManager& focusManager):
			focus{&focusManager},
			board{breakers}
		{}

		bool IsWorking(){
			bool working = true;
			for(std::size_t i = 0; i < 10; ++i){
				working = working & board.GetActivated(i);
			}
			return working;
		}

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
		static inline constexpr std::array<bool, 10> breakers{
			true, true,
			true, true,
			true, true,
			true, true,
			true, true
		};

		void HandleBreakersLockKeyPress(Key key);
		void HandleBreakersKeyPress(Key key);
		void HandleBreakersNumberKey(Key key);

		Lock breakersLock{{90, 35}, true};
		Assets::BreakersBoard board{breakers};
		FocusManager* focus;
	};

}
