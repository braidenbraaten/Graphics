#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texcoord;

out vec2 vUV;
out vec4 vPosition;


void main()
{
	vPosition = position;
	vUV = texcoord;
	gl_Position = position;
}