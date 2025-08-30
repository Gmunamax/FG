#pragma once
#include <GL/glew.h>
#include "point.hpp"
#include "color.hpp"

using Vertex3i = Point3i;

class Vertex3d{
	Point3d position;
	Color3i color;
	
public:

	Vertex3d(){
		position = {0,0,0};
		color = {0,0,0};
	}
	Vertex3d(double x, double y, double z){
		position = {x,y,z};
		color = {0,0,0};
	}
	void SetPosition(Point3d position){
		this->position = position;
	}
	void SetColor(Color3d color){

	}
	Point3d& GetPosition(){
		return position;
	}
	Color3i& GetColor(){
		return color;
	}
	void Draw(){
		glColor3d(color.r,color.g,color.b);
		glVertex3d(position.x,position.y,position.z);
	}

	void DrawAsPart(){
		glVertex3d(position.x,position.y,position.z);
	}
};
