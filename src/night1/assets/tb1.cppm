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

export module Assets:TB1;
import :Door;
import Logic;
import Graphics;

namespace Night1::Assets{

	export class TB1{
	public:
		TB1(Door& door, Logic::Time& time):
			logic{&door.GetLogic(), &time}
		{
			model.SetPosition({0, 4, 0});
		}

		Logic::TB1ai& GetLogic(){
			return logic;
		}

		Graphics::TB1& GetGraphics(){
			return model;
		}

		void Update(){
			logic.Update();
			if(logic.GetState() == Logic::TB1ai::State::Attacking){
				model.Draw();
			}
		}

	private:
		Logic::TB1ai logic;
		Graphics::TB1 model;
	};

}
