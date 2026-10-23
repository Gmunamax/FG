#include "algorithm.hpp"
#include <queue>

namespace PathFinder::algorithm{

	std::vector<int> RunBFS(int start, int finish, const Graph& graph){
		int n = graph.size();
		std::queue<int> queue;
		std::vector<bool> visited(n, false);
		std::vector<int> vertexesParents(n, -1);

		visited[start] = true;
		queue.push(start);

		bool pathFound = false;

		while (!queue.empty()){
			int current = queue.front();
			queue.pop();

			if (current == finish){
				pathFound = true;
				break;
			}

			for (int neighbor : graph[current]){
				if (!visited[neighbor]){
					visited[neighbor] = true;
					vertexesParents[neighbor] = current; // Запоминаем, откуда пришли
					queue.push(neighbor);
				}
			}
		}

		return vertexesParents;
	}

}
