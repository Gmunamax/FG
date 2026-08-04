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
#include <cstddef>

namespace FGengine {

class _UniformBuffer{
	static inline unsigned int freeBindingPoint = 0;
	unsigned int bindingPoint;
	
	unsigned int uniformBuffer;

	void Bind() const;

public:
	unsigned int GetBindingPoint() const{
		return bindingPoint;
	}

	void Update(void* newStorage, std::size_t size);

	_UniformBuffer(std::size_t size);
};

template<typename StructureType>
class UniformBuffer: public _UniformBuffer{
public:
	UniformBuffer(): _UniformBuffer(sizeof(StructureType)) {}

	void Update(const StructureType& newStorage){
		Update(&newStorage, sizeof(StructureType));
	}
};

}
