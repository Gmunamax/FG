#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "FGengine/structures/face.hpp"
#include "FGengine/structures/vertex.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

template<typename VertexType>
class ElemBuffer{
	static inline constexpr short target = GL_ELEMENT_ARRAY_BUFFER;
	static inline constexpr short dividemode = GL_TRIANGLE_STRIP;
	static inline constexpr short usage = GL_STATIC_DRAW;
	
	class FaceLocation{
		SizeType offset;
		SizeType size;
		
		void Select(){
			glBindBuffer(target,buf);
		}
		
	public:
		using SizeType = short;

		void Draw(){
			Select();
			glDrawElements(dividemode,size,offset);
		}
		FaceLocation(SizeType offset, SizeType size){
			this->offset = offset;
			this->size = size;
		}
	};
	
	GLuint buf;
	long maxsize = 0;
	std::vector<FaceLocation> facelocators;

protected:
	void Init(){
		glGenBuffers(1, &buf);
	}
	void Delete(){
		glDeleteBuffers(1, &buf);
	}
	void Select(){
		glBindBuffer(target, buf);
	}

	void Load(std::vector<std::vector<unsigned int>>& ptrtoprops){
		std::vector<unsigned int> newbuffer;
		for(std::vector<std::vector<unsigned int>>::const_reference face : ptrtoprops){
			facelocators.emplace_back(maxsize, face.size());
			maxsize+=face.size();
			for(short i = 0; i<=face.size(); i++)
				newbuffer.emplace_back(face.at(i));
		}
		Select();
		glBufferData(target, newbuffer.size()*sizeof(unsigned int), newbuffer.data(), usage);
	}

	void Draw(){
		for(std::vector<FaceLocation>::reference modelface : facelocators){
			modelface.Draw();
		}
	}

	ElemBuffer(){}
	~ElemBuffer(){}
};