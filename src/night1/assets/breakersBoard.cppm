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
#include <array>

export module Assets:BreakersBoard;
import Graphics;
import Logic;

namespace Night1::Assets{

	export class BreakersBoard{
	public:
		BreakersBoard(std::array<bool, 10> breakers):
			logic{breakers},
			graphics{breakers}
		{}

		void SetActivated(unsigned breaker, bool newState){
			graphics.SetActivated(breaker, newState);
			logic.SetElement(breaker, newState);
		}

		bool GetActivated(unsigned breaker){
			return logic.GetElement(breaker);
		}

	private:
		Logic::Board logic;
		Graphics::BreakersBoard graphics;
	};

}
