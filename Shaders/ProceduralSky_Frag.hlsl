struct PSInput
{
	float4 position : SV_POSITION;
	float3 worldDir : TEXCOORD0;
};

float RayleighPhase(float cosTheta)
{
    return 3.0 / (16.0 * 3.141592) * (1.0 + cosTheta * cosTheta);
}

static const float3 sunDirection = normalize(float3(0.0f, 1.0f, 0.0f));
static const float3 sunDirection_9AM = normalize(float3(-1.0f, 0.5f, 0.0f));
static const float3 sunDirection_4PM = normalize(float3(1.0f, 0.5f, 0.0f));

static const float3 skyColorDay = float3(0.6f, 0.8f, 1.0f);
static const float3 horizonColor = float3(0.8f, 0.9f, 1.0f);
static const float3 sunColor = float3(1.0f, 0.95f, 0.8f);

float4 PSMain(PSInput input) : SV_TARGET
{
	float3 dir = normalize(input.worldDir);
    
	float cosTheta = dot(dir, sunDirection_4PM);
	float rayleigh = RayleighPhase(cosTheta);
    
	float3 sky = lerp(horizonColor, skyColorDay, saturate(dir.y));
	float sunDisk = smoothstep(0.9995f, 1.0f, cosTheta);
	float3 color = sky + sunColor * sunDisk * rayleigh * 5.0f;
    
	return float4(color, 1.0f);
}
