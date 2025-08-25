#pragma once
#include <iostream>
#include <string>

void Log(std::string message){
	#ifdef DEBUG
	std::cout << message << std::endl;
	#endif
}

void FastLog(std::string message){
	#ifdef DEBUG
	std::cout << message << std::endl;
	#endif
}