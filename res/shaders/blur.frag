#version 430
layout(location = 0) uniform sampler2D geoAlbedo;

layout(location = 1) uniform sampler2D prevGeoAlbedo;


 in vec2 vUV;


out vec4 outColor;
void main()
{
vec4 geo = texture(geoAlbedo, vUV );
vec4 prev = texture(prevGeoAlbedo, vUV);

    prev.a = .1;
	geo *= .5;
	prev *= .5;

	outColor = (geo - prev);
}