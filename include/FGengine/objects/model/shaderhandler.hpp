#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "shaderdata.hpp"
#include "FGengine/shaders/shader.hpp"

class ShaderHandler: virtual private ShaderData{
	// GLuint shader;
	Shader* shader;

protected:
	void Select(){
		// shader->Bind();
	}
	void SendMatrix(){
		
		glUniformMatrix4fv( glGetUniformLocation(shader, "objectmatrix"), 1, GL_FALSE, glm::value_ptr( (glm::mat4)objm ));
	}

public:
	void SetShader(Shader* shader){
		this->shader = newshader;
	}
};