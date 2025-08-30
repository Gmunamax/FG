#include "camera.hpp"

void Camera::PresentFrustum(){
	ProceedRotation();
	ProceedPosition();
}

void Camera::PresentOrtho(){
	ProceedRotation();
	ProceedPosition();
}

void Camera::PresentUI(){
	ProceedPosition();
}

Camera::Camera(){}

void Camera::SetAspectRatio(double newaspectratio){
	aspectratio = newaspectratio;
}

void Camera::SetIsAspectRatioForHeight(bool newvalue){
	aspectratioforheight = newvalue;
}

void Camera::SetViewportSize(Geometry2i newgeom){
	glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);
	viewportgeom = newgeom;
}

Geometry2i Camera::GetViewportGeom(){
	return viewportgeom;
}

void Camera::Resize(Geometry2i newviewport){
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

void Camera::SetBackgroundColor(Color3f newbgcolor){
	backgroundcolor = newbgcolor;
	glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
}

void Camera::SetFocusDistance(double value){
	nearz = value;
	if(cameratype == CAMERA_FRUSTUM)
		SetFrustum();
	else if(cameratype == CAMERA_ORTHO)
		SetOrtho();
}

void Camera::SetFrustum(){
	glLoadIdentity();
	glDepthFunc(GL_LESS);
	if(aspectratioforheight)
		glFrustum(-zoom,zoom, -zoom*aspectratio,zoom*aspectratio, nearz,farz);
	else
		glFrustum(-zoom*aspectratio,zoom*aspectratio,-zoom,zoom, nearz,farz);
	cameratype = CAMERA_FRUSTUM;
}

void Camera::SetOrtho(){
	glLoadIdentity();
	glDepthFunc(GL_LESS);
	if(aspectratioforheight)
		glOrtho(-zoom,zoom, zoom*aspectratio,zoom*aspectratio, nearz,farz);
	else
		glOrtho(-aspectratio,aspectratio,-zoom,zoom, nearz,farz);
	cameratype = CAMERA_ORTHO;
}

void Camera::SetUI(){
	glLoadIdentity();
	glDepthFunc(GL_GEQUAL);
	if(aspectratioforheight)
		glOrtho(-zoom,zoom, zoom*aspectratio,zoom*aspectratio, nearz,farz);
	else
		glOrtho(-aspectratio,aspectratio,-zoom,zoom, nearz,farz);
	cameratype = CAMERA_UI;
}

void Camera::StartDrawing(){

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