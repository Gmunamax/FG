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
#include <span>

export module Assets:FusesBoard;
import Logic;
import Graphics;

namespace Assets{

	export class FusesBoard{
	public:
		FusesBoard(std::span<const bool, 10> fuses):
			logic{fuses},
			graphics{fuses}
		{}

		void SetActivated(unsigned breaker, bool newState){
			logic.SetElement(breaker, newState);
			graphics.SetFixed(breaker, newState);
		}

		bool GetActivated(unsigned breaker){
			return logic.GetElement(breaker);
		}

		void Update(){
			graphics.Draw();
		}

	private:
		Logic::Board logic;
		Graphics::FusesBoard graphics;
	};

}
