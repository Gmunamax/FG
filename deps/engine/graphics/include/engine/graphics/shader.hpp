#pragma once
#include <string_view>

class Shader{
public:
	Shader(std::string_view vertexShader, std::string_view fragmentShader);

	void Use();

	unsigned int GetHandle(){
		return shaderProgram;
	}

private:
	unsigned int CreateShader(unsigned int type, std::string_view source);

	unsigned int shaderProgram;
};
