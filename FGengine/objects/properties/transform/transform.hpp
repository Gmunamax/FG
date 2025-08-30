#pragma once
#include "FGengine/structures/point.hpp"
#include <GL/glew.h>

class Position3d{
	using PointType = Point3d;
protected:
	PointType position = {0,0,0};

	void ProceedPosition();

public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}
};

class Rotation3d{
	using PointType = Point3d;
protected:
	PointType rotation = {0,0,0};

	void ProceedRotation();

public:
	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
	}
};

class Scale3d{
	using PointType = Point3d;
protected:
	PointType scale = {1,1,1};

	void ProceedScale();

public:
	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
	}
};