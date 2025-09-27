#pragma once
#include <GL/glew.h>
#include "point.hpp"
#include "color.hpp"
#define VertexAttribs template<typename Pos, typename Col>

VertexAttribs class Vertex;

VertexAttribs struct VertexAO{
	static inline GLuint vao;
	static inline bool ready;

	static void Quit(){
		glDeleteVertexArrays(1,&vao);
	}
	static void SelectVAO(){
		glBindVertexArray(vao);
	}

	static void Init(){
		if(not ready){
			glGenVertexArrays(1,&vao);
			SelectVAO();
			SetPos();
			SetCol();
			ready = true;
		}
	}

protected:
	VertexAO(){}

private:
	static void SetPos(){
		std::cout << Pos::_elemcount << std::endl;
		glVertexAttribPointer(0, Pos::_elemcount, Pos::_gldatatype, false, sizeof(Pos)+sizeof(Col), 0);
		glEnableVertexAttribArray(0);
	}
	static void SetCol(){
		glVertexAttribPointer(1, Col::_elemcount, Col::_gldatatype, false, sizeof(Pos)+sizeof(Col), (void*)sizeof(Pos));
		glEnableVertexAttribArray(1);
	}

};

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

VertexAttribs class Vertex: public VertexAO<Pos,Col>, public VertexPosition<Pos>, public VertexColor<Col>{
public:
	Vertex(Pos pos, Col col):
		Vertex::VertexPosition(pos),
		Vertex::VertexColor(col)
	{}
	Vertex(){}
};

using Vertex2d = Vertex<Point2d,Colord>;
using Vertex3d = Vertex<Point3d,Colord>;