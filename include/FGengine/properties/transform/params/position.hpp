#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/objects/model/shaderdata.hpp"

template <typename PointType>
class Position: virtual protected ShaderData{


protected:
	
	void ProceedPosition(){
		objm = glm::translate(objm,position);
	}

public:

};