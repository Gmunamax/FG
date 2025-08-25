#pragma once
#include "structures/point.hpp"
#include <GL/glew.h>

struct Geometry3d{
	using PointType = Point3d;
protected:
	PointType position;
	PointType rotation;
	PointType scale;

	void ProceedPosition(){
		glTranslated(position.x,position.y,position.z);
	}
	void ProceedRotation(){
		if(rotation.x != 0)
			glRotated(rotation.x,1,0,0);
		if(rotation.y != 0)
			glRotated(rotation.y,0,1,0);
		if(rotation.z != 0)
			glRotated(rotation.z,0,0,1);
	}

public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}
	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
	}
	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
	}
};