#include <pathFinder.hpp>
#include <algorithm.hpp>
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
