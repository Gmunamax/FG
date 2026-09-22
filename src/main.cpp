#include <FGengine/window.hpp>
#include <FGengine/context.hpp>
#include <FGengine/init.hpp>
#include <engine/videoOutput/events.hpp>
#include "gameScene/gameScene.hpp"
#include "demoScene/demoScene.hpp"
#include <cstring>
#include <memory>

int main(int argc, char* argv[]){
	bool demo = false;

	for(unsigned i = 1; i < argc; ++i){
		if(std::strcmp(argv[i], "--demo") == 0){
			demo = true;
		}
	}
	FGengine::Init();
	FGengine::Window win{"FG", {800, 600}};
	FGengine::Context ctx{win};
	std::unique_ptr<EventsPack> scene;
	if(demo)
		scene = std::make_unique<DemoScene>(&win);
	else
		scene = std::make_unique<GameScene>(&win);
	EventsWorker eventsWorker{scene.get()};
	eventsWorker.MainCycle();
	FGengine::Quit();
}
