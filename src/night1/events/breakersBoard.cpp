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
#include <print>

module Night1;
import :SomeThings;

using namespace Night1;

void Focus::BreakersBoard::HandleBreakersLockKeyPress(Key key){
	switch(key){
	using enum Key;
	case Space:
		breakersLock.TryUnlock();
		DrawSimpleKeyVisualization(breakersLock);
		break;

	case Esc:
		focus->Leave();
		break;

	default:
		std::println("Board is locked");
		break;
	}
}

void Focus::BreakersBoard::HandleBreakersKeyPress(Key key){
	switch(key){
	using enum Key;
	case Esc:
		focus->Leave();
		break;
	default:
		HandleBreakersNumberKey(key);
		break;
	}
}

void Focus::BreakersBoard::HandleBreakersNumberKey(Key key){
	auto number = ConvertNumberKeyToNumber(key);
	if(number == -1) return;
	if(number == 0) number = 10;
	auto id = number-1;
	
	world->breakersBoard.SetActivated(id, !world->breakersBoard.GetActivated(id));
	const char* stateWord;
	if(world->breakersBoard.GetActivated(id) == true){
		stateWord = "enabled";
	}
	else{
		stateWord = "disabled";
	}
	std::println("breaker {}: trigger became {}", number, stateWord);
}
