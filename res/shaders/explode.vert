#version 430
 layout(location = 0) in vec4 position;
 layout(location = 3) in vec2 texcoord;
//layout(location = 2) in vec4 normDir;

layout(location = 0) uniform sampler2D geoAlbedo;
layout(location = 1) uniform float deltaTime;

out vec2 vUV;

void main()
{
	float dt = deltaTime;

	//position = vec4(deltaTime, -deltaTime, 1,1);
	vUV = texcoord;

	gl_Position = position;
}

