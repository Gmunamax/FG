#pragma once
struct Point3i{
	int x;
	int y;
	int z;
};

struct Point2d {
	double x;
	double y;
};

using Point2i = SDL_Point;

struct Point3d{
	double x;
	double y;
	double z;

	Point3d(){
		x = 0;
		y = 0;
		z = 0;
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