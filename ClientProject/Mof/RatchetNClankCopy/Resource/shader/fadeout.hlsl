//! コンスタントバッファ
cbuffer cbSceneParam : register(b0) {
    matrix	mtxView			: packoffset(c0);
    matrix	mtxProj			: packoffset(c4);
};

cbuffer cbMeshParam : register(b1) {
    float4	cbvOffset		: packoffset(c0);
    float4	cbvSize			: packoffset(c1);
    float4	cbtOffset		: packoffset(c2);
    float4	cbtSize			: packoffset(c3);
    float4	cbColor			: packoffset(c4);
    matrix	mtxWorld		: packoffset(c5);
};

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

//////////////////
//! 新規のコンスタントバッファ作成
cbuffer cbSceneEffectParam : register(b4) {
    float4	cbTime : packoffset(c0);
};


//! 頂点属性
struct InputVS {
    float4	pos			: POSITION;
    float2	Tex			: TEXCOORD;
};
struct OutputVS {
    float4	pos			: SV_POSITION;
    float2	Tex			: TEXCOORD0;
    float4	color		: COLOR0;
};

//! 頂点シェーダ
OutputVS RenderVS(InputVS inVert) {
    OutputVS	outVert;

    float3 pv = mul(float4(inVert.pos * cbvSize.xyz + cbvOffset.xyz, 1), mtxWorld);
    float4 Pos = mul(float4(pv, 1), mtxView);
    outVert.pos = mul(Pos, mtxProj);

    outVert.Tex = inVert.Tex * cbtSize.xy + cbtOffset.xy;
    outVert.color = cbColor;

    return outVert;
}

//! ピクセルシェーダ
float4 RenderPS(OutputVS inPixel) : SV_TARGET{
    float4 color = txDiffuse.Sample(samLinear,
                                    inPixel.Tex) * inPixel.color;
    float4 alpha = (0.0f, 0.0f, 0.0f, 1.0f);

    // 1秒で遷移
    float blend = clamp(1.0f - cbTime, 0.0f, 1.0f);
    // 色を求める
//    color = lerp(color, alpha, blend);
    color.x = (color.x - blend * (alpha.x));
    color.y = (color.y - blend * (alpha.y));
    color.z = (color.z - blend * (alpha.z));
    color.w = color.w - blend * (alpha.w - color.w);
    /*
    color.x = 1.0f - color.x;
    color.y = 1.0f - color.y;
    color.z = 1.0f - color.z;
    */
    return color;
}

technique11 TShader {
    pass P0 {
        SetVertexShader(CompileShader(vs_4_0, RenderVS()));
        SetGeometryShader(NULL);
        SetHullShader(NULL);
        SetDomainShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, RenderPS()));
        SetComputeShader(NULL);
    }
}
