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

export module Night1:FusesBoard;
import :FocusManager;
import Logic;
import Assets;

using Logic::Lock;

namespace Night1{

	class FusesBoard final: public EventsPack{
	public:
		FusesBoard(FocusManager& focusManager):
			focus{&focusManager}
		{}

		bool IsWorking(){
			bool working = true;
			for(std::size_t i = 0; i < 10; ++i){
				working = working && board.GetActivated(i);
			}
			return working;
		}

		void KeyPress(Key key) override{
			if(fusesLock.IsLocked()){
				HandleFusesLockKeyPress(key);
			}
			else{
				HandleFusesKeyPress(key);
			}
		}

		void KeyRelease(Key key) override{}

		void Draw() override{
			fusesLock.Update();
		}

	private:
		static inline constexpr std::array<bool, 10> fuses{
			false, false,
			false, false,
			true, false,
			false, false,
			false, false
		};

		void HandleFusesLockKeyPress(Key key);
		void HandleFusesKeyPress(Key key);
		void HandleFusesNumberKey(Key key);

		Lock fusesLock{{90, 45}, true};
		Assets::FusesBoard board{fuses};
		FocusManager* focus;
	};

}
