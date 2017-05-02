//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
struct pixelIn
{
	float4	pos			:	SV_POSITION;
	float2	uv				:	UV;
};
struct pixelOut
{
	float4 col		:	SV_TARGET0;
};

//■■■■■■■■■■■■■■■■
//■■■【テクスチャの設定】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼サンプラの設定▼▼▼*/
SamplerState _sampler	:	register(s0);
/*▼▼▼二次元テクスチャの設定▼▼▼*/
Texture2D tex		:	register(t0);

//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ピクセルシェーダ▼▼▼*/
pixelOut PS(pixelIn In)
{
	pixelOut Out;

	Out.col = tex.Sample(_sampler, In.uv);

	return Out;
}
