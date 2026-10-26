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
#include <cstdint>
#include <print>

module Night1;

using namespace Night1;

namespace {

	int_fast8_t ConvertNumberKeyToNumber(EventsPack::Key key){
		unsigned number;
		switch(key){
		using enum EventsPack::Key;
		case Num1:
			number = 1;
			break;
		
		case Num2:
			number = 2;
			break;

		case Num3:
			number = 3;
			break;

		case Num4:
			number = 4;
			break;

		case Num5:
			number = 5;
			break;

		case Num6:
			number = 6;
			break;

		case Num7:
			number = 7;
			break;

		case Num8:
			number = 8;
			break;

		case Num9:
			number = 9;
			break;

		case Num0:
			number = 0;
			break;

		default:
			number = -1;
			break;
		}
		return number;
	}

}

void Scene::HandleBoardNumberKey(Key key){
	auto number = ConvertNumberKeyToNumber(key);
	if(number == -1) return;
	if(number == 0) number = 10;
	auto id = number-1;
	
	auto& breaker = board.breakers[id];
	breaker.SetTriggered(!breaker.IsTriggered());
	std::println("breaker {}: trigger became {}", number, breaker.IsTriggered());
}
