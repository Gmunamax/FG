#pragma once
#include "elembuffer.hpp"
#include "vertbuffer.hpp"
#include "vertarray.hpp"

template<typename VertexType>
class VertexDataStorage: private VertBuffer<VertexType>, private ElemBuffer<VertexType> private VertArray<VertexType>{	
protected:

	//Must be called once, after Model created and OpenGL context loaded
	void Init(){
		VertArray::Init();
		VertArray::Select();
		VertBuffer::Init();
		VertArray::Select();
		ElemBuffer::Init();
		ElemBuffer::Select();
	}

	void Select(){
		VertArray::Select();
	}
	void Delete(){
		VertArray::Delete();
		VertBuffer::Delete();
		ElemBuffer::Delete();
	}
	
	void DrawData(){
		VertArray::Select();
		ElemBuffer::Draw();
	}

	VertexDataStorage(){};
	~VertexDataStorage(){};
public:

	void Load(std::vector<VertexType>& vertexes, std::vector<std::vector<unsigned int>>& elements){
		VertexDataStorage::VertBuffer::Load(vertexes);
		VertexDataStorage::ElemBuffer::Load(elements);
	}
};