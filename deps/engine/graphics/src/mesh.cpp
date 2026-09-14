#include <engine/graphics/properties/mesh.hpp>
#include <gl/gl.hpp>

Mesh::Mesh(std::span<float> vertexes):
	size(vertexes.size())
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size_bytes(), vertexes.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Mesh::Draw(){
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
}
