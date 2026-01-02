#pragma once
#include <GL/glew.h>
#include <vector>
#include "FGengine/structures/face.hpp"
#include "FGengine/structures/vertex.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

class ElemBuffer{
	static inline constexpr int target = GL_ELEMENT_ARRAY_BUFFER;
	static inline constexpr int dividemode = GL_TRIANGLE_STRIP;
	static inline constexpr int usage = GL_STATIC_DRAW;
	static inline constexpr int gldatatype = GL_UNSIGNED_INT;
	using datatype = unsigned int;
	
	class FaceLocation{
	public:
		using SizeType = short;

	private:

		SizeType offset;
		SizeType size;
		
	public:

		void Draw(){
			glDrawElements(dividemode,size,gldatatype,(void*)(sizeof(datatype) * offset));
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

	void Load(const std::vector<std::vector<datatype>>& ptrtoprops){
		std::vector<datatype> newbuffer;
		for(const std::vector<datatype>& face : ptrtoprops){
			facelocators.emplace_back(maxsize, face.size());
			maxsize+=face.size();
			for(short i = 0; i < face.size(); ++i)
				newbuffer.emplace_back(face.at(i));
		}
		Select();
		glBufferData(target, newbuffer.size()*sizeof(datatype), newbuffer.data(), usage);
	}

	void Draw(){
		glBindBuffer(target,buf);
		for(typename std::vector<FaceLocation>::reference modelface : facelocators){
			modelface.Draw();
		}
	}

	ElemBuffer(){}
	~ElemBuffer(){}
};