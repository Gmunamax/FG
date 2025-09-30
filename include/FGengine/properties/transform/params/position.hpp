#pragma once
#include <glm/gtc/matrix_transform.hpp>

template <typename PointType>
class Position{
protected:
	PointType position;
	
	void ProceedPosition(glm::mat4& mat);

public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}
};

template<typename PointType> void Position<PointType>::ProceedPosition(glm::mat4& mat){
	mat = glm::translate(mat,glm::vec3{position.x,position.y,position.z});
}