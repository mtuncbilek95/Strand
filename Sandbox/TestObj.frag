#version 460 core

layout(location = 0) in vec3 vOutFragPos;
layout(location = 1) in vec3 vOutClipPos;
layout(location = 2) in vec3 vOutFragNorm;
layout(location = 3) in vec2 vOutTexCoord;
layout(location = 4) in mat3 vOutTBN;

layout(location = 0) out vec4 outColor;

void main()
{
	// Calculate the normal in world space
	vec3 normal = normalize(vOutTBN * vOutFragNorm);

	outColor = vec4(normal, 1.0);
}