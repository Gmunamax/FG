#pragma once
#include "FGengine/structures/point.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FGengine/shaders/shaderprogram.hpp"

template <typename PointType>
class Position{
protected:
	PointType position;
	bool needupdate = false;

	void ProceedPosition(glm::mat4& mat);

public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
		needupdate = true;
	}
};

template <typename PointType>
class Rotation{
protected:
	PointType rotation;
	bool needupdate = false;

	void ProceedRotation(glm::mat4& mat);

public:
	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
		needupdate = true;
	}
};

template <typename PointType>
class Scale{
protected:
	PointType scale {1};
	bool needupdate = false;

	void ProceedScale(glm::mat4& mat);

public:
	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
		needupdate = true;
	}
};

template<typename PointType>
class Transform: public Position<PointType>, public Rotation<PointType>, public Scale<PointType>{
	glm::mat4 objm {1};
	glm::mat4 resobjm {1};

protected:
	void ProceedTransformations();
	void BindTransformations();
	Transform(){};
};



template<typename PointType> void Position<PointType>::ProceedPosition(glm::mat4& mat){
	// if(needupdate){
		mat = glm::translate(mat,glm::vec3{position.x,position.y,position.z});
		needupdate = false;
	// }
}

template<typename PointType> void Rotation<PointType>::ProceedRotation(glm::mat4& mat){
	// if(needupdate){
		if(rotation.x != 0)
			mat = glm::rotate(mat, (float)glm::radians(rotation.x), glm::vec3{1,0,0});
		if(rotation.y != 0)
			mat = glm::rotate(mat, (float)glm::radians(rotation.y), glm::vec3{0,1,0});
		if(rotation.z != 0)
			mat = glm::rotate(mat, (float)glm::radians(rotation.z), glm::vec3{0,0,1});
		needupdate = false;
	// }
}

template<typename PointType> void Scale<PointType>::ProceedScale(glm::mat4& mat){
	// if(needupdate){
		mat = glm::scale(mat,glm::vec3(scale.x,scale.y,scale.z));
		needupdate = false;
	// }
}

template<typename PointType> void Transform<PointType>::ProceedTransformations(){
	if (not ( Transform::Position::needupdate or
		 Transform::Rotation::needupdate or
		 Transform::Scale::needupdate ) )
		return;
	
	resobjm = glm::mat4{1};
	Transform::ProceedPosition(resobjm);
	Transform::ProceedRotation(resobjm);
	Transform::ProceedScale(resobjm);
}

template<typename PointType> void Transform<PointType>::BindTransformations(){
	ShaderProgram::SetObjectMatrix(&resobjm);
}