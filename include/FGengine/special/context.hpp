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
#include <glm/mat4x4.hpp>
#include "FGengine/backend/modernContext.hpp"
#include "uniformBuffer.hpp"

namespace FGengine{

class Context: public Backend::ModernContext{
public:
	struct cameraUniformBuffer{
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

private:
	UniformBuffer<cameraUniformBuffer> cameraUbo;

public:
	const UniformBuffer<cameraUniformBuffer>& GetCameraUniformBuffer(){
		return cameraUbo;
	}

	Context(const Backend::Window& win): Backend::ModernContext(win) {}
};

}
