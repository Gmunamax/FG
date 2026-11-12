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

export module Assets:Breaker;
import Graphics;
import Logic;

namespace Night1::Assets{

	export class BreakersBoard{
	public:
		BreakersBoard(Logic::Electricity& electricity):
			electricity{&electricity},
			breakers{electricity.GetCircuit(0).breaker}
		{}

		void SetActivated(unsigned breaker, bool newState){
			breakers.at(breaker).SetActivated(newState);
			electricity.GetCircuit(breaker).breaker = newState;
		}

	private:
		Logic::Electricity* electricity;
		std::array<Graphics::Breaker, 10> breakers;

	};

}
