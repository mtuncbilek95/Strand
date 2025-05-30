#version 450

layout(location = 0) in vec3 vWorldDir;
layout(location = 0) out vec4 outColor;

const vec3 sunDirection = normalize(vec3(0.0, 1.0, 0.0));

const vec3 skyColorDay = vec3(0.6, 0.8, 1.0);
const vec3 horizonColor = vec3(0.8, 0.9, 1.0);
const vec3 sunColor = vec3(1.0, 0.95, 0.8);

float rayleighPhase(float cosTheta)
{
    return 3.0 / (16.0 * 3.141592) * (1.0 + cosTheta * cosTheta);
}

void main()
{
    vec3 dir = normalize(vWorldDir);

    float cosTheta = dot(dir, sunDirection);
    float rayleigh = rayleighPhase(cosTheta);

    vec3 sky = mix(horizonColor, skyColorDay, max(dir.y, 0.0));

    float sunDisk = smoothstep(0.9995, 1.0, cosTheta);

    vec3 color = sky + sunColor * sunDisk * rayleigh * 5.0;

    outColor = vec4(color, 1.0);
}
