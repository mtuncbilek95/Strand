struct MeshGeometry
{
    float3 vInPos : POSITION;
    float3 vInNormal : NORMAL;
    float3 vInTangent : TANGENT;
    float3 vInBinormal : BITANGENT;
    float4 vInColor : COLOR;
    float2 vInTexCoord : TEXCOORD0;
}

struct CoarseVertex
{
    float3 vOutFragPos : TEXCOORD0;
    float3 vOutClipPos : TEXCOORD1;
    float3 vTBN0 : TEXCOORD2;
    float3 vTBN1 : TEXCOORD3;
    float3 vTBN2 : TEXCOORD4;
    float4 vOutColor : COLOR0;
    float2 vOutTexCoord : TEXCOORD5;
}

struct VertexOut
{
    CoarseVertex coarseVertex : CoarseVertex;
    float4 sv_position : SV_Position;
}

struct ModelMat
{
    float4x4 modelMatrix;
};
ParameterBlock<ModelMat> gModel;

struct CamMat
{
    float4x4 viewMatrix;
    float4x4 projMatrix;
};
ParameterBlock<CamMat> gCam;

[shader("vertex")]
VertexOut main(MeshGeometry meshInput) : SV_POSITION
{
    VertexOut output;

    return output;
}