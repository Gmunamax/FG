#pragma once
#include <glm/vec3.hpp>

class Movement{
public:
	void Update(glm::vec3& position, double time){
		position.z = position.z + movementVector.z * time - (gravity * time * time)/2.0l;
		movementVector.z = movementVector.z - gravity * time;
		if(position.z < 0){
			position.z = 0;
			movementVector.z = 0;
		}
	}

	void ApplyVector(glm::dvec3 vector){
		movementVector += vector;
	}

private:
	glm::dvec3 movementVector{0};
	static constexpr double gravity = 9.80665;
	static constexpr double weight = 1;
};
