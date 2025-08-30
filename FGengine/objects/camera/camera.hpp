#pragma once
#include <GL/glew.h>
#include "../properties/transform/transform.hpp"
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/color.hpp"

class Camera: public Position3d, public Rotation3d{
	enum CameraType{
		CAMERA_FRUSTUM, /* Perspective */
		CAMERA_ORTHO, 	/* Orthogonal */
		CAMERA_UI		/* Orthogonal with inverted depth-test */
	};

	double nearz = 1.2;
	double farz = 100;

	double aspectratio = 1;
	bool aspectratioforheight = false;
	double zoom = 1;
	double safezonesize = 1;

	CameraType cameratype = CAMERA_ORTHO;

	Color3f backgroundcolor = {0,0,0};

	Geometry2i viewportgeom;
	
	void PresentFrustum();
	void PresentOrtho();
	void PresentUI();

public:
	Camera();

	void SetAspectRatio(double newaspectratio);
	void SetIsAspectRatioForHeight(bool newvalue);

	void SetViewportSize(Geometry2i newgeom);
	Geometry2i GetViewportGeom();
	void Resize(Geometry2i newviewport);

	void SetBackgroundColor(Color3f newbgcolor);

	void SetFocusDistance(double value);

	void SetFrustum();
	void SetOrtho();
	void SetUI();

	void StartDrawing();
};