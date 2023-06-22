
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
};

struct VSInput
{
    float4 pos : POSITIONT;
    float2 uv  : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv :  TEXCOORD0;
};

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    return psIn;
}

Texture2D<float4> mainRenderTargetTexture : register(t0);
sampler Sampler : register(s0);

float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
    float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);
    float t = dot(color.xyz, float3(0.2125f,0.7154f,0.0721f));
    
    clip(t - 1.0f);
    
    return color;

}

