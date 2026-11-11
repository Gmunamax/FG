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
export module Assets:Door;
import Logic;
import Graphics;

namespace Night1::Assets{

	export class Door{
	public:
		Door(){
		}

		Logic::Door& GetLogic(){
			return logic;
		}

		Graphics::Door& GetGraphics(){
			return model;
		}

		void SetClosed(bool newState){
			if(newState == true){
				logic.SetClosed(true);
				visible = true;
			}
			else{
				logic.SetClosed(false);
				visible = false;
			}
		}

		void Update(){
			if(visible){
				model.Draw();
			}
		}

	private:
		Logic::Door logic;
		Graphics::Door model;
		bool visible = logic.GetClosed();
	};

}
