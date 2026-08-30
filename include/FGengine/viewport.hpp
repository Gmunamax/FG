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
#include "FGengine/structures/geometry.hpp"
#include "FGengine/properties/framebuffer.hpp"
#include "FGengine/properties/buffer.hpp"

namespace FGengine{

class Viewport: protected Buffer, public Framebuffer{

	struct Buffer{
		unsigned int id;
		unsigned int internalformat;
	};
	
	Buffer colorBuffer {0};
	Buffer depthStencilBuffer {0};

//viewport

private:
	Vector<2, unsigned int, VectorType::Size> maxSize;

	void ResizeBuffers(Vector<2, unsigned int, VectorType::Size> newMaxSize){
		maxSize = newMaxSize;
		DefineTextureBuffer();
		DefineDepthStencilBuffer();
	}

	const Vector<2, unsigned int, VectorType::Size>& GetMaxSize() const{
		return maxSize;
	}

//viewport

//tests

public:
	enum Buffers{
		NoBuffer,
		DepthBuffer,
		StencilBuffer
	};

//tests

private:
	int mip = 0;

	void DefineTextureBuffer();

	void DefineDepthStencilBuffer();

public:
	void Use();

	Viewport(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize): Viewport(buffers, maxSize, {0, 0, (int)maxSize.w, (int)maxSize.h}) {}
	Viewport(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize, Geometry2i geom){
		Init(buffers, maxSize);
		Use();
		SetViewportGeom(geom);
	}

private:
	void Init(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize);

public:
	~Viewport();
};

}
