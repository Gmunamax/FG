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
#include "compiler.hpp"
#include <iostream>
#include <fstream>

namespace FGengine{

static const char* const fileNotFoundError = "File not found";
static const char* const linkFailedError = "Shader link failed";

GLuint CreateShaderProgram(std::vector<Shader::ObjectDescription> descriptions){
	std::vector<GLuint> parts = CompileAllParts(descriptions);
	GLuint shaderid = LinkShader(parts);
	PrintLinkStatus(shaderid);
	DeleteParts(parts);
	return shaderid;
}

static std::vector<GLuint> CompileAllParts(std::vector<Shader::ObjectDescription> descriptions){
	std::vector<GLuint> shaderparts;
	for(Shader::ObjectDescription& part : descriptions){
		shaderparts.push_back( CompilePart(part) );
	}
	return shaderparts;
}

static GLuint CompilePart(Shader::ObjectDescription description){
	GLuint object = glCreateShader(description.type);
	std::vector<std::string> sources;
	std::vector<const char*> csources;
	std::vector<GLint> lenghts;
	std::string source;
	for(GLsizei i = 0; i < description.filepathes.size(); i++){
		source = ReadFile( description.filepathes.at(i) );
		sources.push_back(source);
		csources.push_back(source.c_str());
		lenghts.push_back(source.length());
	}
	glShaderSource(object, description.filepathes.size(), csources.data(), lenghts.data());
	glCompileShader(object);
	return object;
}

static std::string ReadFile(const char* path){
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

static GLuint LinkShader(std::vector<GLuint> shaderparts){
	GLuint shaderid = glCreateProgram();
	for(GLuint& part : shaderparts){
		glAttachShader(shaderid, part);
	}
	glLinkProgram(shaderid);
	return shaderid;
}

static void PrintLinkStatus(GLuint shaderid){
	constexpr short logsize = 512;
	int status;
	char log[logsize];
	glGetProgramiv(shaderid, GL_LINK_STATUS, &status);
	if(status != GL_TRUE){
		glGetProgramInfoLog(shaderid, logsize, NULL, log);
		std::cout << linkFailedError << "\n" << log << std::endl;
	}
}

static void DeleteParts(std::vector<GLuint> parts){
	for(GLuint& part : parts){
		glDeleteShader(part);
	}
}

}
