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
#include "FGengine/structures/uniform.hpp"
#include "gl/gl.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace FGengine;

void _Uniform::FindLocation(){
	location = glGetUniformLocation(shaderId, name);
}

void _Uniform::UseShader() const{
	glUseProgram(GetShader());
}

template<>
void Uniform<1, float>::SpecialSend() const{
	glUniform1f(location, value);
}
template<>
void Uniform<1, glm::vec<2, float>>::SpecialSend() const{
	glUniform2f(location, value.x, value.y);
}
template<>
void Uniform<1, glm::vec<3, float>>::SpecialSend() const{
	glUniform3f(location, value.x, value.y, value.z);
}
template<>
void Uniform<1, glm::vec<4, float>>::SpecialSend() const{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
template<>
void Uniform<1, double>::SpecialSend() const{
	glUniform1d(location, value);
}
template<>
void Uniform<1, glm::vec<2, double>>::SpecialSend() const{
	glUniform2d(location, value.x, value.y);
}
template<>
void Uniform<1, glm::vec<3, double>>::SpecialSend() const{
	glUniform3d(location, value.x, value.y, value.z);
}
template<>
void Uniform<1, glm::vec<4, double>>::SpecialSend() const{
	glUniform4d(location, value.x, value.y, value.z, value.w);
}
template<>
void Uniform<1, int>::SpecialSend() const{
	glUniform1i(location, value);
}
template<>
void Uniform<1, glm::vec<2, int>>::SpecialSend() const{
	glUniform2i(location, value.x, value.y);
}
template<>
void Uniform<1, glm::vec<3, int>>::SpecialSend() const{
	glUniform3i(location, value.x, value.y, value.z);
}
template<>
void Uniform<1, glm::vec<4, int>>::SpecialSend() const{
	glUniform4i(location, value.x, value.y, value.z, value.w);
}
template<>
void Uniform<1, unsigned int>::SpecialSend() const{
	glUniform1ui(location, value);
}
template<>
void Uniform<1, glm::vec<2, unsigned int>>::SpecialSend() const{
	glUniform2ui(location, value.x, value.y);
}
template<>
void Uniform<1, glm::vec<3, unsigned int>>::SpecialSend() const{
	glUniform3ui(location, value.x, value.y, value.z);
}
template<>
void Uniform<1, glm::vec<4, unsigned int>>::SpecialSend() const{
	glUniform4ui(location, value.x, value.y, value.z, value.w);
}
template<>
void Uniform<1, glm::mat<2, 2, float>>::SpecialSend() const{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<2, 3, float>>::SpecialSend() const{
	glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<2, 4, float>>::SpecialSend() const{
	glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 2, float>>::SpecialSend() const{
	glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 3, float>>::SpecialSend() const{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 4, float>>::SpecialSend() const{
	glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 2, float>>::SpecialSend() const{
	glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 3, float>>::SpecialSend() const{
	glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 4, float>>::SpecialSend() const{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<2, 2, double>>::SpecialSend() const{
	glUniformMatrix2dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<2, 3, double>>::SpecialSend() const{
	glUniformMatrix2x3dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<2, 4, double>>::SpecialSend() const{
	glUniformMatrix2x4dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 2, double>>::SpecialSend() const{
	glUniformMatrix3x2dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 3, double>>::SpecialSend() const{
	glUniformMatrix3dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<3, 4, double>>::SpecialSend() const{
	glUniformMatrix3x4dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 2, double>>::SpecialSend() const{
	glUniformMatrix4x2dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 3, double>>::SpecialSend() const{
	glUniformMatrix4x3dv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Uniform<1, glm::mat<4, 4, double>>::SpecialSend() const{
	glUniformMatrix4dv(location, 1, GL_FALSE, glm::value_ptr(value));
}

template<>
void _Uniform::Send(unsigned count, const int* value) const{
	glUniform1iv(location, count, value);
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<2, int>* value) const{
	glUniform2iv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<3, int>* value) const{
	glUniform3iv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<4, int>* value) const{
	glUniform4iv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const unsigned int* value) const{
	glUniform1uiv(location, count, value);
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<2, unsigned int>* value) const{
	glUniform2uiv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<3, unsigned int>* value) const{
	glUniform3uiv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<4, unsigned int>* value) const{
	glUniform4uiv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const float* value) const{
	glUniform1fv(location, count, value);
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<2, float>* value) const{
	glUniform2fv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<3, float>* value) const{
	glUniform3fv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::vec<4, float>* value) const{
	glUniform4fv(location, count, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 2, float>* value) const{
	glUniformMatrix2fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 3, float>* value) const{
	glUniformMatrix2x3fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 4, float>* value) const{
	glUniformMatrix2x4fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 2, float>* value) const{
	glUniformMatrix3x2fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 3, float>* value) const{
	glUniformMatrix3fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 4, float>* value) const{
	glUniformMatrix3x4fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 2, float>* value) const{
	glUniformMatrix4x2fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 3, float>* value) const{
	glUniformMatrix4x3fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 4, float>* value) const{
	glUniformMatrix4fv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 2, double>* value) const{
	glUniformMatrix2dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 3, double>* value) const{
	glUniformMatrix2x3dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<2, 4, double>* value) const{
	glUniformMatrix2x4dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 2, double>* value) const{
	glUniformMatrix3x2dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 3, double>* value) const{
	glUniformMatrix3dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<3, 4, double>* value) const{
	glUniformMatrix3x4dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 2, double>* value) const{
	glUniformMatrix4x2dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 3, double>* value) const{
	glUniformMatrix4x3dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
template<>
void _Uniform::Send(unsigned count, const glm::mat<4, 4, double>* value) const{
	glUniformMatrix4dv(location, count, GL_FALSE, glm::value_ptr(*value));
}
