#pragma once
#include "params/position.hpp"
#include "params/rotation.hpp"

template<typename PointType>
class WorldPoint: public Position<PointType>, public Rotation<PointType>{
	glm::mat4 mat{1};

protected:
	void ProceedTransformations();
	glm::mat4* GetMatrix();
	
	WorldPoint(){};
};

template<typename PointType> void WorldPoint<PointType>::ProceedTransformations(){
	// if (not ( WorldPoint::Position::needupdate or
	// 	 WorldPoint::Rotation::needupdate or
	// 	 WorldPoint::Scale::needupdate ) )
	// 	return;
	
	mat = glm::mat4{1};
	WorldPoint::ProceedPosition(mat);
	WorldPoint::ProceedRotation(mat);
	// WorldPoint::ProceedScale(mat);
}

template<typename PointType> glm::mat4* WorldPoint<PointType>::GetMatrix(){
	return &mat;
}