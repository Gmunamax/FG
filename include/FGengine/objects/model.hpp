#pragma once
#include <GL/glew.h>
#include "FGengine/properties/transform/transform.hpp"
#include "FGengine/properties/buffer/buffer.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

template<typename VertexType>
class Model: public Transform<typename VertexType::VertexPosition::DataType>, public Drawer<VertexType>{

	typename VertexType::VertexPosition::DataType collidepos;
	typename VertexType::VertexPosition::DataType collidescale;

public:
	Model(){};

	void Draw();
};

template<typename VertexType> void Model<VertexType>::Draw(){
	Model::ProceedTransformations();
	ShaderProgram::SetObjectMatrix(Model::Transform::GetMatrix());
	Model::drawBuf();
}