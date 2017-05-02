//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼テクスチャのサイズ▼▼▼*/
cbuffer cbWindow:register(b0)
{
	float4 texSize : packoffset(c0);	// x…Width y…Height z…offsetX w…offsetY
};
cbuffer cbWeight:register(b1)
{
	float4	weight1;
	float4	weight2;
};
//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct PixelIn
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
/*▼▼▼頂点OUT▼▼▼*/
struct PixelOut
{
	float4	col		:		SV_TARGET0;
};

//■■■■■■■■■■■■■■■■
//■■■【テクスチャの設定】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼サンプラの設定▼▼▼*/
SamplerState mySampler	:	register(s0);

/*▼▼▼二次元テクスチャの設定▼▼▼*/
Texture2D tex			:	register(t0);
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
PixelOut PS_x(PixelIn In)
{
	PixelOut Out = (PixelOut)0;
	Out.col += (tex.Sample(mySampler, In.uv0) + tex.Sample(mySampler, float2(In.uv7.x + texSize.z, In.uv7.y))) * weight1.x;
	Out.col += (tex.Sample(mySampler, In.uv1) + tex.Sample(mySampler, float2(In.uv6.x + texSize.z, In.uv6.y))) * weight1.y;
	Out.col += (tex.Sample(mySampler, In.uv2) + tex.Sample(mySampler, float2(In.uv5.x + texSize.z, In.uv5.y))) * weight1.z;
	Out.col += (tex.Sample(mySampler, In.uv3) + tex.Sample(mySampler, float2(In.uv4.x + texSize.z, In.uv4.y))) * weight1.w;
	Out.col += (tex.Sample(mySampler, In.uv4) + tex.Sample(mySampler, float2(In.uv3.x + texSize.z, In.uv3.y))) * weight2.x;
	Out.col += (tex.Sample(mySampler, In.uv5) + tex.Sample(mySampler, float2(In.uv2.x + texSize.z, In.uv2.y))) * weight2.y;
	Out.col += (tex.Sample(mySampler, In.uv6) + tex.Sample(mySampler, float2(In.uv1.x + texSize.z, In.uv1.y))) * weight2.z;
	Out.col += (tex.Sample(mySampler, In.uv7) + tex.Sample(mySampler, float2(In.uv0.x + texSize.z, In.uv0.y))) * weight2.w;
	return Out;
}
PixelOut PS_y(PixelIn In)
{
	PixelOut Out = (PixelOut)0;
	Out.col += (tex.Sample(mySampler, In.uv0) + tex.Sample(mySampler, float2(In.uv7.x, In.uv7.y + texSize.w))) * weight1.x;
	Out.col += (tex.Sample(mySampler, In.uv1) + tex.Sample(mySampler, float2(In.uv6.x, In.uv6.y + texSize.w))) * weight1.y;
	Out.col += (tex.Sample(mySampler, In.uv2) + tex.Sample(mySampler, float2(In.uv5.x, In.uv5.y + texSize.w))) * weight1.z;
	Out.col += (tex.Sample(mySampler, In.uv3) + tex.Sample(mySampler, float2(In.uv4.x, In.uv4.y + texSize.w))) * weight1.w;
	Out.col += (tex.Sample(mySampler, In.uv4) + tex.Sample(mySampler, float2(In.uv3.x, In.uv3.y + texSize.w))) * weight2.x;
	Out.col += (tex.Sample(mySampler, In.uv5) + tex.Sample(mySampler, float2(In.uv2.x, In.uv2.y + texSize.w))) * weight2.y;
	Out.col += (tex.Sample(mySampler, In.uv6) + tex.Sample(mySampler, float2(In.uv1.x, In.uv1.y + texSize.w))) * weight2.z;
	Out.col += (tex.Sample(mySampler, In.uv7) + tex.Sample(mySampler, float2(In.uv0.x, In.uv0.y + texSize.w))) * weight2.w;
	return Out;
}