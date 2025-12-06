#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GL/glew.h>

namespace Uniforms{

	class UniformData{
	public:
		enum DataTypes{
			Empty,
			Matrix4f,
			Matrix3f,
			Vector4f,
			Vector3f
		};
	
	protected:
		UniformData(const char* name, GLuint shaderid, DataTypes datatype){
			this->location = glGetUniformLocation(shaderid,name);
			valuetype = datatype;
		}

		void SetValue(void* value){
			this->value = value;
		}
		void Update(){
			needupdate = true;
		}

	private:
		void* value;
		DataTypes valuetype;
		const char* name;

	protected:
		bool needupdate = false;
		GLint location;

	public:

		const char* GetName(){
			return name;
		}
	
		void SetShader(GLuint newshader){
			location = glGetUniformLocation(newshader, name);
		}
	};

	template<typename ValueType>
	class Uniform: public UniformData{
		ValueType value;

		void TemplateSend();
	public:
		Uniform(const char* name, GLuint shaderid = 0, ValueType value = nullptr): UniformData(name, shaderid, (void*)EnumValueType){
			SetValue(value);
		}
		void operator=(ValueType newvalue){
			SetValue((void*)newvalue);
			Update();
		}
		void Send(){
			if(needupdate){
				TemplateSend();
				needupdate = false;
			}
		}

	};
	template<>
	void Uniform<glm::mat4>::TemplateSend(){
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr( (glm::mat4)value ));
	}
	template<>
	void Uniform<glm::mat3>::TemplateSend(){
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr( (glm::mat3)value ));
	}
	template<>
	void Uniform<glm::vec4>::TemplateSend(){
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	template<>
	void Uniform<glm::vec3>::TemplateSend(){
		glUniform3f(location, value.x, value.y, value.z);
	}

	using Umat4 = Uniform<glm::mat4>;
	using Umat3 = Uniform<glm::mat3>;
	using Uvec4 = Uniform<glm::vec4>;
	using Uvec3 = Uniform<glm::vec3>;

}