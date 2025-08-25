#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../../structures/point.hpp"
#include "../../config.hpp"

class Buffer3d{
	GLsizei size;
	
	GLuint buf = 0;
	bool free = true;

	#ifdef DEBUG
	void Log(short& axiscount, GLenum& elemdatatype, void*& array, long long& arraysize, long long& arrayelemcount){
		std::cout << '\n' << '\n';
		std::cout << arraysize << '\n';
		std::cout << array << '\n';
		std::cout << axiscount << '\n';
		std::cout << elemdatatype << '\n';
		std::cout << arraysize/arrayelemcount*axiscount << '\n';
		std::cout << '/' << '\n';
		std::cout << arrayelemcount/axiscount << '\n';
		std::cout << '\n';
	}
	#endif

	void Bufdata(short axiscount, GLenum elemdatatype, void* array, long long arraysize, long long arrayelemcount){
		glBufferData(GL_ARRAY_BUFFER, arraysize, array, GL_STATIC_DRAW);
		glVertexAttribPointer(0, axiscount, elemdatatype, GL_FALSE, arraysize/arrayelemcount*axiscount, 0);
		size = arrayelemcount/axiscount;
		free = false;

		#ifdef DEBUG
		Log(axiscount,elemdatatype,array,arraysize,arrayelemcount);
		#endif
	}

public:

	Buffer3d() {}

	void buffer(std::vector<Point3d>& data){
		glGenBuffers(1,&buf);
		glBindBuffer(GL_ARRAY_BUFFER,buf);

		Bufdata(3, GL_DOUBLE, data.data(), sizeof( Point3d )*data.size(), data.size()*3);
		glEnableVertexAttribArray(0);
	}

	void drawBuf(){
		glBindBuffer(GL_ARRAY_BUFFER,buf);
		glDrawArrays(GL_TRIANGLES,0,size);
	}

	~Buffer3d(){
		if(not free)
			glDeleteBuffers(1,&buf);
		
		#ifdef DEBUG
		std::cout << "Some buffer: Bye!" << '\n';
		#endif
	}
};