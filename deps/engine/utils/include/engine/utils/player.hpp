#pragma once
#include <FGengine/renderable/camera.hpp>
#include <engine/utils/properties/timer.hpp>
#include <engine/utils/properties/movement.hpp>

class Walk{
public:
	enum class WalkType{
		On = 1,
		Reverse = -1,
		Off = 0
	};

	void Update(glm::vec3& position, double time){
		position.x += walkVector.x * time;
		position.y += walkVector.y * time;
	}

	void SetWalkX(WalkType type){
		walkVector.x = (int)type * speed;
	}

	void SetWalkY(WalkType type){
		walkVector.y = (int)type * speed;
	}

private:
	glm::vec3 walkVector{0};
	float speed = 1;
};

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

	void SetWalkX(Walk::WalkType type){
		walk.SetWalkX(type);
	}

	void SetWalkY(Walk::WalkType type){
		walk.SetWalkY(type);
	}

	void Update(){
		Timer::dataType time = drawTimer.GetTime();
		drawTimer.Reset();

		glm::vec3 position = {camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
		position = -position;
		movement.Update(position, time);
		walk.Update(position, time);
		position = -position;
		camera.SetPosition({position.x, position.y, position.z});
		camera.ProceedUpdate();

	}

private:
	FGengine::Camera camera;
	Movement movement;
	Walk walk;
	Timer drawTimer;
};
