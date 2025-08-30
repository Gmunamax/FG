#pragma once
#include <GL/glew.h>
#include "../properties/transform/transform.hpp"
#include "../properties/buffer/buffer.hpp"

class Model3d: public Position3d, public Rotation3d, public Scale3d, public Buffer3d{

	Point3d collidepos = {0,0,0};
	Point3d collidescale = {0,0,0};

	void Place();

	bool cancollide = false;

public:
	Model3d();

	void Load(std::vector<Point3d> points);

	bool IsCollide(Point3d obj);

	void Draw();
};