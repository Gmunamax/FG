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
#include "FGengine/special/viewport.hpp"
#include <gl/gl.hpp>

using namespace FGengine;

void Viewport::DefineTextureBuffer(){
	glBindTexture(GL_TEXTURE_2D, colorBuffer.id);
	glTexImage2D(GL_TEXTURE_2D, mip, colorBuffer.internalformat, maxSize.w, maxSize.h, 0, colorBuffer.internalformat, GL_UNSIGNED_BYTE, NULL);
}

void Viewport::DefineDepthStencilBuffer(){
	glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer.id);
	glRenderbufferStorage(GL_RENDERBUFFER, depthStencilBuffer.internalformat, maxSize.w, maxSize.h);
}

void Viewport::Use(){
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void Viewport::Init(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize){
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &colorBuffer.id);
	glGenRenderbuffers(1, &depthStencilBuffer.id);
	
	unsigned int buffersToClear = 0;
	unsigned int attachment = 0;
	if(buffers & DepthBuffer){
		if(buffers & StencilBuffer){
			attachment = GL_DEPTH_STENCIL_ATTACHMENT;
			depthStencilBuffer.internalformat = GL_DEPTH_STENCIL;
			buffersToClear |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
		}
		else{
			attachment = GL_DEPTH_ATTACHMENT;
			depthStencilBuffer.internalformat = GL_DEPTH_COMPONENT;
			buffersToClear |= GL_DEPTH_BUFFER_BIT;
		}
	}
	else{
		if(buffers & StencilBuffer){
			attachment = GL_STENCIL_ATTACHMENT;
			depthStencilBuffer.internalformat = GL_STENCIL_INDEX;
			buffersToClear |= GL_STENCIL_BUFFER_BIT;
		}
	}
	colorBuffer.internalformat = GL_RGBA;
	buffersToClear |= GL_COLOR_BUFFER_BIT;

	ResizeBuffers(maxSize);
	SetBuffersToClear(buffersToClear);

	if(attachment != 0)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, depthStencilBuffer.id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer.id, mip);
}

Viewport::~Viewport(){
	glDeleteRenderbuffers(1, &depthStencilBuffer.id);
	glDeleteTextures(1, &colorBuffer.id);
	glDeleteFramebuffers(1, &framebuffer);
}
