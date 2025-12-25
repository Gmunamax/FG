#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/objects/model/shaderdata.hpp"

template <typename PointType>
class Scale: virtual protected ShaderData{
	PointType scale {1};

protected:

	void ProceedScale(){
		
	}

public:

};