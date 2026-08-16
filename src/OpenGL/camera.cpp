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
#include "FGengine/renderable/camera.hpp"
#include <gl/gl.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/special/uniformBuffer.hpp"
#include "../currentContext/currentContext.hpp"

using namespace FGengine;

void Camera::ProceedTransformations(typename Camera::PointTransform::MatrixType& matrix){
	if(Camera::PointTransform::IsNeedUpdate()){
		matrix = {1};
		matrix = Camera::PointTransform::TransformRotation(matrix);
		matrix = Camera::PointTransform::TransformPosition(matrix);
	}
}

void Camera::ProceedProjection(glm::mat<4, 4, floatType>& matrix){
	switch(projectionmode){
	case ProjectionMode::Frustum:
		glDepthFunc(GL_LESS);
		matrix = glm::perspective<floatType>(fov, *aspectratio, nearz, farz);
		break;

	case ProjectionMode::Ortho:
		glDepthFunc(GL_LESS);
		matrix = glm::ortho<floatType>(-*aspectratio, *aspectratio, -1.0f, 1.0f, nearz, farz);
		break;

	case ProjectionMode::Ui:
		glDepthFunc(GL_GEQUAL);
		matrix = glm::ortho<floatType>(-*aspectratio, *aspectratio, -1.0f, 1.0f);
		break;
	}
}

void Camera::ProceedUpdate(){
	Context::cameraUniformBuffer cameraBuffer;
	ProceedTransformations(cameraBuffer.viewMatrix);
	ProceedProjection(cameraBuffer.projectionMatrix);
	GetCurrentContext().GetCameraUniformBuffer().Update(cameraBuffer);
}