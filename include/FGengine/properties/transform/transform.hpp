#pragma once
#include "params/position.hpp"
#include "params/rotation.hpp"
#include "params/scale.hpp"

template<typename PointType>
class Transform: public Position<PointType>, public Rotation<PointType>, public Scale<PointType>{
	glm::mat4 mat {1};

protected:
	void ProceedTransformations();
	glm::mat4* GetMatrix();

	Transform(){};
};

template<typename PointType> void Transform<PointType>::ProceedTransformations(){
	// if (not ( Transform::Position::needupdate or
	// 	 Transform::Rotation::needupdate or
	// 	 Transform::Scale::needupdate ) )
	// 	return;
	
	mat = glm::mat4{1};
	Transform::ProceedPosition(mat);
	Transform::ProceedRotation(mat);
	Transform::ProceedScale(mat);
}

template<typename PointType> glm::mat4* Transform<PointType>::GetMatrix(){
	return &mat;
}