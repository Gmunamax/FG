#include <FGengine/window.hpp>
#include <FGengine/context.hpp>
#include <FGengine/init.hpp>
#include <FGengine/videoOutput/eventsWorker.hpp>
import Night1;
#include <cstring>
#include <memory>

int main(int argc, char* argv[]){
	FGengine::Init();
	FGengine::Window win{"FG", {800, 600}};
	FGengine::Context ctx{win};
	std::unique_ptr<FGengine::VideoOutput::EventsPack> scene;
	scene = std::make_unique<Night1::Scene>(&win);
	FGengine::VideoOutput::EventsWorker eventsWorker{scene.get()};
	eventsWorker.MainCycle();
	FGengine::Quit();
}
