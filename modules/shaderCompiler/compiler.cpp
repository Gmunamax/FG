// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#include <string>
#include <iostream>
#include <fstream>

namespace FGengine{

static const char* const fileNotFoundError = "File not found";

std::string ReadFile(const char* path){
	std::ifstream reader(path);
	std::string shaderSource = "";

	if(reader.is_open()){
		std::string line;
		while(std::getline(reader,line)){
			shaderSource+=(line+"\n");
		}
		reader.close();
	}
	else{
		std::cout << fileNotFoundError << " [" << path << "]" << std::endl;
	}
	return shaderSource;
}

}
