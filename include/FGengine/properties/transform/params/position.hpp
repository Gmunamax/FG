#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/objects/model/shaderdata.hpp"

template <typename PointType>
class Position: virtual private ShaderData{
	PointType position;

protected:
	
	void ProceedPosition(){
		objm = glm::translate(objm,position);
	}

public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}
};