#version 430

out vec4 outColor;
out vec4 crossColor;

in vec2 vUV;

layout(location = 0) uniform sampler2D map;
layout(location = 1) uniform float time;
layout(location = 2) uniform sampler2D bloom;

vec4 sobel(in sampler2D map, in vec2 UV);
vec4 crossblur(in sampler2D map, in vec2 UV);

void main()
{
	vec4 b = texture(bloom, vUV);
	outColor   = sobel    (map, vUV);
	crossColor = crossblur(map, vUV) /  (outColor - b) ;
}

vec4 crossblur(in sampler2D map, in vec2 UV)
{
	vec2 sDim = textureSize(map,0).xy;
	vec4 retval = vec4(0,0,0,0);
	for(int i = -9; i <= 9; ++i)
	{
		retval += texture(map, UV + vec2( i, 0)/sDim);
		retval += texture(map, UV + vec2( 0, i)/sDim);
	}
	return retval / 361;
}

vec4 sobel(in sampler2D map, in vec2 UV)
{
	vec2 sDim = textureSize(map,0).xy;
	vec4 yColor = 
	texture(map,UV + vec2( 1, -1)/sDim)   +
	texture(map,UV + vec2( 0, -1)/sDim)*2 +
	texture(map,UV + vec2(-1, -1)/sDim)   -
	texture(map,UV + vec2( 1,  1)/sDim)    -
	texture(map,UV + vec2( 0,  1)/sDim)*2  -
	texture(map,UV + vec2(-1,  1)/sDim);

	vec4 xColor = 
	texture(map,UV + vec2(-1, -1)/sDim)   +
	texture(map,UV + vec2(-1,  0)/sDim)*2 +
	texture(map,UV + vec2(-1,  1)/sDim)   -
	texture(map,UV + vec2( 1, -1)/sDim)   -
	texture(map,UV + vec2( 1,  0)/sDim)*2 -
	texture(map,UV + vec2( 1,  1)/sDim);

	return sqrt(yColor * yColor + xColor * xColor);
}