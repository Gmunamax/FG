**The FG project.**


# INTRODUCTION

FG ~~should be~~ is a game inspired by FNAF about a guy who works in a warehouse with robots.

I want this game to have a huge ammount of various controls, much more than in fnaf 7. Huge camera system, unusual walking, a lot of mechanics... A game for those people who beat 50/20 or for professional pianists.
Also while I will making this game I will learn a lot about different special, unusual and main things in programming. So, the second purpose of this project is for me.

Here are all files of this project. They are:

1) FG engine
2) FG

For now here is a demo of engine. Game itself will be coded later, after I make the basic engine


# BUILD

FG uses libraries that listed below:

* SDL2
* GL
* GLEW

You need install them to launch this application. With RPM/DNF you can type these commands:

	sudo dnf install SDL2
	sudo dnf install glew

GL library (OpenGL) is provided by your graphics card driver


To build app from source code you need to install also development files. On RPM/DNF distros usually these packages have "-devel" suffix. So, these commands should look like this:

	sudo dnf install SDL2-devel
	sudo dnf install glew-devel

dev files for GL (OpenGL) should be provided by your graphics card driver or by distro, idk

After installing libraries and dev files you can build this application. FG and FGengine use cmake for this. To build application type these commands in this directory:

	cmake .
	cd build
	make

Then, in FG directory should appear FG executable. This is it. Enjoy.


# VERSIONING

First release have version name 230825, but after I released it I decided to use [Semantic Versioning](https://semver.org/). So, this version also have version name v0.1.0. Other version will use correct versioning only.


# MINIMUM SYSTEM REQUIREMENTS

i dont know. everywere where works sdl2, opengl 4 and glew 2


# FUTURE OF PROJECT

Now changes and updates will be created less frequently. But if I have the opportunity, I will try to do something.



*Made By Gmunamax*
