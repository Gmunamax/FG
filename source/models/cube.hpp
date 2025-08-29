#pragma once
#include "../objects/model/model.hpp"

namespace Cube{
	namespace cubefaces{
		Vertex3d left[4] = {
			{1,-1,-1},
			{1,1,-1},
			{1,1,1},
			{1,-1,1}
		};
		Vertex3d right[4] = {
			{-1,-1,1},
			{-1,-1,-1},
			{-1,1,-1},
			{-1,1,1},
		};
		Vertex3d top[4] = {
			{1,-1,1},
			{-1,-1,1},
			{-1,1,1},
			{1,1,1}
		};
		Vertex3d bottom[4] = {
			{1,-1,-1},
			{-1,-1,-1},
			{-1,1,-1},
			{1,1,-1}
		};
		Vertex3d front[4] = {
			{-1,1,1},
			{1,1,1},
			{1,1,-1},
			{-1,1,-1}
		};
		Vertex3d back[4] = {
			{-1,-1,1},
			{1,-1,1},
			{1,-1,-1},
			{-1,-1,-1}
		};
	}

	namespace cubetriangles{
		Vertex3d l1[] {
			{1,-1,-1},
			{1,1,-1},
			{1,1,1},
		};
		Vertex3d l2[] {
			{1,-1,-1},
			{1,-1,1},
			{1,1,1},
		};
		Vertex3d r1[] {
			{-1,-1,-1},
			{-1,1,-1},
			{-1,1,1},
		};
		Vertex3d r2[] {
			{-1,-1,-1},
			{-1,-1,1},
			{-1,1,1},
		};
		Vertex3d t1[] {
			{1,-1,1},
			{-1,-1,1},
			{-1,1,1},
		};
		Vertex3d t2[] {
			{1,-1,1},
			{1,1,1},
			{-1,1,1},
		};
		Vertex3d bo1[] {
			{1,-1,-1},
			{-1,-1,-1},
			{-1,1,-1},
		};
		Vertex3d bo2[] {
			{1,-1,-1},
			{1,1,-1},
			{-1,1,-1},
		};
		Vertex3d f1[] {
			{-1,1,1},
			{1,1,1},
			{1,1,-1},
		};
		Vertex3d f2[] {
			{-1,1,1},
			{-1,1,-1},
			{1,1,-1},
		};
		Vertex3d ba1[] {
			{-1,-1,1},
			{1,-1,1},
			{1,-1,-1},
		};
		Vertex3d ba2[] {
			{-1,-1,1},
			{-1,-1,-1},
			{1,-1,-1},
		};
	}

	std::vector<Vertex3d> CreateVertexVector(){
		using namespace cubetriangles;
		std::vector<Vertex3d*> cubeb {
			l1,l2,
			r1,r2,
			t1,t2,
			bo1,bo2,
			f1,f2,
			ba1,ba2
		};
		std::vector<Vertex3d> cube;
		for(auto e : cubeb){
			for(short i = 0; i < 3; i++){
				e[i].SetPosition(e[i].GetPosition() - Point3d{0,0,0});
				cube.push_back(e[i]);
			}
		}
		return cube;
	}

	Face3d cubea[6] = {
		{ cubefaces::front,  4, {1,0,0}, {0,-1,0} },
		{ cubefaces::right,  4, {0,1,0}, {1,0,0} },
		{ cubefaces::back,   4, {0,0,1}, {0,1,0} },
		{ cubefaces::left,   4, {1,1,0}, {-1,0,0} },
		{ cubefaces::top,    4, {0,1,1}, {0,0,-1} },
		{ cubefaces::bottom, 4, {1,0,1}, {0,0,1} },
	};

	std::vector<Point3d> Load(){
		std::vector<Vertex3d> tt = CreateVertexVector();
		std::vector<Point3d> t;
		for(auto f : tt){
			t.push_back(f.GetPosition());
		}
		return t;
		//return {cubea,6};
	}
}

// namespace OCube{
// 	namespace cubefaces{
// 		Vertex3d left[4] = {
// 			{1,-1,-1},
// 			{1,1,-1},
// 			{1,1,1},
// 			{1,-1,1}
// 		};
// 		Vertex3d right[4] = {
// 			{-1,-1,1},
// 			{-1,-1,-1},
// 			{-1,1,-1},
// 			{-1,1,1},
// 		};
// 		Vertex3d top[4] = {
// 			{1,-1,1},
// 			{-1,-1,1},
// 			{-1,1,1},
// 			{1,1,1}
// 		};
// 		Vertex3d bottom[4] = {
// 			{1,-1,-1},
// 			{-1,-1,-1},
// 			{-1,1,-1},
// 			{1,1,-1}
// 		};
// 		Vertex3d front[4] = {
// 			{-1,1,1},
// 			{1,1,1},
// 			{1,1,-1},
// 			{-1,1,-1}
// 		};
// 		Vertex3d back[4] = {
// 			{-1,-1,1},
// 			{1,-1,1},
// 			{1,-1,-1},
// 			{-1,-1,-1}
// 		};
// 	}
// 	Face3d cubea[6] = {
// 		{ cubefaces::front,  4, {1,0,0}, {0,-1,0} },
// 		{ cubefaces::right,  4, {0,1,0}, {1,0,0} },
// 		{ cubefaces::back,   4, {0,0,1}, {0,1,0} },
// 		{ cubefaces::left,   4, {1,1,0}, {-1,0,0} },
// 		{ cubefaces::top,    4, {0,1,1}, {0,0,-1} },
// 		{ cubefaces::bottom, 4, {1,0,1}, {0,0,1} },
// 	};

// 	Model3d Load(){
// 		return {cubea,6};
// 	}
// }

namespace Frame{
	std::vector<Vertex3d> vectors {
		{-0.5,-0.5,-1},
		{0.5,-0.5,-1},
		{0.5,0.5,-1},

		{-0.5,-0.5,-1},
		{-0.5,0.5,-1},
		{0.5,0.5,-1},
	};

	std::vector<Vertex3d> Load(){
		// std::vector<Vertex3d> t = vectors;
		// for(std::vector<Vertex3d>::reference v : t){
		// 	v.SetPosition(v.GetPosition() - Point3d{0,0,0});
		// }
		return vectors;
	}
}