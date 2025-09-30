#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
// using Point2i = SDL_Point;

template<typename Type>
struct PointType{};

template<>
struct PointType<float>{
	static constexpr int _gldatatype = GL_FLOAT;
};

template<>
struct PointType<double>{
	static constexpr int _gldatatype = GL_DOUBLE;
};

template<>
struct PointType<int>{
	static constexpr int _gldatatype = GL_INT;
};

template<>
struct PointType<short>{
	static constexpr int _gldatatype = GL_SHORT;
};

template<glm::length_t Count, typename Size>
struct Point: public PointType<Size>, public glm::vec<Count,Size,glm::packed_highp> {
	using glm::vec<Count,Size,glm::packed_highp>::vec;

	static constexpr short _elemcount = Count;
	
	Point(glm::vec<Count,Size,glm::packed_highp> v): glm::vec<Count,Size,glm::packed_highp>(v){
		std::cout << "UNSUPPORTED POINT TYPE" << std::endl;
	}
	Point(Size v): glm::vec<Count,Size,glm::packed_highp>(v){
		std::cout << "UNSUPPORTED POINT TYPE" << std::endl;
	}
};

template<typename Size>
struct Point<2,Size>: public PointType<Size>, public glm::vec<2,Size,glm::packed_highp>{
	using glm::vec<2,Size,glm::packed_highp>::vec;

	static constexpr short _elemcount = 2;

	Point(glm::vec<2,Size,glm::packed_highp> v): glm::vec<2,Size,glm::packed_highp>(v){}
	Point(Size v): glm::vec<2,Size,glm::packed_highp>(v){}

	Point(Size x, Size y): glm::vec<2,Size,glm::packed_highp>(x,y){}
};

template<typename Size>
struct Point<3,Size>: public PointType<Size>, public glm::vec<3,Size,glm::packed_highp>{
	using glm::vec<3,Size,glm::packed_highp>::vec;

	static constexpr short _elemcount = 3;

	Point(glm::vec<3,Size,glm::packed_highp> v): glm::vec<3,Size,glm::packed_highp>(v){}
	Point(Size v): glm::vec<3,Size,glm::packed_highp>(v){}

	Point(Size x, Size y, Size z): glm::vec<3,Size,glm::packed_highp>(x,y,z){}
};

using Point2d = Point<2,double>;
using Point3d = Point<3,double>;
using Point4d = Point<4,double>;

using Point2i = Point<2,int>;
using Point3i = Point<3,int>;
using Point4i = Point<4,int>;

using Point2f = Point<2,float>;
using Point3f = Point<3,float>;
using Point4f = Point<4,float>;