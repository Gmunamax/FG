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
#include <glm/glm.hpp>

namespace FGengine{

enum class VectorType{
	Point,
	Color,
	Size,
	Indice,
};

namespace _Vector{

	using length_t = unsigned;

	template<length_t Length, typename DataType, VectorType VectorPurpose>
	struct VectorData;

	template<typename DataType>
	struct VectorData<1, DataType, VectorType::Indice>{
		DataType value;
	};

	template<typename DataType>
	struct VectorData<1, DataType, VectorType::Point>{
		union{
			DataType value;
			DataType x;
		};
	};

	template<typename DataType>
	struct VectorData<2, DataType, VectorType::Point>{
		union{
			DataType value[2];
			struct{ DataType x, y; };
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Point>{
		union{
			DataType value[3];
			struct{ DataType x, y, z; };
		};
	};

	template<typename DataType>
	struct VectorData<4, DataType, VectorType::Point>{
		union{
			DataType value[4];
			struct{ DataType x, y, z, w; };
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Color>{
		union{
			DataType value[3];
			struct{ DataType r, g, b; };
		};
	};

	template<typename DataType>
	struct VectorData<4, DataType, VectorType::Color>{
		union{
			DataType value[4];
			struct{ DataType r, g, b, a; };
		};
	};

	template<typename DataType>
	struct VectorData<1, DataType, VectorType::Size>{
		union{
			DataType value;
			DataType w;
		};
	};

	template<typename DataType>
	struct VectorData<2, DataType, VectorType::Size>{
		union{
			DataType value[2];
			struct{ DataType w, h; };
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Size>{
		union{
			DataType value[3];
			struct{ DataType w, h, d; };
		};
	};

	template<length_t Length, typename DataType, VectorType VectorPurpose>
	struct VectorMethods: VectorData<Length, DataType, VectorPurpose>{
		using valueType = DataType;
		const valueType& operator[](unsigned index) const{
			return VectorMethods::value[index];
		}
		valueType& operator[](const unsigned index){
			return VectorMethods::value[index];
		}
		static inline constexpr length_t length() {return Length;}
	};

}

template<_Vector::length_t Length, typename DataType, VectorType VectorPurpose>
struct Vector;

template<typename DataType, VectorType VectorPurpose>
struct Vector<1, DataType, VectorPurpose>: public _Vector::VectorMethods<1, DataType, VectorPurpose>{

	Vector() = default;
	Vector(DataType value) {
		Vector::value = value;
	}
		
	glm::vec<1, DataType> toGlm() {return {this->value};}

	Vector& operator=(const Vector& value){
		Vector::value = value.value;
		return *this;
	}

	bool operator==(const Vector& value) const{
		return Vector::value == value.value;
	}
	bool operator!=(const Vector& value) const{
		return Vector::value == value.value;
	}
	bool operator!() const{
		return !Vector::value;
	}
	bool operator&&(const Vector& value) const{
		return Vector::value && value.value;
	}
	bool operator||(const Vector& value) const{
		return Vector::value || value.value;
	}
	bool operator>(const Vector& value) const{
		return Vector::value > value.value;
	}
	bool operator<(const Vector& value) const{
		return Vector::value < value.value;
	}
	bool operator>=(const Vector& value) const{
		return Vector::value >= value.value;
	}
	bool operator<=(const Vector& value) const{
		return Vector::value <= value.value;
	}

	Vector operator+(const Vector& value) const{
		return Vector::value + value.value;
	}
	Vector operator-(const Vector& value) const{
		return Vector::value - value.value;
	}
	Vector operator*(const Vector& value) const{
		return Vector::value * value.value;
	}
	Vector operator/(const Vector& value) const{
		return Vector::value / value.value;
	}
	Vector operator%(const Vector& value) const{
		return Vector::value % value.value;
	}
	Vector operator&(const Vector& value) const{
		return Vector::value & value.value;
	}
	Vector operator|(const Vector& value) const{
		return Vector::value | value.value;
	}
	Vector operator^(const Vector& value) const{
		return Vector::value ^ value.value;
	}
	Vector operator>>(const Vector& value) const{
		return Vector::value >> value.value;
	}
	Vector operator<<(const Vector& value) const{
		return Vector::value << value.value;
	}
	Vector operator~() const{
		return ~Vector::value;
	}

