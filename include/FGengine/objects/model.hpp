#pragma once
#include <GL/glew.h>
#include "FGengine/properties/transform/transform.hpp"
#include "FGengine/objects/model/datastorer.hpp"
#include "FGengine/objects/model/shader.hpp"

template<typename VertexType>
class Model: public ShaderProgram<VertexType>, public VertexDataStorage<VertexType>{

	// typename VertexType::VertexPosition::DataType collidepos;
	// typename VertexType::VertexPosition::DataType collidescale;

public:
	Model(){};

	void Init();

	void Draw();
};

template<typename VertexType> void Model<VertexType>::Init(){
	Model::VertexDataStorage::Init();
}

template<typename VertexType> void Model<VertexType>::Draw(){
	Model::Select();
	Model::ProceedTransformations();
	ShaderProgram::UpdateShaderData();
	Model::DrawData();
}