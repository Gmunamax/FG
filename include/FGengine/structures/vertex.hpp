#pragma once
#include <GL/glew.h>
#include "point.hpp"
#include "color.hpp"

template<typename Type> 
struct VertexType{
	using DataType = Type;
};

template<typename PosType>
class VertexPosition: public VertexType<PosType>{
	PosType position;

protected:
	VertexPosition(PosType position){
		this->position = position;
	}
	VertexPosition(){}

public:
	void SetPosition(PosType position){
		this->position = position;
	}
	PosType& GetPosition(){
		return position;
	}
};

template<typename ColType>
class VertexColor: public VertexType<ColType>{
	ColType color;

protected:
	VertexColor(ColType color){
		this->color = color;
	}
	VertexColor(){}

public:
	void SetColor(ColType color){
		this->color = color;
	}
	ColType& GetColor(){
		return color;
	}
};

template<typename NormalType>
class VertexNormal: public VertexType<NormalType>{
	NormalType normal;

protected:
	VertexNormal(NormalType normal){
		SetNormal(normal);
	}
	VertexNormal(){}

public:
	void SetNormal(NormalType normal){
		this->normal = normal;
	}
	NormalType& GetNormal(){
		return normal;
	}
};

template<typename Pos, typename Col, typename Normal = Point3d>
class Vertex: public VertexPosition<Pos>, public VertexColor<Col>, public VertexNormal<Normal>{
public:
	Vertex(Pos pos, Col col, Normal normal):
		Vertex::VertexPosition(pos),
		Vertex::VertexColor(col),
		Vertex::VertexNormal(normal)
	{}
	Vertex(){}

	static void DeleteType(){
		glDeleteVertexArrays(1,&vao);
	}
	static void SelectType(){
		glBindVertexArray(vao);
	}

	static void Init(){
		if(not ready){
			glGenVertexArrays(1,&vao);
			SelectType();

			Vertex::ApplyPosition();
			Vertex::ApplyColor();
			Vertex::ApplyNormal();

			ready = true;
		}
	}

private:

	static const int stride = sizeof(Pos)+sizeof(Col)+sizeof(Normal);

	static inline GLuint vao;
	static inline bool ready;
};

using Vertex2d = Vertex<Point2d,Colord,Point2d>; /* Note: Normals in 2d space are useless. They're still here, because I don't know exactly what to do with them, should they be here or not. */
using Vertex3d = Vertex<Point3d,Colord,Point3d>;