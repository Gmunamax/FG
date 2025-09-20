#version 460

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 vcolor;
out vec4 color;

uniform mat4 objectmatrix = mat4(1);
uniform mat4 viewmatrix = mat4(1);
uniform mat4 projectionmatrix = mat4(1);

void main(){
	gl_Position = projectionmatrix * viewmatrix * objectmatrix * vec4(pos, 1.0);
	color = vcolor;
}