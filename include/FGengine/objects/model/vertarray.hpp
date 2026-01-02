#pragma once
#include <iostream>
#include "FGengine/structures/vertex.hpp"

template<typename VertexType>
class VertArray{
	GLuint buf;

	void ApplyPosition(){
		glVertexAttribPointer(0, VertexType::VertexPosition::GetLength(), VertexType::VertexPosition::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexPosition::GetOffset());
		glEnableVertexAttribArray(0);
	}
	void ApplyColor(){
		glVertexAttribPointer(1, VertexType::VertexColor::GetLength(), VertexType::VertexColor::DataType::_gldatatype, false, VertexType::GetStride(), (void*)VertexType::VertexColor::GetOffset());
		glEnableVertexAttribArray(1);
	}
	void ApplyNormal(){
		glVertexAttribPointer(2, VertexType::VertexNormal::GetLength(), VertexType::VertexNormal::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexNormal::GetOffset());
		glEnableVertexAttribArray(2);
	}

protected:
	void Select(){
		glBindVertexArray(buf);
	}

	void Init(){
		glGenVertexArrays(1,&buf);
	}

	void Setup(){
		VertArray::ApplyPosition();
		VertArray::ApplyColor();
		VertArray::ApplyNormal();
	}

	void Delete(){
		glDeleteVertexArrays(1,&buf);
	}
};