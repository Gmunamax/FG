#pragma once
#include "../../structures/point.hpp"
#include <GL/gl.h>

struct Location{
protected:
	Point3d position;
	Point3d rotation;

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
	Point3d& GetPosition(){
		return position;
	}
	void SetPosition(Point3d newposition){
		position = newposition;
	}
	Point3d& GetRotation(){
		return rotation;
	}
	void SetRotation(Point3d newrotation){
		rotation = newrotation;
	}
};
