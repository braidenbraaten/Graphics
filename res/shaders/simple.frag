#version 430

out vec4 outColor;

in vec4 vPosition;
in vec2 vUV;

void main()
{
	outColor = vec4(vUV, 1, 1);
}