#pragma once
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/color.hpp"
#include "FGengine/properties/transform/worldpoint.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

class CameraParams{
protected:
	enum CameraType{
		CAMERA_FRUSTUM, /* Perspective */
		CAMERA_ORTHO, 	/* Orthogonal */
		CAMERA_UI		/* Orthogonal with inverted depth-test */
	};

	glm::mat4 projm {1};

	double nearz = 1;
	double farz = 200;
	double fov = 75;

	double aspectratio = 1;
	double zoom = 1;

	CameraType cameratype = CAMERA_ORTHO;

	Colord backgroundcolor = {0,0,0};

	Geometry2i viewportgeom;

	CameraParams(){};

public:
	void SetAspectRatio(double newaspectratio);

	void SetViewportSize(Geometry2i newgeom);
	Geometry2i GetViewportGeom();
	void Resize(Geometry2i newviewport);

	void SetBackgroundColor(Colord newbgcolor);
	Colord GetBackgroundColor();

	void SetFOV(double);

	void SetFrustum();
	void SetOrtho();
	void SetUI();
};

template<typename PointType = Point3d>
class Camera: public CameraParams, public WorldPoint<PointType>{
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