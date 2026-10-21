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

using FGengine::VideoOutput::Window, FGengine::VideoOutput::EventsPack;

namespace Night1{

	export class Scene: public EventsPack{
		TB1 tb1{&door, &time};

		Office office;
		Door door;

		Player player;
		Time time{7*60};
		Window* win;

		virtual void Draw(){
			FGengine::Graphics::Context::GetCurrentWindow().Clear();
			tb1.Update();
			player.Update();
			win->Update();
		}

		virtual void KeyPress(Key key){
			switch(key){
			using enum Key;
			case Space:
				door.SetClosed(true);
				break;

			default:
				break;
			}
		}

		virtual void KeyRelease(Key key){
			switch(key){
			using enum Key;
			case Space:
				door.SetClosed(false);
				break;

			default:
				break;
			}
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
