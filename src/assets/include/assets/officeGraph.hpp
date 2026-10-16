#pragma once
#include <vector>
#include <engine/graphics/model.hpp>
#include <pathFinder.hpp>

namespace Assets{

class OfficeGraph{
public:
	enum LocationsEnum{
		BehindTheFrontDoor = 0,
		BehindTheFrontOfficeWall,
		BehindTheSideDoor,
		NearTheSideDoor,
		HallwayNearTheFrontWall,
		HallwayNearTheSideWall,
		FarAway,
		Null = -1
	};

	OfficeGraph(){
		for(const Location& location : locationsGraph){
			graph.push_back(location.neighbors);
		}
	}

	const PathFinder::Graph& GetGraph(){
		return graph;
	}

	static LocationsEnum GetNearestLocation(glm::vec3 position){
		LocationsEnum nearest = (LocationsEnum)0;
		float shortes = glm::length(locationsGraph[0].position - position);
		for(unsigned i = 0; i < locationsGraph.size(); ++i){
			float distance = glm::length(locationsGraph[i].position - position);
			if(distance < shortes){
				shortes = distance;
				nearest = (LocationsEnum)i;
			}
		}
		return nearest;
	}

	static glm::vec3 GetLocationPosition(LocationsEnum location){
		return locationsGraph[location].position;
	}

private:
	struct Location{
		glm::vec3 position;
		std::vector<int> neighbors;
	};

	static inline const std::vector<Location> locationsGraph{
		{{2, 5, 1}, {BehindTheFrontOfficeWall}},
		{{-4, 5, 1}, {HallwayNearTheFrontWall, BehindTheFrontDoor}},

		// Locations below are just fillers for testing purposes
		{{-5.5, -1, 1}, {NearTheSideDoor}},
		{{-6, 2, 1}, {HallwayNearTheSideWall, BehindTheSideDoor}},
		{{-5, 6, 1}, {FarAway, BehindTheFrontOfficeWall}},
		{{-7, 4, 1}, {FarAway, NearTheSideDoor}},
		{{-7, 6, 1}, {HallwayNearTheFrontWall, HallwayNearTheSideWall}}
	};

	PathFinder::Graph graph;
};

}
