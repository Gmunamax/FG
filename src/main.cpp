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
