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

export module Graphics:FusesBoard;
import Models;

namespace Graphics{

	export class FusesBoard{
	public:
		FusesBoard(std::array<bool, 10> fusesStates):
			fuses{fusesStates}
		{
			fuses.GetTransform().SetPosition({0, 5, 0});
		}

		void Draw(){
			fuses.Update();
		}

		void SetFixed(unsigned breaker, bool newState){
			fuses.SetActivated(breaker, newState);
		}

	private:
		Models::FusesArray fuses;

	};

}
