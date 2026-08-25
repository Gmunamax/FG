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
#include "FGengine/structures/aspectratio.hpp"
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/color.hpp"

namespace FGengine{

class Framebuffer{
private:
	AspectRatio aspectRatio;

public:
	const AspectRatio& GetAspectRatio(){
		return aspectRatio;
	}

public:
	void SetViewportGeom(const Geometry2i& newgeom);

	Geometry2i GetViewportGeom() const;

public:
	void SetBackgroundColor(const Color4f& newbgcolor);

	Color4f GetBackgroundColor() const;

private:
	unsigned int buffersToClear = 0;

public:
	void SetBuffersToClear(unsigned int newMask){
		buffersToClear = newMask;
	}

	const unsigned int& GetBuffersToClear() const{
		return buffersToClear;
	}

public:
	void Clear();
};

}
