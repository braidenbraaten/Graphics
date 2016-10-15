#version 430
//Vertex attributes
layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texcoord; 

//uniforms that were passed in

 out vec2 vUV;

void main()
{
	
	vUV = texcoord;

	gl_Position = position;
}