#pragma once
#include "FGengine/properties/transform/transform.hpp"
#include "FGengine/objects/model/datastorer.hpp"
#include "FGengine/objects/model/shaderhandler.hpp"

template<typename VertexType>
class Model: public ShaderHandler<VertexType>, public Transform<typename VertexType::VertexPosition::DataType>, public VertexDataStorage<VertexType>{
public:

	Model(){};

	void Init(){
		Model::VertexDataStorage::Init();
	}

	void Select(){
		Model::VertexDataStorage::Select();
		Model::ShaderHandler::Select();
	}

	void Draw(){
		Model::Select();
		Model::ResetMatrix();
		Model::ProceedTransformations();
		Model::DrawData();
	}
};