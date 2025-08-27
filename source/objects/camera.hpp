#pragma once
#include "properties/geometry.hpp"
#include "structures/geometry.hpp"
#include "model/model.hpp"
#include <GL/glew.h>

class Camera: public Geometry3d{
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
	
	void PresentFrustum(){
		ProceedRotation();
		ProceedPosition();
	}
	void PresentOrtho(){
		ProceedRotation();
		ProceedPosition();
	}
	void PresentUI(){
		ProceedPosition();
	}

public:
	Camera(){
		
	}

	void SetAspectRatio(double newaspectratio){
		aspectratio = newaspectratio;
	}
	void SetIsAspectRatioForHeight(bool newvalue){
		aspectratioforheight = newvalue;
	}
	void SetViewportSize(Geometry2i newgeom){
		glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);
		viewportgeom = newgeom;
	}
	Geometry2i GetViewportGeom(){
		return viewportgeom;
	}

	void Resize(Geometry2i newviewport){
		SetAspectRatio((double)newviewport.w/(double)newviewport.h);
		SetViewportSize(newviewport);
		switch (cameratype) {
		case CAMERA_FRUSTUM:
			SetFrustum();
			break;
		case CAMERA_ORTHO:
			SetOrtho();
			break;
		case CAMERA_UI:
			SetUI();
			break;
		}
	}

	void SetBackgroundColor(Color3f newbgcolor){
		backgroundcolor = newbgcolor;
		glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
	}

	void SetFocusDistance(double value){
		nearz = value;
		if(cameratype == CAMERA_FRUSTUM)
			SetFrustum();
		else if(cameratype == CAMERA_ORTHO)
			SetOrtho();
	}

	void SetFrustum(){
		glLoadIdentity();
		glDepthFunc(GL_LESS);
		if(aspectratioforheight)
			glFrustum(-zoom,zoom, zoom*aspectratio,zoom*aspectratio, nearz,farz);
		else
			glFrustum(-zoom*aspectratio,zoom*aspectratio,-zoom,zoom, nearz,farz);
		cameratype = CAMERA_FRUSTUM;
	}
	void SetOrtho(){
		glLoadIdentity();
		glDepthFunc(GL_LESS);
		if(aspectratioforheight)
			glOrtho(-zoom,zoom, zoom*aspectratio,zoom*aspectratio, nearz,farz);
		else
			glOrtho(-aspectratio,aspectratio,-zoom,zoom, nearz,farz);
		cameratype = CAMERA_ORTHO;
	}
	void SetUI(){
		glLoadIdentity();
		glDepthFunc(GL_GEQUAL);
		if(aspectratioforheight)
			glOrtho(-zoom,zoom, zoom*aspectratio,zoom*aspectratio, nearz,farz);
		else
			glOrtho(-aspectratio,aspectratio,-zoom,zoom, nearz,farz);
		cameratype = CAMERA_UI;
	}
	// bool TestCollide(Model3d& object){
	// 	for(short i = 0; i < 6; i++){
	// 		for(auto v : Cube::cubea[i].GetVertexes()){
	// 			if(object.IsCollide( position + (v.GetPosition() * Point3d{safezonesize,safezonesize,safezonesize}))){
	// 				return true;
	// 			};
	// 		}
	// 	}
	// 	return false;
	// }

	void StartDrawing(){

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		switch (cameratype){
		case CAMERA_FRUSTUM:
			PresentFrustum();
			break;
		case CAMERA_ORTHO:
			PresentOrtho();
			break;
		case CAMERA_UI:
		 	PresentUI();
			break;
		}
	}
};