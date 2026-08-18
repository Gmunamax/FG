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
#include "shaderCompilation.hpp"
#include <compiler.hpp>
#include <vector>
#include <string>
#include <span>

namespace FGengine{

namespace {

	class ShaderPart{
	public:
		ShaderPart(GLuint type, std::span<const char*> sources){
			part = glCreateShader(type);
			glShaderSource(part, sources.size(), sources.data(), NULL); glCompileShader(part);
		}
		ShaderPart(const ShaderPart&) = delete;
		ShaderPart(ShaderPart&& shaderPart){
			part = shaderPart.part;
			shaderPart.part = 0;
		}
		~ShaderPart(){
			Destroy();
		}

		ShaderPart& operator=(const ShaderPart&) = delete;
		ShaderPart& operator=(ShaderPart&& shaderPart){
			if(&shaderPart != this){
				Destroy();
				part = shaderPart.part;
				shaderPart.part = 0;
			}
			return *this;
		}

		void LinkToProgram(GLuint program) const{
			glAttachShader(program, part);
		}

	private:
		GLuint part;

		void Destroy(){
			if(part != 0)
				glDeleteShader(part);
		}
	};

	void AddPartIfSourcesProvided(GLuint type, Shader::ProgramDescription::Pathes pathes, std::vector<ShaderPart>& destination);
	std::vector<std::string> ReadPartSources(std::span<const char* const> pathes);
	std::vector<const char*> ConvertToCstr(std::span<std::string> sources);
	GLuint LinkShader(std::span<ShaderPart> parts);
}

GLuint CreateShaderProgram(Shader::ProgramDescription description){
	std::vector<ShaderPart> parts;

	AddPartIfSourcesProvided(GL_VERTEX_SHADER, description.vertex, parts);
	AddPartIfSourcesProvided(GL_FRAGMENT_SHADER, description.fragment, parts);
	AddPartIfSourcesProvided(GL_GEOMETRY_SHADER, description.geometry, parts);
	AddPartIfSourcesProvided(GL_TESS_CONTROL_SHADER, description.tessControl, parts);
	AddPartIfSourcesProvided(GL_TESS_EVALUATION_SHADER, description.tessEvaluation, parts);
	AddPartIfSourcesProvided(GL_COMPUTE_SHADER, description.compute, parts);

	return LinkShader(parts);
}

namespace {

	void AddPartIfSourcesProvided(GLuint type, Shader::ProgramDescription::Pathes pathes, std::vector<ShaderPart>& destination){
		if(pathes.size() != 0){
			std::vector<std::string> sources = ReadPartSources(pathes);
			std::vector<const char*> csources = ConvertToCstr(sources);
			destination.emplace_back(type, csources);
		}
	}

	std::vector<std::string> ReadPartSources(std::span<const char* const> pathes){
		std::vector<std::string> sources = {};
		sources.reserve(pathes.size());
		for(const auto& path : pathes){
			sources.push_back(ReadFile(path));
		}
		return sources;
	}

	std::vector<const char*> ConvertToCstr(std::span<std::string> sources){
		std::vector<const char*> csources;
		std::vector<GLint> lenghts;

		for(const auto& filePath : sources){
			csources.push_back(sources.back().c_str());
		}

		return csources;
	}

	GLuint LinkShader(std::span<ShaderPart> parts){
		GLuint shaderid = glCreateProgram();
		for(const auto& part : parts){
			part.LinkToProgram(shaderid);
		}
		glLinkProgram(shaderid);
		return shaderid;
	}

}

}
