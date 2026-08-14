// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#pragma once
#include "FGengine/properties/worldpoint.hpp"
#include "FGengine/structures/aspectratio.hpp"
#include "FGengine/special/defaults.hpp"

namespace FGengine{

class Camera: public PointTransform<3, floatType>{
//viewMatrix

private:
	void ProceedTransformations(typename Camera::PointTransform::MatrixType& matrix);

//viewMatrix


//projectionMatrix

private:
	void ProceedProjection(glm::mat<4, 4, floatType>& matrix);

//projectionMatrix


//aspectratio

private:
	const AspectRatio* aspectratio = Defaults::aspectRatio;

public:
	void SetAspectRatio(const AspectRatio* newaspectratio){
		aspectratio = newaspectratio;
	}
	const AspectRatio* GetAspectRatio() const{
		return aspectratio;
	}

//aspectratio


//fov

private:
	floatType fov = 75 * M_PI/180;

public:
	void SetFOV(const floatType& newfov){
		fov = glm::radians(newfov);
	}
	const floatType& GetFOV() const{
		return fov;
	}

//fov


//viewdistance

private:
	floatType nearz = 1;
	floatType farz = 200;

public:
	void SetNearDistance(const floatType& newNearZ){
		nearz = newNearZ;
	}
	void SetFarDistance(const floatType& newFarZ){
		farz = newFarZ;
	}
	void SetDistance(const floatType& newNearZ, const floatType& newFarZ){
		SetNearDistance(newNearZ);
		SetFarDistance(newFarZ);
	}
	const floatType& GetNearDistance() const{
		return nearz;
	}
	const floatType& GetFarDistance() const{
		return farz;
	}

//viewdistance


//projection

public:
	enum class ProjectionMode{
		Frustum,	/* Perspective */
		Ortho,		/* Orthogonal */
		Ui			/* Orthogonal with inverted depth-test */
	};

private:
	ProjectionMode projectionmode = ProjectionMode::Ortho;

public:
	void SetProjectionMode(ProjectionMode newProjectionMode){
		projectionmode = newProjectionMode;
	}

//projection


//main

public:
	Camera() {};

	void ProceedUpdate();

//main
};

}
