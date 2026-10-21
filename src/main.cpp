#include <FGengine/window.hpp>
#include <FGengine/context.hpp>
#include <FGengine/init.hpp>
#include <engine/videoOutput/events.hpp>
import Night1;
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
	scene = std::make_unique<Night1::Scene>(&win);
	EventsWorker eventsWorker{scene.get()};
	eventsWorker.MainCycle();
	FGengine::Quit();
}
