#pragma once
#include <engine/graphics/shader.hpp>
#include <engine/graphics/properties/mesh.hpp>
#include <engine/graphics/properties/objectMatrix.hpp>
#include <memory>
#include <span>

class Model{
public:
	Model(std::span<float> vertexes, const std::shared_ptr<Shader>& shader):
		shader{shader},
		mesh{vertexes}
	{}

	void Draw(){
		shader->Use();
		matrix.Update();
		mesh.Draw();
	}

	void SetPosition(const glm::vec3& newPosition){
		matrix.SetPosition(newPosition);
	}

private:
	std::shared_ptr<Shader> shader;
	Mesh mesh;
	ObjectMatrix matrix{shader->GetHandle()};
};
