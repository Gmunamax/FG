#pragma once
#include <glm/gtc/matrix_transform.hpp>

template <typename PointType>
class Rotation{
protected:
	PointType rotation;

	void ProceedRotation(glm::mat4& mat);

public:
	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
	}
};

template<typename PointType> void Rotation<PointType>::ProceedRotation(glm::mat4& mat){
	if(rotation.x != 0)
		mat = glm::rotate(mat, (float)glm::radians(rotation.x), glm::vec3{1,0,0});
	if(rotation.y != 0)
		mat = glm::rotate(mat, (float)glm::radians(rotation.y), glm::vec3{0,1,0});
	if(rotation.z != 0)
		mat = glm::rotate(mat, (float)glm::radians(rotation.z), glm::vec3{0,0,1});
}