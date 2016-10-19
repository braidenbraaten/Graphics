#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 UV;
layout(location = 1) uniform float time;

out vec2 vUV;

vec4 warp(in vec4 pos, in float offset);

void main()
{
	 
	vUV = UV;
	gl_Position = position;// + warp(position, time );
}

vec4 warp(in vec4 pos, in float offset)
{
	vec4 result;

	for(int i = -11; i < 11; i++)
	{
		for(int j = -5; j < 5; j++)
		{
			result += pos + offset * 50;
		}
	}

	return result;
}