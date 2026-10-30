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
#include <FGengine/utils/timer.hpp>

export module Logic:Lock;

using FGengine::Utils::Timer;

namespace Logic{

	export class Lock{
	public:
		struct Range{
			Range(double center, double width):
				start{center - width/2},
				end{center + width/2}
			{
				if(start > 360){
					end -= 360;
				}
			}

			double start, end;

			bool IsInRange(double point) const{
				if(start > end){
					return point > start or point < end;
				}
				else{
					return point > start and point < end;
				}
			}
		};

		using AngleType = double;

		Lock(Range range, bool locked):
			locked{locked},
			range{range}
		{}

		void Update(){
			keyAngle += rotationSpeed*timer.GetTime();
			timer.Reset();
			if(keyAngle > 360){
				keyAngle -= 360;
			}
		}

		bool TryUnlock(){
			if(range.IsInRange(keyAngle)){
				locked = false;
				return true;
			}
			else{
				return false;
			}
		}

		void SetRange(const Range& newRange){
			range = newRange;
		}

		const Range& GetRange() const{
			return range;
		}

		bool IsLocked() const{
			return locked;
		}

		void Block(){
			locked = true;
		}

		AngleType GetKeyAngle() const{
			return keyAngle;
		}

		void SetKeyAngle(AngleType newKeyAngle){
			keyAngle = newKeyAngle;
		}

	private:
		Range range;
		bool locked;
		AngleType keyAngle = 0;
		double rotationSpeed = 45;
		Timer timer;
	};

}
