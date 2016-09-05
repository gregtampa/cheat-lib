struct FPSInput
{
    float4 Pos : SV_Position;
    float4 Col : COLOR0;
    float2 Tex : TEXCOORD0;
};

sampler Sampler : register(s0);
Texture2D Texture : register(t0);

float4 main(FPSInput input) : SV_Target
{
    return input.Col * Texture.Sample(Sampler, input.Tex);
}
