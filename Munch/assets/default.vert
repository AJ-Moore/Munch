

#version 330 core
layout (location = 0) in vec4 Vertex;
layout (location = 1) in vec2 texCoordAtrib;
uniform mat4 wvpMat;
varying vec2 texCoord;
void main(){
	texCoord = texCoordAtrib;
	gl_Position = wvpMat * Vertex;
}