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
#include <GL/glew.h>

namespace FGengine {

template<typename StructureType>
class UniformBuffer{
	static inline GLuint freeBindingPoint = 0;
	GLuint bindingPoint;
	
	GLuint uniformBuffer;

	void Bind() const{
		glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
	}

public:
	GLuint GetBindingPoint() const{
		return bindingPoint;
	}

	void Update(const StructureType& newStorage){
		Bind();
		StructureType* buffer = (StructureType*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(StructureType), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		*buffer = newStorage;
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	UniformBuffer(){
		glGenBuffers(1, &uniformBuffer);
		Bind();
		glBufferStorage(GL_UNIFORM_BUFFER, sizeof(StructureType), NULL, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);

		bindingPoint = freeBindingPoint;
		glBindBufferBase(GL_UNIFORM_BUFFER, freeBindingPoint, uniformBuffer);
		++freeBindingPoint;
	}
};

}