	Vector& operator+=(const Vector& value){
		Vector::value += value.value;
		return *this;
	}
	Vector& operator-=(const Vector& value){
		Vector::value -= value.value;
		return *this;
	}
	Vector& operator*=(const Vector& value){
		Vector::value *= value.value;
		return *this;
	}
	Vector& operator/=(const Vector& value){
		Vector::value /= value.value;
		return *this;
	}
	Vector& operator%=(const Vector& value){
		Vector::value %= value.value;
		return *this;
	}
	Vector& operator&=(const Vector& value){
		Vector::value &= value.value;
		return *this;
	}
	Vector& operator|=(const Vector& value){
		Vector::value |= value.value;
		return *this;
	}
	Vector& operator^=(const Vector& value){
		Vector::value ^= value.value;
		return *this;
	}
	Vector& operator>>=(const Vector& value){
		Vector::value >>= value.value;
		return *this;
	}
	Vector& operator<<=(const Vector& value){
		Vector::value <<= value.value;
		return *this;
	}

	Vector& operator++(){
		++Vector::value;
		return *this;
	}
	Vector operator++(int){
		Vector t{*this};
		++*this;
		return t;
	}
	Vector& operator--(){
		--Vector::value;
		return *this;
	}
	Vector operator--(int){
		Vector t{*this};
		--*this;
		return t;
	}
};

template<typename DataType, VectorType VectorPurpose>
struct Vector<2, DataType, VectorPurpose>: public _Vector::VectorMethods<2, DataType, VectorPurpose>{

	Vector() = default;
	explicit Vector(DataType value){
		Vector::value[0] = value;
		Vector::value[1] = value;
	}
	Vector(DataType v1, DataType v2){
		Vector::value[0] = v1;
		Vector::value[1] = v2;
	}

	glm::vec<2, DataType> toGlm() {return {this->value[0], this->value[1]};}

	Vector& operator=(const Vector& value){
		Vector::value[0] = value.value[0];
		Vector::value[1] = value.value[1];
		return *this;
	}

	bool operator==(const Vector& value) const{
		return 
			Vector::value[0] == value.value[0] and 
			Vector::value[1] == value.value[1];
	}
	bool operator!=(const Vector& value) const{
		return 
			Vector::value[0] != value.value[0] or
			Vector::value[1] != value.value[1];
	}
	bool operator!() const{
		return
			!Vector::value[0] and
			!Vector::value[1];
	}
	bool operator&&(const Vector& value) const{
		return
			(Vector::value[0] && value.value[0]) and
			(Vector::value[1] && value.value[1]);
	}
	bool operator||(const Vector& value) const{
		return
			(Vector::value[0] || value.value[0]) or
			(Vector::value[1] || value.value[1]);
	}

	Vector operator+(const Vector& value) const{
		return {Vector::value[0] + value.value[0], 
				Vector::value[1] + value.value[1]};
	}
	Vector operator-(const Vector& value) const{
		return {Vector::value[0] + value.value[0],
		        Vector::value[1] + value.value[1]};
	}
	Vector operator*(const Vector& value) const{
		return {Vector::value[0] * value.value[0],
		        Vector::value[1] * value.value[1]};
	}
	Vector operator/(const Vector& value) const{
		return {Vector::value[0] / value.value[0],
		        Vector::value[1] / value.value[1]};
	}
	Vector operator%(const Vector& value) const{
		return {Vector::value[0] % value.value[0],
		        Vector::value[1] % value.value[1]};
	}
	Vector operator&(const Vector& value) const{
		return {Vector::value[0] & value.value[0],
		        Vector::value[1] & value.value[1]};
	}
	Vector operator|(const Vector& value) const{
		return {Vector::value[0] | value.value[0],
		        Vector::value[1] | value.value[1]};
	}
	Vector operator^(const Vector& value) const{
		return {Vector::value[0] ^ value.value[0],
		        Vector::value[1] ^ value.value[1]};
	}
	Vector operator>>(const Vector& value) const{
		return {Vector::value[0] >> value.value[0],
		        Vector::value[1] >> value.value[1]};
	}
	Vector operator<<(const Vector& value) const{
		return {Vector::value[0] << value.value[0],
		        Vector::value[1] << value.value[1]};
	}
	Vector operator~() const{
		return{~Vector::value[0],
		       ~Vector::value[1]};
	}

