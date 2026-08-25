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
#include "FGengine/properties/framebuffer.hpp"
#include <gl/gl.hpp>

using namespace FGengine;

void Framebuffer::SetViewportGeom(const Geometry2i &newgeom){
	glViewport(newgeom.x, newgeom.y, newgeom.w, newgeom.h);
	aspectRatio = AspectRatio{(float)newgeom.w, (float)newgeom.h}; 
}

Geometry2i Framebuffer::GetViewportGeom() const{
	int rawgeom[4];
	glGetIntegerv(GL_VIEWPORT, rawgeom);
	return {rawgeom[0], rawgeom[1], rawgeom[2], rawgeom[3]};
}

void Framebuffer::SetBackgroundColor(const Color4f &newbgcolor){
	glClearColor(newbgcolor.r, newbgcolor.g, newbgcolor.b, newbgcolor.a);
}

Color4f Framebuffer::GetBackgroundColor() const{
	Color4f color;
	glGetFloatv(GL_COLOR_CLEAR_VALUE, color.value);
	return color;
}

void Framebuffer::Clear(){
	glClear(buffersToClear);
}
