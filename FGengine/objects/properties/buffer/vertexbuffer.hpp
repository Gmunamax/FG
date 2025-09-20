#include <GL/glew.h>
#include <vector>
#include "FGengine/structures/vertex.hpp"

class VertexBuffer{
	
	GLuint buffer;

	VertexBuffer(){
		glGenBuffers(1,&buffer);
	}
	void Buffer(std::vector<Vertex3d>& data){
		
	}
	void SetPos(){
		
	}
	void SetCol(){
		
	}
	void Delete(){
		glDeleteBuffers(1,&buffer);
	}
};