	Vector& operator+=(const Vector& value){
		Vector::value[0] += value.value[0];
		Vector::value[1] += value.value[1];
		return *this;
	}
	Vector& operator-=(const Vector& value){
		Vector::value[0] -= value.value[0];
		Vector::value[1] -= value.value[1];
		return *this;
	}
	Vector& operator*=(const Vector& value){
		Vector::value[0] *= value.value[0];
		Vector::value[1] *= value.value[1];
		return *this;
	}
	Vector& operator/=(const Vector& value){
		Vector::value[0] *= value.value[0];
		Vector::value[1] *= value.value[1];
		return *this;
	}
	Vector& operator%=(const Vector& value){
		Vector::value[0] %= value.value[0];
		Vector::value[1] %= value.value[1];
		return *this;
	}
	Vector& operator&=(const Vector& value){
		Vector::value[0] &= value.value[0];
		Vector::value[1] &= value.value[1];
		return *this;
	}
	Vector& operator|=(const Vector& value){
		Vector::value[0] |= value.value[0];
		Vector::value[1] |= value.value[1];
		return *this;
	}
	Vector& operator^=(const Vector& value){
		Vector::value[0] ^= value.value[0];
		Vector::value[1] ^= value.value[1];
		return *this;
	}
	Vector& operator>>=(const Vector& value){
		Vector::value[0] >>= value.value[0];
		Vector::value[1] >>= value.value[1];
		return *this;
	}
	Vector& operator<<=(const Vector& value){
		Vector::value[0] <<= value.value[0];
		Vector::value[1] <<= value.value[1];
		return *this;
	}

	Vector& operator++(){
		++Vector::value[0];
		++Vector::value[1];
		return *this;
	}
	Vector operator++(int){
		Vector t{*this};
		++*this;
		return t;
	}
	Vector& operator--(){
		--Vector::value[0];
		--Vector::value[1];
		return *this;
	}
	Vector operator--(int){
		Vector t{*this};
		--*this;
		return t;
	}
};

template<typename DataType, VectorType VectorPurpose>
struct Vector<3, DataType, VectorPurpose>: public _Vector::VectorMethods<3, DataType, VectorPurpose>{

	Vector() = default;
	explicit Vector(DataType value){
		Vector::value[0] = value;
		Vector::value[1] = value;
		Vector::value[2] = value;
	}
	Vector(DataType v1, DataType v2, DataType v3){
		Vector::value[0] = v1;
		Vector::value[1] = v2;
		Vector::value[2] = v3;
	}

	glm::vec<3, DataType> toGlm() {return {this->value[0], this->value[1], this->value[2]};}

	Vector& operator=(const Vector& value){
		Vector::value[0] = value.value[0];
		Vector::value[1] = value.value[1];
		Vector::value[2] = value.value[2];
		return *this;
	}

	bool operator==(const Vector& value) const{
		return
			Vector::value[0] == value.value[0] and
			Vector::value[1] == value.value[1] and
			Vector::value[2] == value.value[2];
	}
	bool operator!=(const Vector& value) const{
		return
			Vector::value[0] != value.value[0] or
			Vector::value[1] != value.value[1] or
			Vector::value[2] != value.value[2];
	}
	bool operator!() const{
		return
			!Vector::value[0] and
			!Vector::value[1] and
			!Vector::value[2];
	}
	bool operator&&(const Vector& value) const{
		return
			(Vector::value[0] && value.value[0]) and
			(Vector::value[1] && value.value[1]) and
			(Vector::value[2] && value.value[2]);
	}
	bool operator||(const Vector& value) const{
		return
			(Vector::value[0] || value.value[0]) or
			(Vector::value[1] || value.value[1]) or
			(Vector::value[2] || value.value[2]);
	}
		
