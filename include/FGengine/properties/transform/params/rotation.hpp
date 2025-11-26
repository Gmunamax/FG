#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/objects/model/shaderdata.hpp"

template <typename PointType>
class Rotation: virtual private ShaderData{
	PointType rotation;

protected:

	void ProceedRotation(){
		if(rotation.x != 0)
			objm = glm::rotate(objm, (float)glm::radians(rotation.x), glm::vec3{1,0,0});
		if(rotation.y != 0)
			objm = glm::rotate(objm, (float)glm::radians(rotation.y), glm::vec3{0,1,0});
		if(rotation.z != 0)
			objm = glm::rotate(objm, (float)glm::radians(rotation.z), glm::vec3{0,0,1});
	}

public:
	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
	}
};