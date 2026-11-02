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
#include <stack>

export module Night1:FocusManager;

using FGengine::VideoOutput::EventsPack;

namespace Night1{

	class FocusManager{
	public:
		using Pack = EventsPack*;

		FocusManager(Pack initialPack)
		{
			Enter(initialPack);
		}

		void Enter(Pack pack){
			stack.push(pack);
		}

		Pack& Get(){
			return stack.top();
		}

		void Leave(){
			stack.pop();
		}

	private:
		std::stack<Pack> stack;
	};

}
