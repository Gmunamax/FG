#pragma once
#include <GL/glew.h>
#include "../properties/transform/transform.hpp"
#include "../properties/buffer/buffer.hpp"

template<typename VertexType>
class Model: public Transform<typename VertexType::VertexPosition::DataType>, public Drawer<VertexType>{

	VertexType::VertexPosition::DataType collidepos;
	VertexType::VertexPosition::DataType collidescale;

public:
	Model(){};

	// bool IsCollide(Point3d obj);

	void Draw();
};

// template<typename VertexType> bool Model<VertexType>::IsCollide(Point3d obj)
// {
// 	if(cancollide){
// 		Point3d collidestart = Model::GetPosition() + collidepos;
// 		Point3d collideend = collidestart + collidescale;

// 		bool resultx = (collidestart.x < obj.x) and (obj.x < collideend.x);
// 		bool resulty = (collidestart.y < obj.y) and (obj.y < collideend.y);

// 		return (resultx and resulty);
// 	}
// 	return false;
// }

template<typename VertexType> void Model<VertexType>::Draw(){
	Model::ProceedTransformations();
	Model::BindTransformations();
	Model::drawBuf();
}