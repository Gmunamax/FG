#pragma once
#include <vector>
#include <span>

inline std::vector<float> ConvertToVertexArray(const std::span<float> vertexes, const std::span<unsigned> indices){
	constexpr unsigned vertexLength = 3;
	std::vector<float> vertexArray;

	for(auto index : indices){
		index = (index-1)*3;
		for(unsigned int i = 0; i < vertexLength; ++i){
			vertexArray.push_back(vertexes[index+i]);
		}
	}

	return vertexArray;
}
