//! コンスタントバッファ
cbuffer cbSceneParam : register(b0)
{
    float4 vecViewPos : packoffset(c0);
    matrix mtxView : packoffset(c1);
    matrix mtxProj : packoffset(c5);
};

cbuffer cbMeshParam : register(b1)
{
    matrix mtxWorld : packoffset(c0);
    float4 colRevise : packoffset(c4);
    float4 CoordsRevise : packoffset(c5);
};

cbuffer cbMaterialParam : register(b2)
{
    float4 matDiffuse : packoffset(c0);
    float4 matAmbient : packoffset(c1);
    float4 matSpeculer : packoffset(c2);
    float4 matEmissive : packoffset(c3);
    float matPower : packoffset(c4);
};

cbuffer cbLightParam : register(b3)
{
    float3 litDirection : packoffset(c0);
    float4 litDiffuse : packoffset(c1);
    float4 litAmbient : packoffset(c2);
    float4 litSpeculer : packoffset(c3);
};

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

//! 頂点属性
struct InputVS
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 Tex : TEXCOORD;
    float4 color : COLOR0;
};
struct OutputVS
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float3 wpos : COLOR0;
    
    float4 pos2 : COLOR1;
};

//! 新規のコンスタントバッファ作成
cbuffer cbLightPillarParam : register(b4)
{
    float4 cblgPosition : packoffset(c0);
    float4 cblgDiffuse : packoffset(c1);
    float4 cblgAttenuation : packoffset(c2);
}


//! 頂点シェーダ
OutputVS RenderVS(InputVS inVert)
{
    OutputVS outVert;

    matrix mtxVP = mul(mtxView, mtxProj);
    float4 Pos = float4(inVert.pos.xyz, 1.0);
    outVert.pos2 = inVert.pos;
    Pos = mul(Pos, mtxWorld);
    outVert.pos = mul(Pos, mtxVP);
    outVert.normal = normalize(mul(inVert.normal, (float3x3) mtxWorld));
    outVert.wpos = Pos;
    return outVert;
}

//! ピクセルシェーダ
float4 RenderPS(OutputVS inPixel) : SV_TARGET
{
	//法線
    float3 N = normalize(inPixel.normal);
	//ハーフランバートライティング
    float l = dot(N, -litDirection);
    l = l * 0.5f + 0.5f;
    l *= l;
    float3 amb = litAmbient.xyz * matAmbient.xyz;
    float3 diff = l * litDiffuse.xyz * matDiffuse.xyz;
	//ポイントライティング
    float3 point_light_vec = cblgPosition.xyz - inPixel.wpos.xyz;
    float point_diff = length(point_light_vec);
    point_light_vec = normalize(point_light_vec);
    float point_light = dot(N, point_light_vec);
    float Att = 1.0f / (cblgAttenuation.x + cblgAttenuation.y * point_diff + cblgAttenuation.z * point_diff * point_diff);
    point_light *= Att;
    diff += clamp(point_light, 0.0f, 1.0f) * cblgDiffuse.xyz * matDiffuse.xyz;
    
    // result
    float4 emissive = matEmissive;

    //float3 p = (inPixel.wpos.xyz);
    float3 p = (inPixel.pos2.xyz);
    float3 c = (0.0f, 0.0f, 0.0f);
    p = normalize(p);
    float camera_diff = distance(p, c);
    //return float4(0.2f, 0.6f, 0.6f, 1.0f);
    
    //emissive.xyzw = float4(0.0f, point_light * Att * 2000000000.0f, 0.0f, point_light);
    //emissive.xyzw = float4(0.0f, camera_diff, 0.0f, 0.0f);
    emissive.xyzw = float4(0.0f, 0.5, 0.0f, 0.0f);
    //float4 base_color = float4(0.1f, 0.1f, 0.3f, 0.0f);
    //float4 LP = float4(saturate(emissive.xyz + amb + diff), matDiffuse.w) + base_color;
    float4 LP = float4(saturate(emissive.xyz + amb + diff), matDiffuse.w);
    //float4 LP = float4(saturate(matEmissive.xyz + amb + diff), matDiffuse.w);
    //LP *= camera_diff * 1.8;
    return LP;
}

technique11 TShader
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, RenderVS()));
        SetGeometryShader(NULL);
        SetHullShader(NULL);
        SetDomainShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, RenderPS()));
        SetComputeShader(NULL);
    }
}
