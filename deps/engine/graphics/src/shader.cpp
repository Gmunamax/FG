#include <engine/graphics/shader.hpp>
#include <gl/gl.hpp>
#include <iostream>

Shader::Shader(std::string_view vertexShader, std::string_view fragmentShader){
	unsigned int vert = CreateShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int frag = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vert);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::Use(){
	glUseProgram(shaderProgram);
}

unsigned int Shader::CreateShader(GLenum type, std::string_view source){
	unsigned int shader = glCreateShader(type);
	const char* csource = source.data();
	glShaderSource(shader, 1, &csource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}
