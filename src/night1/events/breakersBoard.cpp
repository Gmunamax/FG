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

void Scene::HandleBreakersKeyPress(Key key){
	switch(key){
	using enum Key;
	case Esc:
		interactionsFocus = InteractionsTarget::World;
		break;
	default:
		HandleBreakersNumberKey(key);
		break;
	}
}

void Scene::HandleBreakersNumberKey(Key key){
	auto number = ConvertNumberKeyToNumber(key);
	if(number == -1) return;
	if(number == 0) number = 10;
	auto id = number-1;
	
	electricity.GetCircuit(id).breaker = !electricity.GetCircuit(id).breaker;
	const char* stateWord;
	if(electricity.GetCircuit(id).breaker == true){
		stateWord = "enabled";
	}
	else{
		stateWord = "disabled";
	}
	std::println("breaker {}: trigger became {}", number, stateWord);
}
