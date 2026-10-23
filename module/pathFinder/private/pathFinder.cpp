// pathFinder - a library for finding pathes
// Copyright (C) 2026 Gmunamax <https://github.com/Gmunamax/FG>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include <pathFinder.hpp>
#include "algorithm.hpp"
#include <algorithm>

namespace PathFinder{

	std::vector<int> GetPathFromAlgorithmResult(int destination, std::span<int> vertexesParents){
		std::vector<int> tempPath;
		if (!vertexesParents.empty()){ 

			int v = destination;
			while(v != -1){
				tempPath.push_back(v);
				v = vertexesParents[v];
			}
			
		}

		return tempPath;
	}

	PathFinder::Path ConvertToPath(std::span<int> tempPath){
		PathFinder::Path path;

		std::reverse(tempPath.begin(), tempPath.end());
		for (int v : tempPath){
			path.push(v);
		}
		
		return path;
	}

	PathFinder::Path PathFinder::FindPath(int start, int finish){
		std::vector<int> vertexesParents = algorithm::RunBFS(start, finish, graph);
		auto tempPath = GetPathFromAlgorithmResult(finish, vertexesParents);
		PathFinder::Path path = ConvertToPath(tempPath);
		return path;
	}

}
