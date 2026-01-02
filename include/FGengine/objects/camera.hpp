#pragma once
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/color.hpp"
#include "FGengine/properties/transform/worldpoint.hpp"
// #include "FGengine/shaders/shaderprogram.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType = Point3d>
class Camera: public WorldPoint<PointType>{
	Uniforms::Umat4 proj {"fg_projectionmatrix"};
	// Uniforms::Umat4 view {"fg_viewmatrix"};

protected:
	void SendMatrix(){
		Shader::SendUniformForAll(proj);
		Shader::SendUniformForAll(*Camera::WorldPoint::GetMatrix());
		// Shader::SendUniformForAll(view);
	}


private:
	double aspectratio = 1;

public:
	void SetAspectRatio(double newaspectratio){
		aspectratio = newaspectratio;
	}
	double GetAspectRatio(){
		return aspectratio;
	}


private:
	double fov = 75;

public:
	void SetFOV(double newfov){
		this->fov = newfov;
	}
	double GetFOV(){
		return fov;
	}

private:

	double nearz = 1;
	double farz = 200;

private:

	Geometry2i viewportgeom;

public:
	void SetViewportGeom(Geometry2i newgeom){
		glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);
		viewportgeom = newgeom;
	}

	Geometry2i GetViewportGeom(){
		return viewportgeom;
	}

	void Resize(Geometry2i newviewport){
		SetAspectRatio((double)newviewport.w/(double)newviewport.h);
		SetViewportGeom(newviewport);
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

private:

	Colord backgroundcolor = {0,0,0};

public:
	void SetBackgroundColor(Colord newbgcolor){
		backgroundcolor = newbgcolor;
	}
	Colord GetBackgroundColor(){
		return backgroundcolor;
	}



protected:
	enum CameraTypeEnum{
		CAMERA_FRUSTUM, /* Perspective */
		CAMERA_ORTHO, 	/* Orthogonal */
		CAMERA_UI		/* Orthogonal with inverted depth-test */
	};

	CameraTypeEnum cameratype = CAMERA_ORTHO;

public:
	void SetFrustum(){
		glDepthFunc(GL_LESS);
		proj = glm::perspective(fov,aspectratio,nearz,farz);
		cameratype = CAMERA_FRUSTUM;
		// ShaderProgram::UpdateProjectionMatrix();
	}
	void SetOrtho(){
		glDepthFunc(GL_LESS);
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		cameratype = CAMERA_ORTHO;
		// ShaderProgram::UpdateProjectionMatrix();
	}

	void SetUI(){
		glDepthFunc(GL_GEQUAL);
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		cameratype = CAMERA_UI;
		// ShaderProgram::UpdateProjectionMatrix();
	}



public:
	Camera(){};

	void StartDrawing(){

		glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		Camera::ProceedTransformations();
		Camera::SendMatrix();
		// ShaderProgram::SetProjectionMatrix(&proj);
		// ShaderProgram::SetViewMatrix(Camera::GetMatrix());
	}
};