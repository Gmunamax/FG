#pragma once
#include "elembuffer.hpp"
#include "vertbuffer.hpp"
#include "vertarray.hpp"

template<typename VertexType>
class VertexDataStorage: private VertBuffer<VertexType>, private ElemBuffer, private VertArray<VertexType>{
protected:

	//Must be called once, after Model created and OpenGL context loaded
	void Init(){
		VertexDataStorage::VertArray::Init();
		VertexDataStorage::VertBuffer::Init();
		VertexDataStorage::ElemBuffer::Init();
		VertexDataStorage::VertArray::Select();
		VertexDataStorage::VertBuffer::Select();
		VertexDataStorage::ElemBuffer::Select();
		VertexDataStorage::VertArray::Setup();
		glBindVertexArray(0);
	}

	void Select(){
		VertexDataStorage::VertArray::Select();
	}
	void Delete(){
		VertexDataStorage::VertArray::Delete();
		VertexDataStorage::VertBuffer::Delete();
		VertexDataStorage::ElemBuffer::Delete();
	}
	
	void DrawData(){
		VertexDataStorage::ElemBuffer::Draw();
	}

	VertexDataStorage(){};
	~VertexDataStorage(){};
public:

	void Load(const std::vector<VertexType>& vertexes, const std::vector<std::vector<unsigned int>>& elements){
		VertexDataStorage::VertBuffer::Load(vertexes);
		VertexDataStorage::ElemBuffer::Load(elements);
	}
};