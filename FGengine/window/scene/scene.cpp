#include <iostream>
#include "windowScene.hpp"

void WindowDrawing::Draw(){
	if(frameskip <= 0){
		if(needupdate){

			t1 = std::chrono::steady_clock::now();

			glPushMatrix();
			GetScene()->cam.StartDrawing();
			GetScene()->Drawing();
			glPopMatrix();
			SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

			t2 = std::chrono::steady_clock::now();
			std::chrono::nanoseconds t = (t2 - t1);


			needupdate = false;

			glFlush();

			frameskip = std::chrono::duration_cast<std::chrono::milliseconds>(t).count()/frametime;

			long long f = (frametime *1000 *1000); //nanoseconds
			stepsize = ((double)t.count()/frametime)*(frameskip+1);
			stepsize = stepsize /1000 /1000; //to miliseconds

			/* to avoid false positives */
			if(frameskip == 1)
				frameskip = 0;
		}
	}
	else{
		std::cout << "Frameskip: " << (int)frameskip << " left\n" << std::endl;
		frameskip--;
	}
}