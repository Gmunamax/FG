#pragma once
#include <GL/glew.h>

template<typename VertexType>
class VertBuffer{

	static inline constexpr int target = GL_ARRAY_BUFFER;
	static inline constexpr int usage = GL_STATIC_DRAW;

	GLuint buf;

protected:
	void Select(){
		glBindBuffer(target,buf);
	}
	void Init(){
		glGenBuffers(1,&buf);
	}
	void Load(const std::vector<VertexType>& data){
		glBufferData(target, sizeof(VertexType)*data.size(), data.data(), usage);
	}
	void Delete(){
		glDeleteBuffers(1, &buf);
	}
};