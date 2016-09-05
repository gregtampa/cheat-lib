cbuffer FVSData : register(b0)
{
    float4x4 Projection;
};

struct FVSInput
{
    float2 Pos : POSITION;
    float4 Col : COLOR0;
    float2 Tex : TEXCOORD0;
};

struct FPSInput
{
    float4 Pos : SV_Position;
    float4 Col : COLOR0;
    float2 Tex : TEXCOORD0;
};

FPSInput main(FVSInput input)
{
    FPSInput output;

    output.Pos = mul(Projection, float4(input.Pos.xy, 0.0f, 1.0f));
    output.Col = input.Col;
    output.Tex = input.Tex;

    return output;
}
