#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "shaderdata.hpp"

class ShaderHandler: virtual private ShaderData{
	GLuint shader;

protected:
	void Select(){
		glUseProgram(shader);
	}
	void ResetMatrix(){
		objm = 1;
	}
	void SendMatrix(){
		glUniformMatrix4fv( glGetUniformLocation(shader, "objectmatrix"), 1, GL_FALSE, glm::value_ptr( (glm::mat4)objm ));
	}

public:
	void SetShader(GLuint newshader){
		this->shader = newshader;
	}
};