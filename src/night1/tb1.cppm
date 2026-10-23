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
#include "assets/tb1.hpp"

export module Night1:TB1;
import :TB1ai;

namespace Night1{

	class TB1{
	public:
		TB1(Door* door, Time* time):
			ai{door, time}
		{}

		void Update(){
			ai.Update();
			tb1.Draw();
		}

		void SetPosition(const glm::vec3& newPosition){
			tb1.SetPosition(newPosition);
		}

		const glm::vec3& GetPosition(){
			return tb1.GetPosition();
		}

	private:
		Assets::TB1 tb1;
		TB1ai ai;
	};

}
