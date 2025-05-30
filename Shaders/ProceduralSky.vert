#version 460 core
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) out vec3 vWorldDir;

layout(set = 0, binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    mat4 invView;
    mat4 invProj;
} camera;

void main()
{
    vec2 pos = vec2((gl_VertexIndex == 0) ? -1.0 : 3.0,
                    (gl_VertexIndex == 1) ? -1.0 : 3.0);

    gl_Position = vec4(pos, 0.0, 1.0);

    vec4 viewDir = camera.invProj * vec4(pos, 1.0, 1.0);
    viewDir /= viewDir.w;
    vec3 worldDir = (camera.invView * vec4(normalize(viewDir.xyz), 0.0)).xyz;

    vWorldDir = worldDir;
}