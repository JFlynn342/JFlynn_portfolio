TextureCube SkyboxTexture;
SamplerState TrilinearSampler;

struct VS_OUTPUT
{
	float4 Position: SV_Position;
	float3 TextureCoordinates : TEXCOORD;
};

float4 main(VS_OUTPUT IN) : SV_TARGET
{
	return SkyboxTexture.Sample(TrilinearSampler, IN.TextureCoordinates);
}