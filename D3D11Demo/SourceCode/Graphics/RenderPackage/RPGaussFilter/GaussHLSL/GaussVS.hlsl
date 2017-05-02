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
	float4 uv0 : TEX_UV0;   // テクセル
	float4 uv1 : TEX_UV1;   // テクセル
	float4 uv2 : TEX_UV2;   // テクセル
	float4 uv3 : TEX_UV3;   // テクセル
	float4 uv4 : TEX_UV4;   // テクセル
	float4 uv5 : TEX_UV5;   // テクセル
	float4 uv6 : TEX_UV6;   // テクセル
	float4 uv7 : TEX_UV7;   // テクセル
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS_x(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv0 = In.uv + float4(-1.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv1 = In.uv + float4(-3.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv2 = In.uv + float4(-5.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv3 = In.uv + float4(-7.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv4 = In.uv + float4(-9.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv5 = In.uv + float4(-11.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv6 = In.uv + float4(-13.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv7 = In.uv + float4(-15.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	return Out;
}
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS_y(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv0 = In.uv + float4(0.0f, -1.0f / texSize.y, 0.0f, 0.0f);
	Out.uv1 = In.uv + float4(0.0f, -3.0f / texSize.y, 0.0f, 0.0f);
	Out.uv2 = In.uv + float4(0.0f, -5.0f / texSize.y, 0.0f, 0.0f);
	Out.uv3 = In.uv + float4(0.0f, -7.0f / texSize.y, 0.0f, 0.0f);
	Out.uv4 = In.uv + float4(0.0f, -9.0f / texSize.y, 0.0f, 0.0f);
	Out.uv5 = In.uv + float4(0.0f, -11.0f / texSize.y, 0.0f, 0.0f);
	Out.uv6 = In.uv + float4(0.0f, -13.0f / texSize.y, 0.0f, 0.0f);
	Out.uv7 = In.uv + float4(0.0f, -15.0f / texSize.y, 0.0f, 0.0f);
	return Out;
}