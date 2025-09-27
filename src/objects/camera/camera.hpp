#pragma once
#include "../properties/transform/transform.hpp"
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/color.hpp"

class CameraTransform{
	Point3d position;
	Point3d rotation;

protected:
	glm::mat4 viewm {1};
	bool needupdate = true;
	void ProceedPosition();
	void ProceedRotation();

	void ProceedTransform();

public:
	void SetPosition(Point3d newposition){
		position = newposition;
		needupdate = true;
	}
	Point3d& GetPosition(){
		return position;
	}

	void SetRotation(Point3d newrotation){
		rotation = newrotation;
		needupdate = true;
	}
	Point3d& GetRotation(){
		return rotation;
	}
};

class Camera: public CameraTransform{
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
	
public:
	Camera();

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

	void StartDrawing();
};