	Vector operator+(const Vector& value) const{
		return {Vector::value[0] + value.value[0], 
				Vector::value[1] + value.value[1], 
				Vector::value[2] + value.value[2]};
	}
	Vector operator-(const Vector& value) const{
		return {Vector::value[0] - value.value[0],
		        Vector::value[1] - value.value[1],
				Vector::value[2] - value.value[2]};
	}
	Vector operator*(const Vector& value) const{
		return {Vector::value[0] * value.value[0], 
				Vector::value[1] * value.value[1], 
				Vector::value[2] * value.value[2]};
	}
	Vector operator/(const Vector& value) const{
		return {Vector::value[0] / value.value[0],
		        Vector::value[1] / value.value[1],
				Vector::value[2] / value.value[2]};
	}
	Vector operator%(const Vector& value) const{
		return {Vector::value[0] % value.value[0],
		        Vector::value[1] % value.value[1],
				Vector::value[2] % value.value[2]};
	}
	Vector operator&(const Vector& value) const{
		return {Vector::value[0] & value.value[0],
		        Vector::value[1] & value.value[1],
				Vector::value[2] & value.value[2]};
	}
	Vector operator|(const Vector& value) const{
		return {Vector::value[0] | value.value[0],
		        Vector::value[1] | value.value[1],
				Vector::value[2] | value.value[2]};
	}
	Vector operator^(const Vector& value) const{
		return {Vector::value[0] ^ value.value[0],
		        Vector::value[1] ^ value.value[1],
				Vector::value[2] ^ value.value[2]};
	}
	Vector operator>>(const Vector& value) const{
		return {Vector::value[0] >> value.value[0],
		        Vector::value[1] >> value.value[1],
				Vector::value[2] >> value.value[2]};
	}
	Vector operator<<(const Vector& value) const{
		return {Vector::value[0] << value.value[0],
		        Vector::value[1] << value.value[1],
				Vector::value[2] << value.value[2]};
	}
	Vector operator~() const{
		return {~Vector::value[0],
		        ~Vector::value[1],
				~Vector::value[2]};
	}

	Vector& operator+=(const Vector& value){
		Vector::value[0] += value.value[0];
		Vector::value[1] += value.value[1];
		Vector::value[2] += value.value[2];
		return *this;
	}
	Vector& operator-=(const Vector& value){
		Vector::value[0] -= value.value[0];
		Vector::value[1] -= value.value[1];
		Vector::value[2] -= value.value[2];
		return *this;
	}
	Vector& operator*=(const Vector& value){
		Vector::value[0] *= value.value[0];
		Vector::value[1] *= value.value[1];
		Vector::value[2] *= value.value[2];
		return *this;
	}
	Vector& operator/=(const Vector& value){
		Vector::value[0] /= value.value[0];
		Vector::value[1] /= value.value[1];
		Vector::value[2] /= value.value[2];
		return *this;
	}
	Vector& operator%=(const Vector& value){
		Vector::value[0] %= value.value[0];
		Vector::value[1] %= value.value[1];
		Vector::value[2] %= value.value[2];
		return *this;
	}
	Vector& operator&=(const Vector& value){
		Vector::value[0] &= value.value[0];
		Vector::value[1] &= value.value[1];
		Vector::value[2] &= value.value[2];
		return *this;
	}
	Vector& operator|=(const Vector& value){
		Vector::value[0] |= value.value[0];
		Vector::value[1] |= value.value[1];
		Vector::value[2] |= value.value[2];
		return *this;
	}
	Vector& operator^=(const Vector& value){
		Vector::value[0] ^= value.value[0];
		Vector::value[1] ^= value.value[1];
		Vector::value[2] ^= value.value[2];
		return *this;
	}
	Vector& operator>>=(const Vector& value){
		Vector::value[0] >>= value.value[0];
		Vector::value[1] >>= value.value[1];
		Vector::value[2] >>= value.value[2];
		return *this;
	}
	Vector& operator<<=(const Vector& value){
		Vector::value[0] <<= value.value[0];
		Vector::value[1] <<= value.value[1];
		Vector::value[2] <<= value.value[2];
		return *this;
	}

