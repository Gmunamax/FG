#include "FGengine/window/windowBase.hpp"

void WindowBase::InitBackend(){
		GLenum glewres = glewInit();
	if(glewres != GLEW_OK)
		std::cout << glewGetErrorString(glewres) << std::endl;

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthRange(0.5,100);
}

WindowBase* WindowBase::GetWindowFromID(Uint32 id){
	return static_cast<WindowBase*>(SDL_GetWindowData(SDL_GetWindowFromID(id), windowdataname));
}

void WindowBase::Apply(){
	if(opened){
		WindowTitle::Apply();
		WindowSize::Apply();
		WindowVsync::Apply();
		WindowMinSize::Apply();
	}
}

void WindowBase::Select(){
	if(opened){
		SDL_GL_MakeCurrent(win,glcon);
	}
}

void SDL_TestForNull(void* pointer){
	if(pointer == nullptr){
		throw SDL_GetError();
	}
}

void WindowBase::Open(){
	if(not opened){
		win = SDL_CreateWindow(GetTitle().c_str(),GetPosition().x,GetPosition().y,GetSize().x,GetSize().y,GetFlags());
		SDL_TestForNull(win);
		glcon = SDL_GL_CreateContext(win);
		SDL_TestForNull(glcon);
		InitBackend();
		SDL_SetWindowData(win,windowdataname,this);
		opened = true;
	}
}
void WindowBase::Close(){
	if(opened){
		SDL_DestroyWindow(win);
		SDL_GL_DeleteContext(glcon);
		opened = false;
	}
}