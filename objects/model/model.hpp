#pragma once
//#include <GL/gl.h>
#include <GL/glew.h>
#include "../../structures/point.hpp"
#include "../../structures/vertex.hpp"
#include "../properties/position.hpp"
#include "buffer.hpp"


class Model3d: public Location, public Buffer3d{

	Point3d scale = {1,1,1};

	Point3d collidepos = {-1,-1,-1};
	Point3d collidescale = {2,2,2};

	double transparency = 0;

	Point3i centerpoint = {0,0,0};

	void CalcPosition(){
		glTranslatef(position.x,position.y,position.z);
	}

	void CalcRotation(){
		if(rotation.x != 0)
			glRotated(rotation.x,1,0,0);
		if(rotation.y != 0)
			glRotated(rotation.y,0,1,0);
		if(rotation.z != 0)
			glRotated(rotation.z,0,0,1);
	}

	void CalcScale(){
		glScaled(scale.x,scale.y,scale.z);
	}

	void Calc(){
		CalcPosition();
		CalcRotation();
		CalcScale();
	}

	bool cancollide = false;

public:


	Model3d() {
		std::cout << "Some model: Hi!" << '\n';
	}

	void Load(std::vector<Point3d> points){
		buffer(points);
	}

	// Point3d& GetPosition(){
	// 	return position;
	// }
	// void SetPosition(Point3d newposition){
	// 	position = newposition;
	// 	needupdate = true;
	// }
	// void SetPosition(char axis, double value){
	// 	if(axis == 'x'){
	// 		position.x = value;
	// 	}
	// 	else if(axis == 'y'){
	// 		position.y = value;
	// 	}
	// 	else if(axis == 'z'){
	// 		position.z = value;
	// 	}
	// }

	// Point3d& GetRotation(){
	// 	return rotation;
	// }
	// void SetRotation(Point3d newrotation){
	// 	rotation = newrotation;
	// 	needupdate = true;
	// }

	// Point3d& GetScale(){
	// 	return scale;
	// }
	// void SetScale(Point3d newscale){
	// 	scale = newscale;
	// 	needupdate = true;
	// }

	bool IsCollide(Point3d obj){
		if(cancollide){
			Point3d collidestart = position + collidepos;
			Point3d collideend = collidestart + collidescale;

			bool resultx = (collidestart.x < obj.x) and (obj.x < collideend.x);
			bool resulty = (collidestart.y < obj.y) and (obj.y < collideend.y);

			return (resultx and resulty);
		}
		return false;
	}

	void Draw(){
		glPushMatrix();

		Calc();
		drawBuf();

		glPopMatrix();
	}

	
};