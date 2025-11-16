#pragma once
#include "FGengine/structures/vertex.hpp"

template<typename VertexType>
class VertArray{
	GLuint buf;

	void ApplyPosition(){
		glVertexAttribPointer(0, VertexType::VertexPosition::DataType::_elemcount, VertexType::VertexPosition::DataType::_gldatatype, false, Property<VertexType::VertexPositon>::GetStride(), 0);
		glEnableVertexAttribArray(0);
	}
	void ApplyColor(){
		glVertexAttribPointer(1, VertexType::VertexColor::DataType::_elemcount, VertexType::VertexColor::DataType::_gldatatype, false, Property<VertexType::VertexPositon>::GetStride(), 0);
		glEnableVertexAttribArray(1);
	}
	void ApplyNormal(){
		glVertexAttribPointer(2, VertexType::VertexNormal::DataType::_elemcount, VertexType::VertexNormal::DataType::_gldatatype, false, Property<VertexType::VertexPositon>::GetStride(), 0);
		glEnableVertexAttribArray(2);
	}

protected:
	void Select(){
		glBindVertexArray(buf);
	}

	void Init(){
		glGenBuffers(1,&buf);
		VertArray::Select();
		VertArray::ApplyPosition();
		VertArray::ApplyColor();
		VertArray::ApplyNormal();
	}

	void Delete(){
		glDeleteVertexArrays(1,&buf);
	}
};