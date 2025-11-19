#pragma once
#include <optional>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GL/glew.h>

class ShaderProperty{
	enum DataTypes{
		Empty,
		Matrix4f,
		Matrix3f,
		Vector4f,
		Vector3f
	};
	void* value;
	DataTypes valuetype;

	int size;

	bool needupdate = false;
	GLint uniform;

	ShaderProperty(GLint uniform, void* value){
		this->uniform = uniform;
		this->value = value;		
	}
	void BindValue(void* value){
		this->value = value;
	}

public:
	void Update(){
		if(needupdate){
			switch(valuetype){
			case Matrix4f:
				glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr( *(glm::mat4*)value ));
				break;
			case Matrix3f:
				glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr( *(glm::mat3*)value ));
				break;
			case Vector4f:
				glUniform4f(uniform, ((glm::vec4*)value)->x, ((glm::vec4*)value)->y, ((glm::vec4*)value)->z, ((glm::vec4*)value)->w);
				break;
			case Vector3f:
				glUniform3f(uniform, ((glm::vec3*)value)->x, ((glm::vec3*)value)->y, ((glm::vec3*)value)->z);
				break;
			default:
				break;
			}
		}
	}

	
	void BindValue(glm::mat4* value){
		BindValue((void*)value);
		valuetype = Matrix4f;
	}
	void BindValue(glm::mat3* value){
		BindValue((void*)value);
		valuetype = Matrix3f;
	}
	void BindValue(glm::vec4* value){
		BindValue((void*)value);
		valuetype = Vector4f;
	}
	void BindValue(glm::vec3* value){
		BindValue((void*)value);
		valuetype = Vector3f;
	}

	ShaderProperty(GLint uniform, glm::mat4* value): ShaderProperty(uniform, (void*)value){
		valuetype = Matrix4f;
	}
	ShaderProperty(GLint uniform, glm::mat3* value): ShaderProperty(uniform, (void*)value){
		valuetype = Matrix3f;
	}
	ShaderProperty(GLint uniform, glm::vec4* value): ShaderProperty(uniform, (void*)value){
		valuetype = Vector4f;
	}
	ShaderProperty(GLint uniform, glm::vec3* value): ShaderProperty(uniform, (void*)value){
		valuetype = Vector3f;
	}
	ShaderProperty(GLint uniform, std::nullptr_t): ShaderProperty(uniform, (void*)nullptr){
		valuetype = Empty;
	}
};