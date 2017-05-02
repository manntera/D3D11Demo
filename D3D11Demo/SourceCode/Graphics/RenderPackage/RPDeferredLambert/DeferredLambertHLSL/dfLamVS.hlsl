//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼テクスチャのサイズ▼▼▼*/
cbuffer cbWindow:register(b0)
{
	float4 texSize : packoffset(c0);	// x…Width y…Height z…offsetX w…offsetY
};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct vertexIn
{
	float4	pos		:	POSITION;
	float4	uv			:	TEX_UV;
};
/*▼▼▼頂点OUT▼▼▼*/
struct vertexOut
{
	float4 pos    : SV_POSITION;
	float4 uv		 : TEX_UV;
	float4 sPos		:sPos;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv = In.uv;
	Out.sPos = In.pos;
	return Out;
}