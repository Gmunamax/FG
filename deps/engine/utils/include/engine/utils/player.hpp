#pragma once
#include <FGengine/renderable/camera.hpp>
#include <engine/utils/properties/timer.hpp>
#include <engine/utils/properties/movement.hpp>

class Walk{
public:
	void Update(glm::vec3& position, glm::vec3& rotation, double time){
		position.x += ((walkVector.x * glm::cos(glm::radians(rotation.z))) + (walkVector.y * glm::sin(glm::radians(rotation.z)))) * time;
		position.y += ((walkVector.y * glm::cos(glm::radians(rotation.z))) - (walkVector.x * glm::sin(glm::radians(rotation.z)))) * time;
	}

	void SetWalkX(float scalar){
		walkVector.x = scalar;
	}

	void SetWalkY(float scalar){
		walkVector.y = scalar;
	}

private:
	glm::vec3 walkVector{0};
};

class Look{
public:
	void Update(glm::vec3& rotation, double time){
		rotation.x += lookVector.x * time;
		rotation.y += lookVector.y * time;
		rotation.z += lookVector.z * time;
	}

	void SetYaw(float scalar){
		lookVector.x = scalar;
	}

	void SetPitch(float scalar){
		lookVector.z = scalar;
	}

	void SetRoll(float scalar){
		lookVector.y = scalar;
	}

private:
	glm::vec3 lookVector{0};
};

class Player{
public:
	enum class MovementType{
		On = 1,
		Reverse = -1,
		Off = 0
	};

	Player(){
		camera.SetProjectionMode(FGengine::Camera::ProjectionMode::Frustum);
	}

	void Jump(){
		constexpr double jumpPower = 5;
		if(camera.GetPosition().z >= 0)
			movement.ApplyVector({0,0,jumpPower});
	}

	void SetWalkX(MovementType type){
		walk.SetWalkX((int)type * walkSpeed);
	}

	void SetWalkY(MovementType type){
		walk.SetWalkY((int)type * walkSpeed);
	}

	void SetYaw(MovementType type){
		constexpr double speed = 180;
		look.SetYaw((int)type * speed);
	}

	void SetPitch(MovementType type){
		constexpr double speed = 180;
		look.SetPitch((int)type * speed);
	}

	void Update(){
		Timer::dataType time = drawTimer.GetTime();
		drawTimer.Reset();

		glm::vec3 position = {camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
		glm::vec3 rotation = {camera.GetRotation().x, camera.GetRotation().y, camera.GetRotation().z};
		position = -position;
		rotation.x = -rotation.x;

		movement.Update(position, time);
		walk.Update(position, rotation, time);
		look.Update(rotation, time);

		position = -position;
		rotation.x = -rotation.x;
		camera.SetPosition({position.x, position.y, position.z});
		camera.SetRotation({rotation.x, rotation.y, rotation.z});
		camera.ProceedUpdate();

	}

private:
	FGengine::Camera camera;
	Movement movement;
	Walk walk;
	static constexpr double walkSpeed = 3;
	Look look;
	Timer drawTimer;
};
