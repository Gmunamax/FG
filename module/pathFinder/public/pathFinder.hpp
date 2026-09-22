#pragma once
#include <queue>
#include <vector>

namespace PathFinder{

	using Graph = std::vector<std::vector<int>>;

	class PathFinder{
	public:
		using Path = std::queue<int>;

		PathFinder(const Graph& g):
			graph{g}
		{}

		Path FindPath(int start, int finish);

	private:
		const Graph& graph;
	};

}
