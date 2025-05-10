#version 460 core

layout(location = 0) in vec3 fInFragPos;
layout(location = 1) in vec3 fInClipPos;
layout(location = 2) in vec3 fInFragNorm;
layout(location = 3) in vec2 fInTexCoord;
layout(location = 4) in mat3 fInTBN;

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}