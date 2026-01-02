#pragma once
// #include "params/position.hpp"
// #include "params/rotation.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType>
class WorldPoint{
	Uniforms::Umat4 mat{"fg_viewmatrix"};
	bool needupdate = true;
	PointType position{0};
	PointType rotation{0};

protected:
	void ProceedTransformations(){
		if(needupdate){
			mat = 1;
			this->mat = glm::translate(this->mat.GetValue(), position);
			if(rotation.x != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.x), glm::dvec3{1,0,0});
			if(rotation.y != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.y), glm::dvec3{0,1,0});
			if(rotation.z != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.z), glm::dvec3{0,0,1});
			needupdate = false;
		}
	}
	Uniforms::Umat4* GetMatrix(){
		return &mat;
	}
	void SendMatrix(){
		mat.Send();
	}
	void SetShader(Shader*& newshader){
		mat.SetShader(newshader->ToGL());
	}
	
	// ?
	// WorldPoint(const char* matrixname){
	// 	mat = new {matrixname};
	// };
	// ~WorldPoint(){
	// 	delete mat;
	// }


public:

	const PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
	}

	const PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
	}
};