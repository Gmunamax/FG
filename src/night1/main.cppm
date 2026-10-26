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
import :Office;
import :TB1;
import :Player;
import :Door;
import :Time;
import :DistributionBoard;

using FGengine::VideoOutput::Window, FGengine::VideoOutput::EventsPack;

namespace Night1{

	export class Scene: public EventsPack{
		TB1 tb1{&door, &time};

		Office office;
		Door door;
		DistributionBoard board{
			true, true,
			true, true,
			true, true,
			true, true,
			true, true
		};
		enum class InteractionsTarget{
			World,
			DistributionBoard
		} interactionsFocus = InteractionsTarget::World;

		Player player;
		Time time{7*60};
		Window* win;

		virtual void Draw() override{
			FGengine::Graphics::Context::GetCurrentWindow().Clear();
			tb1.Update();
			player.Update();
			win->Update();
		}

		virtual void KeyPress(Key key) override{
			switch(interactionsFocus){
			using enum InteractionsTarget;
			case World:
				HandleWorldKeyPress(key);
				break;

			case DistributionBoard:
				HandleBoardKeyPress(key);
				break;
			}
		}

		void HandleWorldKeyPress(Key key){
			switch(key){
			using enum Key;
			case Space:
				door.SetClosed(true);
				break;

			case Num1:
				interactionsFocus = InteractionsTarget::DistributionBoard;
				break;

			default:
				break;
			}
		}

		void HandleBoardKeyPress(Key key){
			switch(key){
			using enum Key;
			case Esc:
				interactionsFocus = InteractionsTarget::World;
				break;
			default:
				HandleBoardNumberKey(key);
				break;
			}
		}

		void HandleBoardNumberKey(Key key);

		virtual void KeyRelease(Key key) override{
			switch(interactionsFocus){
			using enum InteractionsTarget;
			case World:
				HandleWorldKeyRelease(key);
				break;
			
			case DistributionBoard:
				HandleBoardKeyRelease(key);
				break;
			}
		}

		void HandleWorldKeyRelease(Key key){
			switch(key){
			using enum Key;
			case Space:
				door.SetClosed(false);
				break;

			default:
				break;
			}
		}

		void HandleBoardKeyRelease(Key key){
			
		}

	public:
		Scene(Window* win):
			win(win)
		{
			tb1.SetPosition({0, 3, 0});
			player.SetRotation({90, 0, 0});
		}
	};

}
