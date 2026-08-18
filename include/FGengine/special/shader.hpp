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
#include <span>
#include "FGengine/structures/shaderid.hpp"

namespace FGengine{

class Shader{
public:
	struct ProgramDescription{
		using Pathes = std::span<const char*>;
		Pathes geometry;
		Pathes vertex;
		Pathes fragment;
		Pathes tessControl;
		Pathes tessEvaluation;
		Pathes compute;
	};

	Shader(ProgramDescription descriptions){
		Load(descriptions);
		BindCommonUniformBuffers();
	}
	Shader(const Shader&) = delete;
	Shader(Shader&& shader): shaderid(shader.shaderid){
		shader.shaderid = 0;
	}
	~Shader(){
		Delete();
	}

	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&& shader){
		if(&shader != this){
			Delete();
			shaderid = shader.shaderid;
			shader.shaderid = 0;
		}
		return *this;
	}
	
	void Load(ProgramDescription descriptions);

	ShaderID GetID() const{
		return shaderid;
	}

private:
	ShaderID shaderid;

	void Delete();
	void BindCommonUniformBuffers();
	
};

}
