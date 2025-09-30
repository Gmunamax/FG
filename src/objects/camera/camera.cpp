#include "FGengine/objects/camera.hpp"
#include "FGengine/shaders/shaderprogram.hpp"
#include <iostream>

void CameraParams::SetAspectRatio(double newaspectratio){
	aspectratio = newaspectratio;
}

void CameraParams::SetViewportSize(Geometry2i newgeom){
	glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);
	viewportgeom = newgeom;
}

Geometry2i CameraParams::GetViewportGeom(){
	return viewportgeom;
}

void CameraParams::Resize(Geometry2i newviewport){
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

void CameraParams::SetBackgroundColor(Colord newbgcolor){
	backgroundcolor = newbgcolor;
}

// void CameraParams::SetFocusDistance(double value){
// 	nearz = value;
// 	if(cameratype == CAMERA_FRUSTUM)
// 		SetFrustum();
// 	else if(cameratype == CAMERA_ORTHO)
// 		SetOrtho();
// }

void CameraParams::SetFOV(double newfov){
	this->fov = newfov;
}

void CameraParams::SetFrustum(){
	glDepthFunc(GL_LESS);
	projm = glm::perspective(fov,aspectratio,nearz,farz);
	cameratype = CAMERA_FRUSTUM;
	ShaderProgram::UpdateProjectionMatrix();
}

void CameraParams::SetOrtho(){
	glDepthFunc(GL_LESS);
	projm = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_ORTHO;
	ShaderProgram::UpdateProjectionMatrix();
}

void CameraParams::SetUI(){
	glDepthFunc(GL_GEQUAL);
	projm = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_UI;
	ShaderProgram::UpdateProjectionMatrix();
}

Colord CameraParams::GetBackgroundColor(){
	return backgroundcolor;
}