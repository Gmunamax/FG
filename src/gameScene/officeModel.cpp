#include "officeModel.hpp"
#include <glm/vec3.hpp>
#include <vector>
#include <array>
#include <span>

namespace{
	std::span<float> GetPoints(){
		static float officeVertexes[]{
		-4.791071, 0.038613, -0.875585,
		-4.791071, 0.038613, 0.980120,
		3.587305, 0.038613, -0.875586,
		3.587305, 0.038613, 0.980119,
		-4.791071, -0.038612, -0.875585,
		-4.791071, -0.038612, 0.980120,
		3.587305, -0.038612, -0.875586,
		3.587305, -0.038612, 0.980119,
		-3.781683, 0.038613, -0.371967,
		-3.781683, 0.038613, 0.460649,
		0.874506, 0.038613, 0.460649,
		0.874506, 0.038613, -0.371967,
		0.874506, -0.038612, 0.460649,
		-3.781683, -0.038612, -0.371967,
		-3.781683, -0.038612, 0.460649,
		0.874506, -0.038612, -0.371967,
		1.543718, 0.038613, -0.875586,
		2.567228, 0.038613, -0.875586,
		1.543718, 0.038613, 0.682370,
		2.567228, 0.038613, 0.682370,
		1.543718, -0.038612, 0.682370,
		1.543718, -0.038612, -0.875586,
		2.567228, -0.038612, -0.875586,
		2.567228, -0.038612, 0.682370
		};

		return officeVertexes;
	}

	using LayoutType = std::vector<unsigned>;
	const LayoutType& GetModelIndexes(){
		static const LayoutType modelLayout{
			1, 10, 9,
			2, 4, 19,
			4, 7, 3,
			15, 5, 14,
			16, 22, 21,
			6, 1, 5,
			1, 22, 5,
			3, 23, 18,
			4, 6, 8,
			11, 16, 13,
			9, 15, 14,
			11, 15, 10,
			9, 16, 12,
			24, 18, 23,
			21, 17, 19,
			24, 19, 20,
			15, 6, 5,
			23, 7, 24,
			7, 8, 24,
			8, 6, 21,
			6, 15, 13,
			21, 6, 13,
			21, 24, 8,
			16, 14, 22,
			14, 5, 22,
			21, 13, 16,
			9, 14, 16,
			1, 2, 10,
			1, 9, 17,
			9, 12, 17,
			11, 10, 2,
			17, 12, 19,
			12, 11, 19,
			4, 3, 20,
			3, 18, 20,
			19, 11, 2,
			4, 20, 19,
			4, 8, 7,
			6, 2, 1,
			1, 17, 22,
			3, 7, 23,
			4, 2, 6,
			11, 12, 16,
			9, 10, 15,
			11, 13, 15,
			24, 20, 18,
			21, 22, 17,
			24, 21, 19,

		};
		return modelLayout;
	}

	std::array<float, 3> GetVertex(unsigned id){
		auto officeVertexes = GetPoints();
		id-=1;
		id*=3;
		return {officeVertexes[id], officeVertexes[id+1], officeVertexes[id+2]};
	}

	// std::array<float, 3> GetVertex(const std::array<unsigned, 3>& vertexIndexes){
	// 	std::array<float, 3> vertex;
	// 	for(unsigned char i = 0; i < vertexIndexes.size(); ++i){
	// 		vertex[i] = GetNumber(vertexIndexes[i]);
	// 	}
	// 	return vertex;
	// }
}

std::vector<float> GetOfficeModel(){
	const LayoutType& modelLayout = GetModelIndexes();

	std::vector<float> vertexes;

	for(const auto& index : modelLayout){
		std::array<float, 3> vertex = GetVertex(index);
		for(const auto& number : vertex){
			vertexes.push_back(number);
		}
	}

	return vertexes;
}
