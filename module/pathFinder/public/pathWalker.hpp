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
