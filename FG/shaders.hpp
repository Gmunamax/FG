#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>

class Shader{
	friend GLuint LoadShader(const char* location, GLenum type);
	GLuint id;
	
};

GLuint LoadShader(const char* location, GLenum type){
	GLuint s = glCreateShader(type);
	std::ifstream reader(location);
	if(!reader.is_open()){
		std::cout << "Shader: file not found: " << location << std::endl;
	}
	std::string shadcode = "";
	std::string line;
	while(std::getline(reader,line)){
		shadcode+=(line+"\n");
	}
	reader.close();
	const char* c = shadcode.c_str();

	glShaderSource(s, 1, &c, NULL);
    glCompileShader(s);
    // check for shader compile errors
    int su;
    char infoLog[512];
    glGetShaderiv(s, GL_COMPILE_STATUS, &su);
    if (!su){
        glGetShaderInfoLog(s, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << "Full source:" << std::endl;
		std::cout << c << std::endl;
    }
	return s;
}

GLuint LinkProgram(GLuint vert, GLuint frag){
	GLuint prog = glCreateProgram();
	if(vert != 0){
		glAttachShader(prog,vert);
	}
	if(frag != 0){
		glAttachShader(prog,frag);
	}
	glLinkProgram(prog);
	GLint reslt;
	char log[512];
	glGetProgramiv(prog, GL_LINK_STATUS, &reslt);
	if(!reslt){
		glGetProgramInfoLog(prog, 512, NULL, log);
		std::cout << log << std::endl;
	}
	return prog;
}

GLuint curprog = 0;