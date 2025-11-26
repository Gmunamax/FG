#include "FGengine/shaders/shaderprogram.hpp"

namespace ShaderProgram{

	static bool needupdateviewm;
	static glm::mat4* viewm;
	static bool needupdateprojm;
	static glm::mat4* projm;
	static glm::mat4* objm;

	void SetViewMatrix(glm::mat4* newviewm){
		viewm = newviewm;
	}
	void UpdateViewMatrix(){
		needupdateviewm = true;
	}
	void SetProjectionMatrix(glm::mat4* newprojm){
		projm = newprojm;
	}
	void UpdateProjectionMatrix(){
		needupdateprojm = true;
	}
	void SetObjectMatrix(glm::mat4* newobjm){
		objm = newobjm;
	}
}

void ShaderProgram::SendMatrixTo(GLuint shaderprogram){
	glUseProgram(shaderprogram);
	glUniformMatrix4fv( glGetUniformLocation(shaderprogram, "objectmatrix"), 1, GL_FALSE, glm::value_ptr( (glm::mat4)*objm ));

	if(needupdateviewm){
		glUniformMatrix4fv( glGetUniformLocation(shaderprogram, "viewmatrix"), 1, GL_FALSE, glm::value_ptr((glm::mat4)*viewm));
		needupdateviewm = false;
	}

	if(needupdateprojm){
		glUniformMatrix4fv( glGetUniformLocation(shaderprogram, "projectionmatrix"), 1, GL_FALSE, glm::value_ptr((glm::mat4)*projm));
		needupdateprojm = false;
	}
}
