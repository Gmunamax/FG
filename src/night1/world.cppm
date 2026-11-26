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
export module Night1:World;
import :Assets;
import Logic;

namespace Night1{

	using Assets::Door, Assets::TB1, Assets::Player;
	using Logic::Time;

	export struct World{
		Door door;
		Time time{7*60};
		TB1 tb1{door, time};
		// Office office;
		Player player;
		Assets::BreakersBoard breakersBoard;
		Assets::FusesBoard fusesBoard;
	};

}
