#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ShaderProgram{

	void SetViewMatrix(glm::mat4* newviewmatrix);
	void UpdateViewMatrix();
	void SetProjectionMatrix(glm::mat4* newprojmatrix);
	void UpdateProjectionMatrix();
	void SetObjectMatrix(glm::mat4* newobjecmatrix);

	void SendMatrixTo(GLuint shaderprogram);
}