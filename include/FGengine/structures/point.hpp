#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

template<glm::length_t Lenght, typename SizeType, glm::qualifier Q = glm::packed>
struct Point: public glm::vec<Lenght, SizeType, Q> {
	using glm::vec<Lenght, SizeType, Q>::vec;

	Point(glm::vec<Lenght, SizeType, Q> c): glm::vec<Lenght, SizeType, Q>::vec(c){}
};

template<glm::length_t Lenght, glm::qualifier Q>
struct Point<Lenght, short, Q>: public glm::vec<Lenght, short, Q>{
	using glm::vec<Lenght, short, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_SHORT;}

	Point(glm::vec<Lenght, short, Q> c): glm::vec<Lenght, short, Q>::vec(c){}
};

template<glm::length_t Lenght, glm::qualifier Q>
struct Point<Lenght, int, Q>: public glm::vec<Lenght, int, Q>{
	using glm::vec<Lenght, int, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_INT;}

	Point(glm::vec<Lenght, int, Q> c): glm::vec<Lenght, int, Q>::vec(c){}
};

template<glm::length_t Lenght, glm::qualifier Q>
struct Point<Lenght, float, Q>: public glm::vec<Lenght, float, Q>{
	using glm::vec<Lenght, float, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_FLOAT;}

	Point(glm::vec<Lenght, float, Q> c): glm::vec<Lenght, float, Q>::vec(c){}
};

template<glm::length_t Lenght, glm::qualifier Q>
struct Point<Lenght, double, Q>: public glm::vec<Lenght, double, Q>{
	using glm::vec<Lenght, double, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_DOUBLE;}

	Point(glm::vec<Lenght, double, Q> c): glm::vec<Lenght, double, Q>::vec(c){}
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