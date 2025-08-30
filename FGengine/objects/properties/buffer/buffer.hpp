#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "FGengine/structures/point.hpp"

class Buffer3d{
	GLsizei size;
	
	GLuint buf = 0;
	bool free = true;


	void Log(short& axiscount, GLenum& elemdatatype, void*& array, long long& arraysize, long long& arrayelemcount);

	void Bufdata(short axiscount, GLenum elemdatatype, void* array, long long arraysize, long long arrayelemcount);

protected:

	Buffer3d();

	void buffer(std::vector<Point3d>& data);

	void drawBuf();

	~Buffer3d();
};