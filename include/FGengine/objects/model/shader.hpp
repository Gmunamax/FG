#pragma once
#include "FGengine/shaders/shaderprogram.hpp"
#include "FGengine/properties/transform/transform.hpp"

template<typename VertexType>
class ShaderProgram: public Transform<typename VertexType::VertexPosition::DataType>{
	GLuint shader =0;

	void Select(){
		glUseProgram(shader);
	}
	
protected:
	void UpdateShaderData(){
		Shader::Select();
		ShaderProgram::SetObjectMatrix(Model::Transform::GetMatrix());
		ShaderProgram::SendMatrixTo(shaderprog);
	}

public:
	void SetShader(GLuint newshader){
		this->shader = newshader;
	}
};