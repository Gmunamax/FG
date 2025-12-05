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
			this->uniform = glGetUniformLocation(shaderid,name);
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


		bool needupdate = false;

		const char* name;
		GLuint shaderid;

		GLint uniform;

	public:

		void Send(){
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
				needupdate = false;
			}
		}

		const char* GetName(){
			return name;
		}

	};

	template<typename ValueType, short EnumValueType>
	class Uniform: private UniformData{
	public:
		Uniform(const char* name, GLuint shaderid = 0, ValueType value = nullptr): UniformData(name, shaderid, (void*)EnumValueType){
			SetValue(value);
		}
		void operator=(ValueType newvalue){
			SetValue((void*)newvalue);
			Update();
		}

	};

	using Umat4 = Uniform<glm::mat4*, UniformData::DataTypes::Matrix4f>;
	using Umat3 = Uniform<glm::mat3*, UniformData::DataTypes::Matrix3f>;
	using Uvec4 = Uniform<glm::vec4*, UniformData::DataTypes::Vector4f>;
	using Uvec3 = Uniform<glm::vec3*, UniformData::DataTypes::Vector3f>;

}