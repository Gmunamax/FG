#define BOOST_TEST_MODULE modules tests
#include <boost/test/unit_test.hpp>
#include <algorithm.hpp>
#include <shared.hpp>
#include <print>

BOOST_AUTO_TEST_CASE(AlgorithmCorrectness){
	auto algorithmResult = PathFinder::algorithm::RunBFS(0, 4, graph);

	BOOST_TEST(algorithmResult.at(4) == 1);
	BOOST_TEST(algorithmResult.at(1) == 0);

	std::println("algorithm result:");
	for(auto e : algorithmResult)
		std::print("{} ", e);
}
