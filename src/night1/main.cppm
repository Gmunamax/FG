module;
#include <engine/videoOutput/eventsPack.hpp>
#include <FGengine/window.hpp>

export module Night1;
import :Office;
import :TB1;
import :Player;
import :Door;

namespace Night1{

	export class Scene: public EventsPack{
		TB1 tb1{&door};

		Office office;
		Door door;

		Player player;
		FGengine::Window* win;

		virtual void Draw(){
			win->Clear();
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
		Scene(FGengine::Window* win):
			win(win)
		{
			tb1.SetPosition({0, 3, 0});
			player.SetRotation({90, 0, 0});
		}
	};

}
