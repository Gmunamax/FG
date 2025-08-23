#include <iostream>
#include <vector>
#include <map>
//#include <freetype2/ft2build.h>
#include "Main/main.hpp"
#include "scenes/scene.hpp"
#include "config.hpp"
#include "states.hpp"
#include "scenes/buffer.hpp"
#include "Walk.hpp"

#include <SDL2/SDL_ttf.h>

int main(){

	init(WINDOWW,WINDOWH);
	std::cout << "Hello world!" << std::endl;
	Scene::Scene();
	std::cout << "Starting" << std::endl;
	mainCycle();
	std::cout << "Goodbye!" << std::endl;
	
	return 0;
}