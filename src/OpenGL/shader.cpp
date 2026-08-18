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
#include "FGengine/special/shader.hpp"
#include <gl/gl.hpp>
#include "FGengine/special/uniformBuffer.hpp"
#include "../currentContext/currentContext.hpp"
#include "shaderCompilation/shaderCompilation.hpp"
#include <iostream>

using namespace FGengine;

namespace {
	void PrintLinkStatus(GLuint shaderid);
}

void Shader::Load(ProgramDescription descriptions){
	if(shaderid != 0)
		Delete();
	shaderid = CreateShaderProgram(descriptions);
	PrintLinkStatus(shaderid);
}

namespace {

	void PrintLinkStatus(GLuint shaderid){
		constexpr short logsize = 512;
		int status;
		char log[logsize];
		glGetProgramiv(shaderid, GL_LINK_STATUS, &status);
		if(status != GL_TRUE){
			glGetProgramInfoLog(shaderid, logsize, NULL, log);
			std::cout << "Shader link failed" << "\n" << log << std::endl;
		}
	}

}

void Shader::Delete(){
	if(shaderid != 0){
		glDeleteProgram(shaderid);
		shaderid = 0;
	}
}

void BindUniformBlock(const Shader& shader, const _UniformBuffer& uniformBuffer, const char* blockName){
	GLuint index = glGetUniformBlockIndex(shader.GetID(), blockName);
	glUniformBlockBinding(shader.GetID(), index, uniformBuffer.GetBindingPoint());
}

void Shader::BindCommonUniformBuffers(){
	BindUniformBlock(*this, GetCurrentContext().GetCameraUniformBuffer(), "camera");
}
