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
#include <glm/matrix.hpp>
#include "FGengine/structures/shaderid.hpp"

namespace FGengine{

class _Uniform{
	const char* name;
	ShaderID shaderId;

	void FindLocation();

protected:
	int location = 0;

	template<typename ValueType>
	void Send(unsigned count, const ValueType* value) const;

	void UseShader() const;

public:
	const char* GetName() const{
		return name;
	}

	void SetShader(const ShaderID& newshader){
		this->shaderId = newshader;
		FindLocation();
	}

	const ShaderID& GetShader() const{
		return shaderId;
	}

	_Uniform(const char* name): name(name) {}
	_Uniform(const char* name, const ShaderID& shader): name(name), shaderId(shader) {
		FindLocation();
	}
};

template<unsigned Count, typename ValueType>
class Uniform: public _Uniform{

	ValueType value[Count];

	void SetValue(const ValueType newvalue[Count]){
		for(unsigned e = 0; e < Count; ++e){
			value[e] = newvalue[e];
		}
	}

public:
	const ValueType* GetValue() const{
		return value;
	}

	void Send() const{
		UseShader();
		Uniform::_Uniform::Send(Count, value);
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ValueType value[Count]): _Uniform(name) {
		SetValue(value);
	}
	Uniform(const char* const name, const ShaderID& shader): _Uniform(name, shader) {}
	Uniform(const char* const name, const ShaderID& shader, const ValueType value[Count]): _Uniform(name, shader){
		SetValue(value);
	}

	void operator=(const ValueType newvalue[Count]){
		SetValue(newvalue);
	}
	const ValueType& operator[](const unsigned index) const{
		return Uniform::value[index];
	}
};

template<typename ValueType>
class Uniform<1, ValueType>: public _Uniform{

	ValueType value;

	void SpecialSend() const;

public:
	const ValueType& GetValue() const{
		return value;
	}
	void Send() const{
		UseShader();
		SpecialSend();
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ValueType& value): _Uniform(name), value(value) {}
	Uniform(const char* const name, const ShaderID& shader): _Uniform(name, shader) {}
	Uniform(const char* const name, const ShaderID& shader, const ValueType& value): _Uniform(name, shader), value(value) {}

	void operator=(const ValueType& newvalue){
		Uniform::value = newvalue;
	}
};

template<unsigned Count, typename ValueType>
class Uniform<Count, ValueType*>: public _Uniform{
public:
	void Send(const ValueType* value) const{
		UseShader();
		Uniform::_Uniform::Send(Count, value);
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ShaderID& shader): _Uniform(name, shader) {}
};

template<typename ValueType>
class Uniform<1, ValueType*>: public _Uniform{
public:
	void Send(const ValueType* value) const{
		UseShader();
		Uniform::_Uniform::Send(1, value);
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ShaderID& shader): _Uniform(name, shader) {}
};

using Umat4d = Uniform<1, glm::dmat4>;
using Umat4f = Uniform<1, glm::mat4>;
using Umat3d = Uniform<1, glm::dmat3>;
using Umat3f = Uniform<1, glm::mat3>;
using Uvec4d = Uniform<1, glm::dvec4>;
using Uvec4f = Uniform<1, glm::vec4>;
using Uvec3d = Uniform<1, glm::dvec3>;
using Uvec3f = Uniform<1, glm::vec3>;

}
