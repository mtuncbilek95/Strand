#version 460 core
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 vInPos;
layout(location = 1) in vec3 vInNormal;
layout(location = 2) in vec3 vInTangent;
layout(location = 3) in vec3 vInBinormal;
layout(location = 4) in vec4 vInColor;
layout(location = 5) in vec2 vInTexCoord;

layout(set = 0, binding = 0) uniform ModelMat
{
	mat4 model;
} model;

layout(set = 0, binding = 1) uniform CamDetail
{
	mat4 view;
	mat4 projection;
} camera;

layout(location = 0) out vec3 vOutFragPos;
layout(location = 1) out vec3 vOutClipPos;
layout(location = 2) out vec3 vTBN0;
layout(location = 3) out vec3 vTBN1;
layout(location = 4) out vec3 vTBN2;
layout(location = 5) out vec4 vOutColor;
layout(location = 6) out vec2 vOutTexCoord;

void main()
{
	vec3 fragPos = (model.model * vec4(vInPos.x, -vInPos.y, vInPos.z, 1.0)).xyz;
	vec3 fragNormal = inverse(transpose(mat3(model.model))) * vInNormal;
	vec4 clipPos = camera.projection * camera.view * vec4(fragPos, 1.0);
	
	vOutFragPos = fragPos;
	vOutClipPos = clipPos.xyz / clipPos.w;
	vOutTexCoord = vInTexCoord;

	vTBN0 = normalize(model.model * vec4(vInTangent, 0.0)).xyz;
	vTBN1 = normalize(model.model * vec4(vInBinormal, 0.0)).xyz;
	vTBN2 = normalize(fragNormal);

	gl_Position = clipPos;

	vOutColor = vInColor;
}