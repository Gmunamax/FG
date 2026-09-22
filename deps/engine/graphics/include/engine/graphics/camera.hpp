#pragma once
#include <FGengine/camera.hpp>

class Camera: public FGengine::Camera{
public:
	using VectorType = glm::vec3;
	using PositionType = VectorType;
	using RotationType = VectorType;

	Camera(){
		SetProjectionMode(FGengine::Camera::ProjectionMode::Frustum);
	}

	PositionType GetPosition(){
		glm::vec3 position = {FGengine::Camera::GetPosition().x, FGengine::Camera::GetPosition().y, FGengine::Camera::GetPosition().z};
		position = -position;
		return position;
	}

	RotationType GetRotation(){
		RotationType rotation = {FGengine::Camera::GetRotation().x, FGengine::Camera::GetRotation().y, FGengine::Camera::GetRotation().z};
		rotation.x = -rotation.x;
		return rotation;
	}

	void SetPosition(const PositionType& newPosition){
		FGengine::Camera::SetPosition({-newPosition.x, -newPosition.y, -newPosition.z});
	}
	
	void SetRotation(const RotationType& newRotation){
		FGengine::Camera::SetRotation({-newRotation.x, newRotation.y, newRotation.z});
	}

	void Update(){
		ProceedUpdate();
	}

};
