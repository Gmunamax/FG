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
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/structures/types.hpp"
#include "FGengine/structures/aspectratio.hpp"
#include "FGengine/defaults.hpp"

namespace FGengine{

class ProjectionMatrix{
public:
	enum class ProjectionMode{
		Frustum,
		Ortho,
	};

	using ProjectionMatrixType = glm::mat4;

	ProjectionMatrixType CalculateProjectionMatrix(){
		ProjectionMatrixType matrix;
		switch(projectionmode){
		case ProjectionMode::Frustum:
			matrix = glm::perspective<floatType>(fov, *aspectratio, nearz, farz);
			break;

		case ProjectionMode::Ortho:
			matrix = glm::ortho<floatType>(-*aspectratio, *aspectratio, -1.0f, 1.0f, nearz, farz);
			break;
		}
		return matrix;
	}

	ProjectionMode GetProjectionMatrix(){
		return projectionmode;
	}
	void SetProjectionMode(ProjectionMode newProjectionMode){
		projectionmode = newProjectionMode;
	}

	const floatType& GetNearDistance() const{
		return nearz;
	}
	void SetNearDistance(const floatType& newNearZ){
		nearz = newNearZ;
	}

	const floatType& GetFarDistance() const{
		return farz;
	}
	void SetFarDistance(const floatType& newFarZ){
		farz = newFarZ;
	}

	const floatType& GetFOV() const{
		return fov;
	}
	void SetFOV(const floatType& newfov){
		fov = glm::radians(newfov);
	}

	const AspectRatio* GetAspectRatio() const{
		return aspectratio;
	}
	void SetAspectRatio(const AspectRatio* newaspectratio){
		aspectratio = newaspectratio;
	}

private:
	ProjectionMode projectionmode = ProjectionMode::Ortho;
	floatType nearz = 1;
	floatType farz = 200;
	floatType fov = 75 * M_PI/180;
	const AspectRatio* aspectratio = Defaults::aspectRatio;
};

}
