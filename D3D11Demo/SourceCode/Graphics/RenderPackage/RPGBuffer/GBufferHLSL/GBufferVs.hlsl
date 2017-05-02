//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼各種行列▼▼▼*/
cbuffer cbTransform:register(b0)
{
	column_major float4x4	transformMat;
	column_major float4x4	worldMat;
	column_major float4x4	viewMat;
	column_major float4x4	projMat;
	float4	viewVector;
};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct vertexIn
{
	float4	pos			:	POSITION;
	float4	normal		:	NORMAL;
	float4	texUV			:	TEX_UV;
};
/*▼▼▼頂点OUT▼▼▼*/
struct vertexOut
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.wPos = mul(In.pos, worldMat);
	Out.pos = mul(In.pos, transformMat);
	Out.texUV = In.texUV;

	float3 nor = normalize(In.normal.xyz);
	Out.normal.xyz = mul(nor, (float3x3)worldMat);

	return Out;
}