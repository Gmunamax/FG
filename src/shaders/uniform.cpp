#include "FGengine/shaders/uniform.hpp"

namespace Uniforms{

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
	
}