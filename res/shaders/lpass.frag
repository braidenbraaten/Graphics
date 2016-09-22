#version 430

layout(location = 0) uniform mat4 view;
layout(location = 1) uniform mat4 proj;

layout(location = 2) uniform sampler2D albedoMap;
layout(location = 3) uniform sampler2D normalMap;
layout(location = 4) uniform sampler2D specularMap;
layout(location = 5) uniform sampler2D positionMap;
layout(location = 6) uniform sampler2D depthMap;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 specularColor;

in vec2 vUV; //the texcoords coming in from the vert shader

uniform vec4 lDir = normalize(vec4(1,0,-1,0));

void main()
{
vec3 L = normalize((view * lDir).xyz); //light rays
vec3 N = normalize(texture(normalMap, vUV).xyz); //normals of the geo

vec3 R = reflect(L, N); //reflecting the light rays off of the normals of the geo
vec3 E = -normalize(texture(positionMap, vUV).xyz);
float sP = 2; //specular power

float lamb = max(0,-dot(L,N));
float spec = max(0, -dot(E,R)); //if rays directly hitting eye

if(spec > 0)
spec = pow(spec, sP);

	outColor = texture(albedoMap, vUV) * lamb;
	specularColor = texture(specularMap, vUV) * spec;
}