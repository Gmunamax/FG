#include <boost/test/unit_test.hpp>
#include "gameScene/office.hpp"

BOOST_AUTO_TEST_SUITE(OfficeGraphTests)

struct OfficeGraphFixture{
	PathFinder::OfficeGraph graph;
	PathFinder::PathFinder pathFinder{graph.GetGraph()};

	void TestPathFinder(int start, int finish){
		auto path = pathFinder.FindPath(start, finish);
		
		int step = -1;
		while(!path.empty()){
			step = path.back();
			path.pop();
		}
		BOOST_TEST(step == finish);
	}

	void TestPathLength(int start, int finish, int length){
		auto path = pathFinder.FindPath(start, finish);

		BOOST_TEST(path.size() == length);
	}
};

BOOST_FIXTURE_TEST_CASE(GetNearestLocation, OfficeGraphFixture){
	using enum OfficeGraph::LocationsEnum;
	BOOST_TEST(graph.GetNearestLocation({2, 6, 1}) == BehindTheFrontDoor);
	BOOST_TEST(graph.GetNearestLocation({-3, 5, 1}) == BehindTheFrontOfficeWall);
	BOOST_TEST(graph.GetNearestLocation({0, -5, 6}) == FarAway);
}

BOOST_FIXTURE_TEST_CASE(PathCorrectness, OfficeGraphFixture){
	using enum OfficeGraph::LocationsEnum;
	TestPathFinder(BehindTheFrontDoor, FarAway);
	TestPathFinder(FarAway, BehindTheFrontDoor);
	TestPathFinder(BehindTheFrontDoor, BehindTheSideDoor);
	TestPathFinder(BehindTheSideDoor, BehindTheFrontDoor);
	TestPathFinder(BehindTheSideDoor, FarAway);
	TestPathFinder(FarAway, BehindTheSideDoor);
}

BOOST_FIXTURE_TEST_CASE(PathLength, OfficeGraphFixture){
	using enum OfficeGraph::LocationsEnum;
	TestPathLength(FarAway, NearTheSideDoor, 2);
}

BOOST_AUTO_TEST_SUITE_END()
