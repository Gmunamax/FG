#include "model.hpp"

void Model3d::Place(){
	ProceedPosition();
	ProceedRotation();
	ProceedScale();
}

Model3d::Model3d() {}

void Model3d::Load(std::vector<Point3d> points){
	buffer(points);
}

bool Model3d::IsCollide(Point3d obj){
	if(cancollide){
		Point3d collidestart = position + collidepos;
		Point3d collideend = collidestart + collidescale;

		bool resultx = (collidestart.x < obj.x) and (obj.x < collideend.x);
		bool resulty = (collidestart.y < obj.y) and (obj.y < collideend.y);

		return (resultx and resulty);
	}
	return false;
}

void Model3d::Draw(){
	glPushMatrix();

	Place();
	drawBuf();

	glPopMatrix();
}