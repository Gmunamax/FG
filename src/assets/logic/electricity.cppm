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

export module Logic:Electricity;

namespace Logic{

	export class Electricity{
	public:
		struct Circuit{
			bool breaker :1;
			bool fuse :1;

			bool IsWorking(){
				return breaker && fuse;
			}
		};

		Electricity(std::span<const bool, 10> breakers, std::span<const bool, 10> fuses){
			for(unsigned i = 0; i < 10; ++i){
				circuits.at(i).breaker = breakers.at(i);
				circuits.at(i).fuse = fuses.at(i);
			}
		}

		bool IsWorking(){
			bool working = true;
			for(auto& circuit : circuits){
				working = working && circuit.IsWorking();
			}
			return working;
		}

		Circuit& GetCircuit(unsigned id){
			return circuits.at(id);
		}

	private:
		std::array<Circuit, 10> circuits;

	};

}
