#pragma once
#include <glm/vec3.hpp>
#include <FGengine/structures/uniform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

class ObjectMatrix{
public:
	ObjectMatrix(unsigned int shaderProgram, glm::vec3 position = {0,0,0}):
		position{position},
		objectMatrix{"model", FGengine::ShaderID{shaderProgram}}
	{
		Calculate();
	}

	void Update(){
		Calculate();
		objectMatrix.Send();
	}

	void SetPosition(const glm::vec3& newPosition){
		position = newPosition;
	}
	const glm::vec3& GetPosition(){
		return position;
	}

private:
	void Calculate(){
		objectMatrix = glm::translate(glm::mat4{1}, position);
	}

	FGengine::Uniform<1, glm::mat4> objectMatrix;
	glm::vec3 position;
};
