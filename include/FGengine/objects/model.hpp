#pragma once
#include "FGengine/properties/transform/transform.hpp"
#include "FGengine/objects/model/datastorer.hpp"
// #include "FGengine/objects/model/shaderhandler.hpp"

template<typename VertexType>
class Model: public Transform<typename VertexType::VertexPosition::DataType>, public VertexDataStorage<VertexType>{
public:

	Model(){};

	Shader* shader;

	void SetShader(Shader* newshader){
		shader = newshader;
		Model::Transform::SetShader(newshader);
	}

	void Init(){
		Model::VertexDataStorage::Init();
	}

	void Select(){
		Model::VertexDataStorage::Select();
		glUseProgram(shader->ToGL());
		// Model::ShaderHandler::Select();
	}

	void Draw(){
		Model::Select();
		// Model::ResetMatrix();
		Model::ProceedTransformations();
		Model::DrawData();
	}
};