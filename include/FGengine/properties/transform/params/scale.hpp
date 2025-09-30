#pragma once
#include <glm/gtc/matrix_transform.hpp>

template <typename PointType>
class Scale{
protected:
	PointType scale {1};

	void ProceedScale(glm::mat4& mat);

public:
	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
	}
};

template<typename PointType> void Scale<PointType>::ProceedScale(glm::mat4& mat){
	mat = glm::scale(mat,glm::vec3(scale.x,scale.y,scale.z));
}