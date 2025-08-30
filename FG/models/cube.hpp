#pragma once
#include "FGengine/objects/model/model.hpp"


namespace Cube{
	namespace cubetriangles{
		Point3d l1[] {
			{1,-1,-1},
			{1,1,-1},
			{1,1,1},
		};
		Point3d l2[] {
			{1,-1,-1},
			{1,-1,1},
			{1,1,1},
		};
		Point3d r1[] {
			{-1,-1,-1},
			{-1,1,-1},
			{-1,1,1},
		};
		Point3d r2[] {
			{-1,-1,-1},
			{-1,-1,1},
			{-1,1,1},
		};
		Point3d t1[] {
			{1,-1,1},
			{-1,-1,1},
			{-1,1,1},
		};
		Point3d t2[] {
			{1,-1,1},
			{1,1,1},
			{-1,1,1},
		};
		Point3d bo1[] {
			{1,-1,-1},
			{-1,-1,-1},
			{-1,1,-1},
		};
		Point3d bo2[] {
			{1,-1,-1},
			{1,1,-1},
			{-1,1,-1},
		};
		Point3d f1[] {
			{-1,1,1},
			{1,1,1},
			{1,1,-1},
		};
		Point3d f2[] {
			{-1,1,1},
			{-1,1,-1},
			{1,1,-1},
		};
		Point3d ba1[] {
			{-1,-1,1},
			{1,-1,1},
			{1,-1,-1},
		};
		Point3d ba2[] {
			{-1,-1,1},
			{-1,-1,-1},
			{1,-1,-1},
		};
	}

	std::vector<Point3d> CreateVertexVector(){
		using namespace cubetriangles;
		std::vector<Point3d*> cubeb {
			l1,l2,
			r1,r2,
			t1,t2,
			bo1,bo2,
			f1,f2,
			ba1,ba2
		};
		std::vector<Point3d> cube;
		for(auto e : cubeb){
			for(short i = 0; i < 3; i++){
				cube.push_back(e[i]);
			}
		}
		return cube;
	}

	std::vector<Point3d> Load(){
		return CreateVertexVector();
	}
}