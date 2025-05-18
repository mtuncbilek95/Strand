#version 460 core

layout(location = 0) in vec3 vOutFragPos;
layout(location = 1) in vec3 vOutClipPos;
layout(location = 2) in vec3 vTBN0;
layout(location = 3) in vec3 vTBN1;
layout(location = 4) in vec3 vTBN2;
layout(location = 5) in vec4 vOutColor;
layout(location = 6) in vec2 vOutTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	// Calculate the normal in world space
	vec3 dummyExtract = vOutFragPos * vOutClipPos * vOutColor.xyz * vec3(vOutTexCoord, 1.0) * vTBN0 * vTBN1 * vTBN2;

	dummyExtract = vTBN2;
	outColor = vec4(dummyExtract, 1.0);
}