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
		VertexDataStorage::VertArray::Select();
		VertexDataStorage::VertBuffer::Init();
		VertexDataStorage::VertArray::Select();
		VertexDataStorage::ElemBuffer::Init();
		VertexDataStorage::ElemBuffer::Select();
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
		VertexDataStorage::VertArray::Select();
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