	Vector& operator++(){
		++Vector::value[0];
		++Vector::value[1];
		++Vector::value[2];
		return *this;
	}
	Vector operator++(int){
		Vector t{*this};
		++*this;
		return t;
	}
	Vector& operator--(){
		--Vector::value[0];
		--Vector::value[1];
		--Vector::value[2];
		return *this;
	}
	Vector operator--(int){
		Vector t{*this};
		--*this;
		return t;
	}
};

template<typename DataType, VectorType VectorPurpose>
struct Vector<4, DataType, VectorPurpose>: public _Vector::VectorMethods<4, DataType, VectorPurpose>{
		
	Vector() = default;
	explicit Vector(DataType value){
		Vector::value[0] = value;
		Vector::value[1] = value;
		Vector::value[2] = value;
		Vector::value[3] = value;
	}
	Vector(DataType v1, DataType v2, DataType v3, DataType v4){
		Vector::value[0] = v1;
		Vector::value[1] = v2;
		Vector::value[2] = v3;
		Vector::value[3] = v4;
	}

	glm::vec<4, DataType> toGlm() {return {this->value[0], this->value[1], this->value[2], this->value[3]};}

	Vector& operator=(const Vector& value){
		Vector::value[0] = value.value[0];
		Vector::value[1] = value.value[1];
		Vector::value[2] = value.value[2];
		Vector::value[3] = value.value[3];
		return *this;
	}

	bool operator==(const Vector& value) const{
		return
			Vector::value[0] == value.value[0] and
			Vector::value[1] == value.value[1] and
			Vector::value[2] == value.value[2] and
			Vector::value[3] == value.value[3];
	}
	bool operator!=(const Vector& value) const{
		return
			Vector::value[0] != value.value[0] or
			Vector::value[1] != value.value[1] or
			Vector::value[2] != value.value[2] or
			Vector::value[3] != value.value[3];
	}
	bool operator!() const{
		return
			!Vector::value[0] and
			!Vector::value[1] and
			!Vector::value[2] and
			!Vector::value[3];
	}
	bool operator&&(const Vector& value) const{
		return
			(Vector::value[0] && value.value[0]) and
			(Vector::value[1] && value.value[1]) and
			(Vector::value[2] && value.value[2]) and
			(Vector::value[3] && value.value[3]);
	}
	bool operator||(const Vector& value) const{
		return
			(Vector::value[0] || value.value[0]) or
			(Vector::value[1] || value.value[1]) or
			(Vector::value[2] || value.value[2]) or
			(Vector::value[3] || value.value[3]);
	}

	Vector operator+(const Vector& value) const{
		return {Vector::value[0] + value.value[0], 
				Vector::value[1] + value.value[1], 
				Vector::value[2] + value.value[2], 
				Vector::value[3] + value.value[3]};
	}
	Vector operator-(const Vector& value) const{
		return {Vector::value[0] - value.value[0],
		        Vector::value[1] - value.value[1],
				Vector::value[2] - value.value[2],
				Vector::value[3] - value.value[3]};
	}
	Vector operator*(const Vector& value) const{
		return {Vector::value[0] * value.value[0],
		        Vector::value[1] * value.value[1],
				Vector::value[2] * value.value[2],
				Vector::value[3] * value.value[3]};
	}
	Vector operator/(const Vector& value) const{
		return {Vector::value[0] / value.value[0],
		        Vector::value[1] / value.value[1],
				Vector::value[2] / value.value[2],
				Vector::value[3] / value.value[3]};
	}
	Vector operator%(const Vector& value) const{
		return {Vector::value[0] % value.value[0],
		        Vector::value[1] % value.value[1],
				Vector::value[2] % value.value[2],
				Vector::value[3] % value.value[3]};
	}
	Vector operator&(const Vector& value) const{
		return {Vector::value[0] & value.value[0],
		        Vector::value[1] & value.value[1],
				Vector::value[2] & value.value[2],
				Vector::value[3] & value.value[3]};
	}
	Vector operator|(const Vector& value) const{
		return {Vector::value[0] | value.value[0],
		        Vector::value[1] | value.value[1],
				Vector::value[2] | value.value[2],
				Vector::value[3] | value.value[3]};
	}
	Vector operator^(const Vector& value) const{
		return {Vector::value[0] ^ value.value[0],
		        Vector::value[1] ^ value.value[1],
				Vector::value[2] ^ value.value[2],
				Vector::value[3] ^ value.value[3]};
	}
	Vector operator>>(const Vector& value) const{
		return {Vector::value[0] >> value.value[0],
		        Vector::value[1] >> value.value[1],
				Vector::value[2] >> value.value[2],
				Vector::value[3] >> value.value[3]};
	}
	Vector operator<<(const Vector& value) const{
		return {Vector::value[0] << value.value[0],
		        Vector::value[1] << value.value[1],
				Vector::value[2] << value.value[2],
				Vector::value[3] << value.value[3]};
	}
	Vector operator~() const{
		return {~Vector::value[0],
		        ~Vector::value[1],
				~Vector::value[2],
				~Vector::value[3]};
	}

