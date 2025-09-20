#pragma once
struct Colord{
	double r;
	double g;
	double b;
	double a;

	static constexpr short _gldatatype = GL_DOUBLE;
	static constexpr short _elemcount = 4;
};

struct Color3f{
	float r;
	float g;
	float b;
	float a;

	static constexpr short _gldatatype = GL_FLOAT;
	static constexpr short _elemcount = 4;

	Color3f(){
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}

	Color3f(float r, float g, float b, float a = 255){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void SetColor8888(float r, float g, float b, float a = 255){
		this->r = r/255;
		this->g = g/255;
		this->b = b/255;
		this->a = a/255;
	}
};

struct Color3i{
	short r;
	short g;
	short b;
	short a;

	Colord Color255to1f(){
		return{	
			(double)r/255,
			(double)g/255,
			(double)b/255,
			(double)a/255
		};
	}
};