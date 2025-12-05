#pragma once
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/color.hpp"
#include "FGengine/properties/transform/worldpoint.hpp"
#include "FGengine/shaders/shaderprogram.hpp"
#include "FGengine/shaders/shaderproperty.hpp"

class ShaderData{
public:

	Uniforms::Umat4 proj {"fg_projectionmatrix"};
	Uniforms::Umat4 view {"fg_viewmatrix"};
	// glm::mat4 proj;
	// bool needupdateproj;
	// glm::mat4 view;
	// bool needupdateview;

};

class ShaderHandler: virtual private ShaderData{
protected:
	void SendMatrix(){
		if(needupdateview){
			glUniformMatrix4fv( glGetUniformLocation(shaderprogram, "viewmatrix"), 1, GL_FALSE, glm::value_ptr((glm::mat4)*viewm));
			needupdateview = false;
		}

		if(needupdateproj){
			glUniformMatrix4fv( glGetUniformLocation(shaderprogram, "projectionmatrix"), 1, GL_FALSE, glm::value_ptr((glm::mat4)*projm));
			needupdateproj = false;
		}
	}
};

class AspectRatio{
	double aspectratio = 1;

public:
	void SetAspectRatio(double newaspectratio);
	double GetAspectRatio();
};

class FOV{
	double fov = 75;

public:
	void SetFOV(double);
	double GetFOV();
};

class ViewDistance{
	double nearz = 1;
	double farz = 200;
};

class Viewport{
	Geometry2i viewportgeom;

public:
	void SetViewportGeom(Geometry2i newgeom);
	Geometry2i GetViewportGeom();
	void Resize(Geometry2i newviewport);
};

class Background{
	Colord backgroundcolor = {0,0,0};

public:
	void SetBackgroundColor(Colord newbgcolor);
	Colord GetBackgroundColor();
};

class CameraType{
protected:
	enum CameraTypeEnum{
		CAMERA_FRUSTUM, /* Perspective */
		CAMERA_ORTHO, 	/* Orthogonal */
		CAMERA_UI		/* Orthogonal with inverted depth-test */
	};

	CameraTypeEnum cameratype = CAMERA_ORTHO;

public:
	void SetFrustum();
	void SetOrtho();
	void SetUI();
};

template<typename PointType = Point3d>
class Camera: public WorldPoint<PointType>, public CameraType, public Background, pubilc Viewport, public ViewDistance, public FOV, public AspectRatio{
public:
	Camera(){};

	void StartDrawing(){

		glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		Camera::ProceedTransformations();
		ShaderProgram::SetProjectionMatrix(&projm);
		ShaderProgram::SetViewMatrix(Camera::GetMatrix());
	}
};