	Vector& operator+=(const Vector& value){
		Vector::value[0] += value.value[0];
		Vector::value[1] += value.value[1];
		Vector::value[2] += value.value[2];
		Vector::value[3] += value.value[3];
		return *this;
	}
	Vector& operator-=(const Vector& value){
		Vector::value[0] -= value.value[0];
		Vector::value[1] -= value.value[1];
		Vector::value[2] -= value.value[2];
		Vector::value[3] -= value.value[3];
		return *this;
	}
	Vector& operator*=(const Vector& value){
		Vector::value[0] *= value.value[0];
		Vector::value[1] *= value.value[1];
		Vector::value[2] *= value.value[2];
		Vector::value[3] *= value.value[3];
		return *this;
	}
	Vector& operator/=(const Vector& value){
		Vector::value[0] /= value.value[0];
		Vector::value[1] /= value.value[1];
		Vector::value[2] /= value.value[2];
		Vector::value[3] /= value.value[3];
		return *this;
	}
	Vector& operator%=(const Vector& value){
		Vector::value[0] %= value.value[0];
		Vector::value[1] %= value.value[1];
		Vector::value[2] %= value.value[2];
		Vector::value[3] %= value.value[3];
		return *this;
	}
	Vector& operator&=(const Vector& value){
		Vector::value[0] &= value.value[0];
		Vector::value[1] &= value.value[1];
		Vector::value[2] &= value.value[2];
		Vector::value[3] &= value.value[3];
		return *this;
	}
	Vector& operator|=(const Vector& value){
		Vector::value[0] |= value.value[0];
		Vector::value[1] |= value.value[1];
		Vector::value[2] |= value.value[2];
		Vector::value[3] |= value.value[3];
		return *this;
	}
	Vector& operator^=(const Vector& value){
		Vector::value[0] ^= value.value[0];
		Vector::value[1] ^= value.value[1];
		Vector::value[2] ^= value.value[2];
		Vector::value[3] ^= value.value[3];
		return *this;
	}
	Vector& operator>>=(const Vector& value){
		Vector::value[0] >>= value.value[0];
		Vector::value[1] >>= value.value[1];
		Vector::value[2] >>= value.value[2];
		Vector::value[3] >>= value.value[3];
		return *this;
	}
	Vector& operator<<=(const Vector& value){
		Vector::value[0] <<= value.value[0];
		Vector::value[1] <<= value.value[1];
		Vector::value[2] <<= value.value[2];
		Vector::value[3] <<= value.value[3];
		return *this;
	}

	Vector& operator++(){
		++Vector::value[0];
		++Vector::value[1];
		++Vector::value[2];
		++Vector::value[3];
		return *this;
	}
	Vector operator++(int){
		Vector t{*this};
		++*this;
		return t;
	}
	Vector& operator--(){
		--Vector::value[0];
		--Vector::value[1];
		--Vector::value[2];
		--Vector::value[3];
		return *this;
	}
	Vector operator--(int){
		Vector t{*this};
		--*this;
		return t;
	}
};

}
