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
#include <print>

export module Logic:FusesBoard;
import :Fuse;
import :BreakersBoard;

namespace Logic{

	export class FusesBoard{
	public:
		FusesBoard(std::array<Fuse, 10> fuses, BreakersBoard* breakersBoard):
			fuses{fuses},
			breakersBoard{*breakersBoard}
		{}

		void TryFixFuse(unsigned id){
			if( not breakersBoard.breakers.at(id).IsTriggered()){
				fuses.at(id).Fix();
			}
			else{
				std::println("Disable breaker first");
			}
		}

		bool IsFuseWorking(unsigned id){
			return fuses.at(id).IsWorking();
		}

	private:
		std::array<Fuse, 10> fuses;
		BreakersBoard& breakersBoard;
	};

}
