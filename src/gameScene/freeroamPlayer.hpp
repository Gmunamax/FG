#include <engine/utils/player.hpp>
#include <engine/graphics/camera.hpp>

class FreeroamPlayer: public Player{
public:
	enum class MovementType{
		On = 1,
		Reverse = -1,
		Off = 0
	};

	void SetWalkX(MovementType scalar){
		walkVector.x = (int)scalar * walkSpeed;
	}

	void SetWalkY(MovementType scalar){
		walkVector.y = (int)scalar * walkSpeed;
	}


	void SetYaw(MovementType scalar){
		lookVector.x = (int)scalar * rotationSpeed;
	}

	void SetPitch(MovementType scalar){
		lookVector.z = (int)scalar * rotationSpeed;
	}

	void SetRoll(MovementType scalar){
		lookVector.y = (int)scalar * rotationSpeed;
	}


	void Jump(){
		if(camera.GetPosition().z <= 0)
			forces.ApplyVector({0,0,jumpPower});
	}


	void SetWalkSpeed(double newSpeed){
		walkSpeed = newSpeed;
	}

	void SetRotationSpeed(double newSpeed){
		rotationSpeed = newSpeed;
	}

	void SetJumpPower(double newJumpPower){
		jumpPower = newJumpPower;
	}

protected:
	void UpdateProperties(TimeType timeDelta){
		glm::vec3 position = camera.GetPosition();
		glm::vec3 rotation = camera.GetRotation();

		forces.Update(position, timeDelta);

		rotation += lookVector * timeDelta;

		float zRotation = glm::radians(rotation.z);
		position.x += ((walkVector.x * glm::cos(zRotation)) + (walkVector.y * glm::sin(zRotation))) * timeDelta;
		position.y += ((walkVector.y * glm::cos(zRotation)) - (walkVector.x * glm::sin(zRotation))) * timeDelta;

		camera.SetPosition(position);
		camera.SetRotation(rotation);

		camera.Update();
	}

private:
	Camera camera;
	Movement forces;
	glm::vec3 lookVector{0};
	glm::vec3 walkVector{0};
	double walkSpeed = 3;
	double rotationSpeed = 180;
	double jumpPower = 5;
};
