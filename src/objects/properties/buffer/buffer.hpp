#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "FGengine/structures/vertex.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

class Buffer{
	GLenum type;
	GLuint buf;

public:
	void Select(){
		glBindBuffer(type,buf);
	}
	void Generate(GLenum type){
		glGenBuffers(1,&buf);
		this->type = type;
	}
	void Delete(){
		glDeleteBuffers(1,&buf);
	}
	void Load(GLsizeiptr size, const void* data, GLenum usage){
		glBufferData(type, size, data, usage);
	}
	GLuint& GetBuffer(){
		return buf;
	}

	Buffer(){}
	~Buffer(){}
};

template<typename VertexType>
class Drawer{
	long long size;
	
	bool free = true;
	
	Buffer vbo;
	Buffer ebo;

	void Select();

protected:
	GLuint shaderprog = 0;

	Drawer(){};

	void drawBuf();
 
public:
	void Init();

	void Load(std::vector<VertexType> data);

	void SetShaderProgram(GLuint shaderprog);

	~Drawer();
};

template<typename VertexType> void Drawer <VertexType>::Init(){
	vbo.Generate(GL_ARRAY_BUFFER);
	// ebo.Generate(GL_ELEMENT_ARRAY_BUFFER);
}

template<typename VertexType> void Drawer <VertexType>::Select(){
	VertexType::SelectVAO();
	vbo.Select();
	// ebo.Select();
}

template<typename VertexType> void Drawer <VertexType>::Load(std::vector<VertexType> data){
	Select();

	vbo.Load(sizeof(VertexType) * data.size(), data.data(), GL_STATIC_DRAW);
	// ebo.Load(sizeof(unsigned short) * indexessize, indexes, GL_STATIC_DRAW);
	VertexType::Init();

	size = data.size();
	free = false;
}

template<typename VertexType> void Drawer <VertexType>::drawBuf(){
	ShaderProgram::SendMatrixTo(shaderprog);
	Select();
	glDrawArrays(GL_TRIANGLES,0,size);
	// glDrawElements(GL_TRIANGLES,size,GL_UNSIGNED_SHORT,0);
}

template<typename VertexType>  Drawer <VertexType>::~Drawer(){
	if(not free){
		vbo.Delete();
		ebo.Delete();
	}
}

template<typename VertexType> void Drawer <VertexType>::SetShaderProgram(GLuint shaderprog){
	this->shaderprog = shaderprog;
}