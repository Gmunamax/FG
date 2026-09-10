#pragma once
#include <FGengine/renderable/camera.hpp>
#include <engine/utils/properties/timer.hpp>
#include <engine/utils/properties/movement.hpp>

class Player{
public:
	Player(){
		camera.SetProjectionMode(FGengine::Camera::ProjectionMode::Frustum);
	}

	void Jump(){
		constexpr double jumpPower = 5;
		if(camera.GetPosition().z >= 0)
			movement.ApplyVector({0,0,jumpPower});
	}

	void Update(){
		Timer::dataType time = drawTimer.GetTime();
		drawTimer.Reset();

		glm::vec3 position = {camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
		position.z = -position.z;
		movement.Update(position, time);
		position.z = -position.z;
		camera.SetPosition({position.x, position.y, position.z});
		camera.ProceedUpdate();
	}

private:
	FGengine::Camera camera;
	Movement movement;
	Timer drawTimer;
};
