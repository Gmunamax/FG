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
#define BOOST_TEST_MODULE modules tests
#include <boost/test/unit_test.hpp>
#include <pathFinder.hpp>
#include <shared.hpp>
#include <print>

struct PathFinderFixture{
	int GetPathLength(int start, int finish){
		auto path = pathFinder.FindPath(start, finish);

		return path.size();
	}

	int GetFlushedPath(int start, int finish){
		auto path = pathFinder.FindPath(start, finish);

		int step = -1;
		while(!path.empty()){
			step = path.front();
			path.pop();
		}
		return step;
	}

	PathFinder::PathFinder pathFinder{graph};
};

BOOST_FIXTURE_TEST_CASE(PathCorrectness, PathFinderFixture){
	int flushedPath = GetFlushedPath(0, 4);
	// BOOST_TEST(flushedPath == 2 || flushedPath == 3);
	BOOST_TEST(flushedPath == 3);
	BOOST_TEST(GetFlushedPath(6, 1) == 1);
	BOOST_TEST(GetFlushedPath(5, 3) == 3);
	BOOST_TEST(GetFlushedPath(4, 0) == 0);
	auto path = pathFinder.FindPath(0, 4);
	while(!path.empty()){
		std::print("{} ", path.front());
		path.pop();
	}
	std::println();
}

BOOST_FIXTURE_TEST_CASE(PathLength, PathFinderFixture){
	BOOST_TEST(GetPathLength(5, 0) == 2);
	BOOST_TEST(GetPathLength(0, 6) == 3);
}
