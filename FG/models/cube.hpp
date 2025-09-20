#pragma once
#include "FGengine/objects/model/model.hpp"


namespace Cube{
	std::vector<Point3d> cubetriangles{
		//l
			{1,-1,-1},
			{1,1,-1},
			{1,1,1},
		
		
			{1,-1,-1},
			{1,-1,1},
			{1,1,1},
		
		//r
			{-1,-1,-1},
			{-1,1,-1},
			{-1,1,1},
		
		
			{-1,-1,-1},
			{-1,-1,1},
			{-1,1,1},
		
		//t
			{1,-1,1},
			{-1,-1,1},
			{-1,1,1},
		
		
			{1,-1,1},
			{1,1,1},
			{-1,1,1},
		
		//bo
			{1,-1,-1},
			{-1,-1,-1},
			{-1,1,-1},
		
		
			{1,-1,-1},
			{1,1,-1},
			{-1,1,-1},
		
		//f
			{-1,1,1},
			{1,1,1},
			{1,1,-1},
		
		
			{-1,1,1},
			{-1,1,-1},
			{1,1,-1},
		
		//b
			{-1,-1,1},
			{1,-1,1},
			{1,-1,-1},
		
		
			{-1,-1,1},
			{-1,-1,-1},
			{1,-1,-1},
		
	};

	std::vector<Vertex3d> CreateVertexVector(){
		// std::vector<Point3d*> cubeb {
		// 	l1,l2,
		// 	r1,r2,
		// 	t1,t2,
		// 	bo1,bo2,
		// 	f1,f2,
		// 	ba1,ba2
		// };

		
		std::vector<Vertex3d> cube;
		for(auto e : cubetriangles){
			//for(short i = 0; i < 3; i++){
				cube.push_back({e, {4,0,4}});
			//}
		}
		std::cout << "Cube size: " << cube.size() << std::endl;
		return cube;
	}

	std::vector<Vertex3d> Load(){
		return CreateVertexVector();
	}
}

namespace Triangle{
	Point3d tr[] {
		{-0.5, -0.5, 0.0}, // left
    	{0.5, -0.5, 0.0}, // right 
    	{0.0,  0.5, 0.0}  // top   
	};
	Colord color = {1,0,0};

	std::vector<Vertex3d> Load(){
		std::vector<Vertex3d> output;
		for(auto e : tr){
			output.push_back({e,color});
		}
		return output;
	}
}

namespace Pyramid{
	const Point3d pts[] {
		{-0.5,-0.5,-0.5},
		{ 0.5,-0.5,-0.5},
		{ 0  , 0.5,-0.5},

		{ 0  , 0  , 0.5},
	};
	const int ptssize = 4;
	
	const unsigned short elms[] {
		0,1,3,
		1,2,3,
		0,2,3,
		0,1,2
	};

	const int elmssize = 6;

	Colord color =  {4,0,4};

	std::vector<unsigned short> Index(){
		std::vector<unsigned short> out;
		for(auto e : elms){
			out.push_back(e);
		}
		return out;
	}

	std::vector<Vertex3d> Load(){
		std::vector<Vertex3d> out;
		for(auto e : elms){
			out.push_back({pts[e],color});
		}
		return out;
	}

	// Vertex3d* Load(){
	// 	Vertex3d* out = new Vertex3d[ptssize];
	// 	for(int i = 0; i < ptssize; i++){
	// 		out[i] = {pts[i],color};
	// 	}
	// 	return out;
	// }
}