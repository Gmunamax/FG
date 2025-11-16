#pragma once
#include <GL/glew.h>
#include <vector>
#include "vertex.hpp"

template<typename VertexType>
class Face{
    std::vector<VertexType> data;

public:
    short GetSize(){
        return data.size();
    }
    VertexType* GetData(){
        return data.data();
    }
    VertexType GetVertex(std::size_t pos){
        return data.at(pos);
    }
    void InsertVertex(std::size_t pos, VertexType vertex){
        data.insert(data.begin()+pos,vertex);
    }
    void DeleteVertex(std::size_t pos){
        data.erase(data.begin()+pos);
    }

    Face(std::vector<VertexType>& data){
        
    }
};