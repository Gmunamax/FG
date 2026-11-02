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

using namespace Night1;

void World::HandleWorldKeyPress(Key key){
	switch(key){
	using enum Key;
	case Space:
		door->SetClosed(true);
		break;

	case Num1:
		focus->Enter(breakersBoard);
		break;

	case Num2:
		focus->Enter(fusesBoard);
		break;

	default:
		break;
	}
}

void World::HandleWorldKeyRelease(Key key){
	switch(key){
	using enum Key;
	case Space:
		door->SetClosed(false);
		break;

	case B:
		if(electricity->IsWorking()){
			std::println("Congratulations");
		}
		else{
			std::println("Mission is not complete yet");
		}
	default:
		break;
	}
}
