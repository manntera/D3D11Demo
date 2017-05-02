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
};
/*▼▼▼頂点OUT▼▼▼*/
struct vertexOut
{
	float4	pos			:	SV_POSITION;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = mul(In.pos, transformMat);

	return Out;
}