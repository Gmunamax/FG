#pragma once
// #include "params/position.hpp"
// #include "params/rotation.hpp"
// #include "params/scale.hpp"
#include "FGengine/shaders/uniform.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType>
class Transform{

	Uniforms::Umat4 objm{"fg_objectmatrix"};

	bool needupdate = true;

protected:
	void ProceedTransformations(){
		if(this->needupdate){

			this->objm = 1;
			this->objm = glm::translate(this->objm.GetValue(), position);

			if(rotation.x != 0)
				this->objm = glm::rotate(this->objm.GetValue(), glm::radians(rotation.x), glm::dvec3{1,0,0});
			if(rotation.y != 0)
				this->objm = glm::rotate(this->objm.GetValue(), glm::radians(rotation.y), glm::dvec3{0,1,0});
			if(rotation.z != 0)
				this->objm = glm::rotate(this->objm.GetValue(), glm::radians(rotation.z), glm::dvec3{0,0,1});

			this->objm = glm::scale(this->objm.GetValue(), scale);

			needupdate = false;
		}
	}

	Uniforms::Umat4* GetMatrix(){
		return &objm;
	}

	void SendMatrix(){
		objm.Send();
	}

	void SetShader(Shader*& newshader){
		objm.SetShader(newshader->ToGL());
	}

	Transform(){};

	PointType position{0};
	PointType rotation{0};
	PointType scale{1};


public:
	PointType& GetPosition(){
		return this->position;
	}
	void SetPosition(PointType newposition){
		this->position = newposition;
		this->needupdate = true;
	}

	

	PointType& GetRotation(){
		return this->rotation;
	}
	void SetRotation(PointType newrotation){
		this->rotation = newrotation;
		this->needupdate = true;
	}

	

	PointType& GetScale(){
		return this->scale;
	}
	void SetScale(PointType newscale){
		this->scale = newscale;
		this->needupdate = true;
	}

};