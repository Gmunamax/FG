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
#include <FGengine/videoOutput/eventsPack.hpp>
#include <cstdint>
#include <print>

export module Night1:SomeThings;
import Logic;

using FGengine::VideoOutput::EventsPack, Logic::Lock;

namespace Night1{

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

	void DrawSimpleKeyVisualization(const Lock& lock){
		const unsigned width = 80;
		const char empty = '-';
		const char fill = '_';
		const char key = '|';

		unsigned angleOnWidth = 0;
		while(angleOnWidth < width){
			if(lock.GetKeyAngle() < ((360.0/width) * angleOnWidth+1)){
				break;
			}
			else{
				++angleOnWidth;
			}
		}

		const auto range = lock.GetKeyAngle();
		for(unsigned i = 0; i < width; ++i){
			const char* character;
			const Lock::AngleType currentAngle = (360.0/width) * i;

			if(lock.GetRange().IsInRange(currentAngle)){
				character = &fill;
			}
			else{
				character = &empty;
			}

			if(i == angleOnWidth){
				character = &key;
			}

			std::print("{}", *character);
		}
		std::println();
	}

}
