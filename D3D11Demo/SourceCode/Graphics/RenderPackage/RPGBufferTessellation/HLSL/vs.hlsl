//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct vertexIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*▼▼▼頂点OUT▼▼▼*/
struct vertexOut
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS(vertexIn In)
{
	vertexOut Out;
	Out.pos = In.pos;
	Out.texUV = In.texUV;

	return Out;
}