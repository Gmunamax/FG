#pragma once
#include <glm/vec3.hpp>
#include <FGengine/structures/uniform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

class ObjectMatrix{
public:
	ObjectMatrix(unsigned int shaderProgram, glm::vec3 position = {0,0,0}, glm::vec3 rotation = {0, 0, 0}):
		position{position},
		rotation{rotation},
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
	const glm::vec3& GetPosition() const{
		return position;
	}

	void SetRotation(const glm::vec3& newRotation){
		rotation = newRotation;
	}
	const glm::vec3& GetRotation() const{
		return rotation;
	}

private:
	void Calculate(){
		objectMatrix = glm::translate(glm::mat4{1}, position);
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.x, {1,0,0});
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.y, {0,1,0});
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.z, {0,0,1});
	}

	FGengine::Uniform<1, glm::mat4> objectMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
};
