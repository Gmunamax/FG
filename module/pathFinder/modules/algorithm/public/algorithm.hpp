#include <vector>

namespace PathFinder::algorithm{

	using Graph = std::vector<std::vector<int>>;

	std::vector<int> RunBFS(int start, int finish, const Graph& graph);

}
