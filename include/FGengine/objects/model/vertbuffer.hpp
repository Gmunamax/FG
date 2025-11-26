#pragma once
#include <GL/glew.h>

template<typename VertexType>
class VertBuffer{

	static inline constexpr short target = GL_ARRAY_BUFFER;
	static inline constexpr short usage = GL_STATIC_DRAW;

	GLuint buf;

protected:
	void Select(){
		glBindBuffer(target,buf);
	}
	void Init(){
		glGenBuffers(1,&buf);
	}
	void Load(const std::vector<VertexType>& data){
		glBufferData(target, sizeof(VertexType)*data.size(), &data, usage);
	}
	void Delete(){
		glDeleteBuffers(1, &buf);
	}
};