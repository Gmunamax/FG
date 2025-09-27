#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>

using Point2i = SDL_Point;

struct Point2d {
	double x;
	double y;

	static constexpr int _gldatatype = GL_DOUBLE;
	static constexpr short _elemcount = 2;

	Point2d(){
		x = 0;
		y = 0;
	}
	Point2d(double val){
		x = val;
		y = val;
	}
	Point2d(double x, double y){
		this->x = x;
		this->y = y;
	}
};


struct Point3i{
	int x;
	int y;
	int z;

	static constexpr int _gldatatype = GL_INT;
	static constexpr short _elemcount = 3;
};

struct Point3d{
	double x;
	double y;
	double z;

	static constexpr int _gldatatype = GL_DOUBLE;
	static constexpr short _elemcount = 3;

	Point3d(){
		x = 0;
		y = 0;
		z = 0;
	}

	Point3d(double val){
		x = val;
		y = val;
		z = val;
	}

	Point3d(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point3d(Point3i& v){
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Point3d operator+= (const Point3d& s){
		return{
			x+=s.x,
			y+=s.y,
			z+=s.z
		};
	}
	Point3d operator+ (const Point3d& s){
		return{
			x+s.x,
			y+s.y,
			z+s.z
		};
	}
	Point3d operator- (const Point3d& s){
		return{
			x-s.x,
			y-s.y,
			z-s.z
		};
	}
	Point3d operator* (const Point3d& s){
		return{
			x*s.x,
			y*s.y,
			z*s.z
		};
	}
};