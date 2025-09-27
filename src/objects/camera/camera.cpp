#include "camera.hpp"
#include "FGengine/shaders/shaderprogram.hpp"

Camera::Camera(){}

void CameraTransform::ProceedPosition(){
	viewm = glm::translate(viewm,glm::vec3{position.x,position.y,position.z});
}
void CameraTransform::ProceedRotation(){
	if(rotation.x != 0)
		viewm = glm::rotate(viewm,(float)glm::radians(rotation.x),glm::vec3{1,0,0});
	if(rotation.y != 0)
		viewm = glm::rotate(viewm,(float)glm::radians(rotation.y),glm::vec3{0,1,0});
	if(rotation.z != 0)
		viewm = glm::rotate(viewm,(float)glm::radians(rotation.z),glm::vec3{0,0,1});
}
void CameraTransform::ProceedTransform(){
	if(CameraTransform::needupdate){
		ProceedPosition();
		ProceedRotation();
		needupdate = false;
		ShaderProgram::UpdateViewMatrix();
	}
}


void Camera::SetAspectRatio(double newaspectratio){
	aspectratio = newaspectratio;
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

void Camera::SetBackgroundColor(Colord newbgcolor){
	backgroundcolor = newbgcolor;
}

// void Camera::SetFocusDistance(double value){
// 	nearz = value;
// 	if(cameratype == CAMERA_FRUSTUM)
// 		SetFrustum();
// 	else if(cameratype == CAMERA_ORTHO)
// 		SetOrtho();
// }

void Camera::SetFOV(double newfov){
	this->fov = newfov;
}

void Camera::SetFrustum(){
	glDepthFunc(GL_LESS);
	projm = glm::perspective(fov,aspectratio,nearz,farz);
	cameratype = CAMERA_FRUSTUM;
	ShaderProgram::UpdateProjectionMatrix();
}

void Camera::SetOrtho(){
	glDepthFunc(GL_LESS);
	projm = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_ORTHO;
	ShaderProgram::UpdateProjectionMatrix();
}

void Camera::SetUI(){
	glDepthFunc(GL_GEQUAL);
	projm = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_UI;
	ShaderProgram::UpdateProjectionMatrix();
}

Colord Camera::GetBackgroundColor(){
	return backgroundcolor;
}

void Camera::StartDrawing(){

	glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	ProceedTransform();
	ShaderProgram::SetProjectionMatrix(&projm);
	ShaderProgram::SetViewMatrix(&viewm);
}