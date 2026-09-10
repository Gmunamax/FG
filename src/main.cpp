#include <args.hpp>
#include <FGengine/special/window.hpp>
#include <FGengine/special/context.hpp>
#include <FGengine/init.hpp>
#include "events.hpp"
#include "gameScene/gameScene.hpp"

int main(int argc, char* argv[]){
	ArgParser::parseArguments(argc, argv);
	FGengine::Init();
		FGengine::Window win{"FG", {800, 600}};
		FGengine::Context ctx{win};
		GameScene scene{&win};
		EventsWorker eventsWorker{&scene};
		eventsWorker.MainCycle();
	FGengine::Quit();
}
