#pragma once
#include <GL/glew.h>
#include "point.hpp"
#include "color.hpp"

template<typename Type, class Base> 
class VertexType{
protected:
	using DataType = Type;
	DataType data;
	static inline const short offset = offsetof(Base, data);

public:
	static short GetOffset(){
		return VertexType::offset;
	}
};

template<typename PosType, class Base>
class VertexPosition: public VertexType<PosType,Base>{
protected:
	VertexPosition(PosType position){
		SetPosition(position);
	}
	VertexPosition(){}

public:
	void SetPosition(PosType newposition){
		this->data = newposition;
	}
	PosType& GetPosition(){
		return this->data;
	}
};

template<typename ColType, typename Base>
class VertexColor: public VertexType<ColType, Base>{
protected:
	VertexColor(ColType color){
		SetColor(color);
	}
	VertexColor(){}

public:
	void SetColor(ColType newcolor){
		this->data = newcolor;
	}
	ColType& GetColor(){
		return this->data;
	}
};

template<typename NormalType, typename Base>
class VertexNormal: public VertexType<NormalType, Base>{

protected:
	VertexNormal(NormalType normal){
		SetNormal(normal);
	}
	VertexNormal(){}

public:
	void SetNormal(NormalType newnormal){
		this->data = newnormal;
	}
	NormalType& GetNormal(){
		return this->data;
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