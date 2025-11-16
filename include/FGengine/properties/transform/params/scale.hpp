#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/objects/model/shaderdata.hpp"

template <typename PointType>
class Scale: virtual private ShaderData{
	PointType scale {1};

protected:

	void ProceedScale(){
		objm = glm::scale(objm,scale);
	}

public:
	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
	}
};