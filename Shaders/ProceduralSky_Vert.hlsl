cbuffer CameraUBO : register(b0)
{
	matrix view;
	matrix proj;
	matrix invView;
	matrix invProj;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 worldDir : TEXCOORD0;
};

static const float4 newTriangle[6] =
{
	float4(-1.0f, -1.0f, 0.0f, 1.0f),
    float4(-1.0f, 1.0f, 0.0f, 1.0f),
    float4(1.0f, 1.0f, 0.0f, 1.0f),
	float4(-1.0f, -1.0f, 0.0f, 1.0f),
    float4(1.0f, 1.0f, 0.0f, 1.0f),
	float4(1.0f, -1.0f, 0.0f, 1.0f)
};

VSOutput VSMain(uint vertexID : SV_VertexID)
{
	VSOutput output;
	output.position = newTriangle[vertexID];
	
	float4 viewDir = mul(invProj, float4(output.position.xy, 1.0f, 1.0f));
	viewDir /= viewDir.w;
	output.worldDir = mul(invView, float4(normalize(viewDir.xyz), 0.0f)).xyz;
    
	return output;
}
