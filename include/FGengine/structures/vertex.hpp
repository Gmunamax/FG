#pragma once
#include <GL/glew.h>
#include "point.hpp"
#include "color.hpp"

template<typename PosType, class Base>
class VertexPosition{
protected:
	VertexPosition(PosType position){
		SetPosition(position);
	}
	VertexPosition(){}

public:
	using DataType = PosType;

protected:

	DataType position;
	static inline const short offset = offsetof(Base, position);

public:
	void SetPosition(PosType newposition){
		this->position = newposition;
	}
	PosType& GetPosition(){
		return this->position;
	}
	static short GetOffset(){
		return VertexPosition::offset;
	}
};

template<typename ColType, typename Base>
class VertexColor{
protected:
	VertexColor(ColType color){
		SetColor(color);
	}
	VertexColor(){}

public:
	using DataType = ColType;

protected:
	DataType color;
	static inline const short offset = offsetof(Base, color);

public:
	void SetColor(ColType newcolor){
		this->color = newcolor;
	}
	ColType& GetColor(){
		return this->color;
	}
	static short GetOffset(){
		return VertexColor::offset;
	}
};

template<typename NormalType, typename Base>
class VertexNormal{

protected:
	VertexNormal(NormalType normal){
		SetNormal(normal);
	}
	VertexNormal(){}

public:
	using DataType = NormalType;

protected:
	DataType normal;
	static inline const short offset = offsetof(Base, normal);

public:
	void SetNormal(NormalType newnormal){
		this->normal = newnormal;
	}
	NormalType& GetNormal(){
		return this->normal;
	}
	static short GetOffset(){
		return VertexNormal::offset;
	}
};

template<typename Pos, typename Col, typename Normal = Point3d>
class Vertex: public VertexPosition<Pos,Vertex<Pos,Col,Normal>>, public VertexColor<Col, Vertex<Pos,Col,Normal>>, public VertexNormal<Normal, Vertex<Pos,Col,Normal>>{
public:
	Vertex(Pos pos, Col col, Normal normal):
		Vertex::VertexPosition(pos),
		Vertex::VertexColor(col),
		Vertex::VertexNormal(normal)
	{}
	Vertex(){}

	static int GetStride(){
		return stride;
	}

private:

	static const int stride = sizeof(Vertex);

	static inline GLuint vao;
	static inline bool ready;
};

using Vertex2d = Vertex<Point2d,Colord,Point2d>; /* Note: Normals in 2d space are useless. They're still here, because I don't know exactly what to do with them, should they be here or not. */
using Vertex3d = Vertex<Point3d,Colord,Point3d>;