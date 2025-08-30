#include "transform.hpp"

void Position3d::ProceedPosition(){
	glTranslated(position.x,position.y,position.z);
}

void Rotation3d::ProceedRotation(){
	if(rotation.x != 0)
		glRotated(rotation.x,1,0,0);
	if(rotation.y != 0)
		glRotated(rotation.y,0,1,0);
	if(rotation.z != 0)
		glRotated(rotation.z,0,0,1);
}

void Scale3d::ProceedScale(){
	glScaled(scale.x,scale.y,scale.z);
}