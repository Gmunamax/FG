#pragma once
#include "params/position.hpp"
#include "params/rotation.hpp"
#include "params/scale.hpp"

template<typename PointType>
class Transform: public Position<PointType>, public Rotation<PointType>, public Scale<PointType>{

protected:
	void ProceedTransformations();
	glm::mat4* GetMatrix();

	Transform(){};
};

template<typename PointType> void Transform<PointType>::ProceedTransformations(){
	Transform::ProceedPosition();
	Transform::ProceedRotation();
	Transform::ProceedScale();
}

template<typename PointType> glm::mat4* Transform<PointType>::GetMatrix(){
	return &mat;
}