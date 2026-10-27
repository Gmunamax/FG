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
#include <FGengine/videoOutput/window.hpp>
#include <FGengine/graphics/context.hpp>

export module Night1;
import Logic;

using FGengine::VideoOutput::Window, FGengine::VideoOutput::EventsPack;
using namespace Logic;

namespace Night1{

	export class Scene: public EventsPack{

		virtual void KeyPress(Key key) override{
			switch(interactionsFocus){
			using enum InteractionsTarget;
			case World:
				HandleWorldKeyPress(key);
				break;

			case DistributionBoard:
				HandleBoardKeyPress(key);
				break;
			
			case FusesBoard:
				HandleFuseKeyPress(key);
				break;
			}
		}

		void HandleWorldKeyPress(Key key);

		void HandleBoardKeyPress(Key key);
		void HandleBoardNumberKey(Key key);

		void HandleFuseKeyPress(Key key);
		void HandleFuseNumberKey(Key key);

		virtual void KeyRelease(Key key) override{
			switch(interactionsFocus){
			using enum InteractionsTarget;
			case World:
				HandleWorldKeyRelease(key);
				break;
			
			case DistributionBoard:
				// noop
				break;
			
			case FusesBoard:
				// noop
				break;
			}
		}

		void HandleWorldKeyRelease(Key key);

		virtual void Draw() override{
			FGengine::Graphics::Context::GetCurrentWindow().Clear();
			tb1.Update();
			player.Update();
			win->Update();
		}

	public:
		Scene(Window* win):
			win{win}
		{
			// tb1.SetPosition({0, 3, 0});
			player.SetRotation({90, 0, 0});
		}
		
	private:
		TB1ai tb1{&door, &time};
		// Office office;
		Door door;
		DistributionBoard board{
			true, true,
			true, true,
			true, true,
			true, true,
			true, true
		};
		FusesBoard fusesBoard{
			false, false,
			false, false,
			true, false,
			false, false,
			false, false
		};
		Player player;
		Time time{7*60};

		enum class InteractionsTarget{
			World,
			DistributionBoard,
			FusesBoard
		} interactionsFocus = InteractionsTarget::World;
		Window* win;

	};

}
