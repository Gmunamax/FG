#pragma once
#include <span>

class Mesh{
public:
	Mesh(std::span<float> vertexes);

	void Draw();

private:
	unsigned int vbo;
	unsigned int vao;
};
