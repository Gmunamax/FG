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
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

class PathWalker{
public:
	void WalkTo(const glm::vec3& newDestination){
		destination = newDestination;
	}

	void Update(glm::vec3& position, glm::vec3& rotation, float timeDelta){
		glm::vec3 distance = destination - position;
		if(glm::length(distance) < finishCheckError){
			return;
		}
		glm::vec3 speedVector = glm::normalize(distance) * walkSpeed;
		position += speedVector * timeDelta;
	}

private:
	glm::vec3 destination;
	float walkSpeed = 3;
	float finishCheckError = 0.3;
};
