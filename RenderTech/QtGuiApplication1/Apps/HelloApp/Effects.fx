#include "EffectCommon.fxh"

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_OUTPUT VS(float4 inPos : POSITION,float4 inColor:COLOR)
{
	VS_OUTPUT output;
	output.Pos=mul(inPos,WVP);
	output.Color=inColor;

	return output;
}

float4 PS(VS_OUTPUT input): SV_TARGET
{
	return input.Color;
}

technique11 ColorTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
