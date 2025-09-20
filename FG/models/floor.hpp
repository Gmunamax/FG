#pragma once
#include "FGengine/objects/model/model.hpp"

namespace Floor{
	namespace floorfaces{
		Point3d part[4] = {
			{0,0,0},
			{1,0,0},
			{1,1,0},
			{0,1,0},
		};
	}
	Colord cellcolor1 = {1,1,1};
	Colord cellcolor2 = {0.1,0.1,0.1};
	bool swapcolors = false;

	float cellsize = 0.5;
	short cellcountw = 4;
	short cellcounth = 4;

	std::vector<Vertex3d> GenerateFloor(){

		std::vector<Point3d> cell = {
			{0,0,0},
			{1,0,0},
			{1,1,0},

			{0,0,0},
			{0,1,0},
			{1,1,0},
		};

		// Face3d cell1 = {
		// 	floorfaces::part,4,cellcolor1,{0,0,1},
		// };
		// Face3d cell2 = {
		// 	floorfaces::part,4,cellcolor2,{0,0,1},
		// };
		Colord cells[2]{
			cellcolor1,
			cellcolor2
		};

		std::vector<Vertex3d> result {};

		bool changecolorw = false;
		bool changecolorh = swapcolors;
		short chcol = 0;
		//Face3d* sourcecell;
		for(short cellh = 0; cellh < cellcounth; cellh+=1){
			changecolorw = changecolorh;
			for(short cellw = 0; cellw < cellcountw; cellw+=1){

				for(short i = 0; i < cell.size(); i++){
					Point3d ttt = cell.at(i);
					ttt = ttt * Point3d{cellsize,cellsize,0} + Point3d{(double)cellw*cellsize,(double)cellh*cellsize,0};
					result.push_back({ ttt,cells[changecolorw] });
				}

				changecolorw = !changecolorw;
			}
			changecolorh = !changecolorh;
		}

		// std::cout << "Floor last point:\n" << result.at(result.size()-1).x << ",\n" << result.at(result.size()-1).y << ",\n" << result.at(result.size()-1).z << "\n\n";

		return result;

	}

	std::vector<Vertex3d> Load(){

		return GenerateFloor();

	}
}