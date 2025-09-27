#pragma once
#include <vector>
#include "FGengine/structures/vertex.hpp"

namespace FgFloor{

	std::vector<Point3d> data{
		
		{-1,-1,-1},
		{-1,1,-1},
		{1,-1,-1},
		
		{1,1,-1},
		{-1,1,-1},
		{1,-1,-1}
		
	};

	Colord color = {0.2,0.2,0.9};

	std::vector<Vertex3d> Load(){
		std::vector<Vertex3d> vdata;
		for(auto point : data){
			vdata.push_back({point, color});
		}
		return vdata;
	}
}