#include <FGengine/renderable/camera.hpp>
#include <print>
#include "timer.hpp"

class Player{
public:
	Player(){
		camera.SetProjectionMode(FGengine::Camera::ProjectionMode::Frustum);
	}

	void Jump(){
		constexpr double jumpPower = 5;
		if(camera.GetPosition().z >= 0)
			movementVector.z += jumpPower;
		std::println("Jump!");
	}

	void Draw(){
		static Timer drawTimer;
		Timer::dataType time = drawTimer.GetTime();
		drawTimer.Reset();

		{
			auto position = camera.GetPosition();
			position.z = -position.z;
			position.z = position.z + movementVector.z * time - (gravity * time * time)/2.0l;
			if(position.z < 0){
				position.z = 0;
				movementVector.z = 0;
			}
			position.z = -position.z;
			camera.SetPosition(position);
			// std::println("cam.pos: {:.3f}, {:.3f}, {:.3f}", position.x, position.y, position.z);
			// std::println("z vector: {:.3f}", movementVector.z);
			// std::println("time: {:.8f}", time);
			// std::println();
		}

		{
			movementVector.z = movementVector.z - gravity * time;
		}

		camera.ProceedUpdate();
	}

private:
	FGengine::Camera camera;
	glm::dvec3 movementVector{0};
	double gravity = 9.80665;
	double weight = 1;

};
