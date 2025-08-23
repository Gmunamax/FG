#pragma once
#include "vertex.hpp"
#include <vector>
#include <GL/glew.h>

class OFace3d{
	std::vector<Vertex3d> vertexposdata;
	Point3d normal;
	Color3f color;
public:

	std::vector<Vertex3d>& GetVertexes(){
		return vertexposdata;
	}
	Color3f GetColor(){
		return color;
	}

	OFace3d(Vertex3d vertexposdata[], short vertexcount, Color3f color, Point3d normal){
		for(int i = 0; i < vertexcount; i++){

			this->vertexposdata.push_back(vertexposdata[i]);
		}
		this->color = color;
		this->normal = normal;
	}

	void Draw(){
		glNormal3d(normal.x, normal.y, normal.z);
		for(int i = 0; i < vertexposdata.size(); i++){
			glColor3d(color.r,color.g,color.b);
			vertexposdata[i].DrawAsPart();
		}
	}
};

class Face3d{
	std::vector<Vertex3d> vertexposdata;
	Point3d normal;
	Color3f color;
public:

	std::vector<Vertex3d>& GetVertexes(){
		return vertexposdata;
	}
	Color3f GetColor(){
		return color;
	}

	Face3d(Vertex3d vertexposdata[], short vertexcount, Color3f color, Point3d normal){
		for(int i = 0; i < vertexcount; i++){
			
			this->vertexposdata.push_back(vertexposdata[i]);
		}
		this->color = color;
		this->normal = normal;
	}

	void Draw(){
		glNormal3d(normal.x, normal.y, normal.z);
		for(int i = 0; i < vertexposdata.size(); i++){
			glColor3d(color.r,color.g,color.b);
			vertexposdata[i].DrawAsPart();
		}
	}
};