//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
/*▼▼▼ドメインIN▼▼▼*/
struct domainIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*▼▼▼ドメインパッチ定数IN▼▼▼*/
struct constDomainIn
{
	float edges[4]:SV_TessFactor;
	float inside[2]:SV_InsideTessFactor;
};
/*▼▼▼ドメインOUT▼▼▼*/
struct domainOut
{
	float4	pos			:	SV_POSITION;
	float4	texUV			:	TEX_UV;
};

/*▼▼▼サンプラの設定▼▼▼*/
SamplerState mySampler	:	register(s0);

/*▼▼▼二次元テクスチャの設定▼▼▼*/
Texture2D texHeight		:	register(t0);

//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ドメインシェーダ▼▼▼*/
[domain("quad")]
domainOut DS(constDomainIn In, float2 uv:SV_DomainLocation, const OutputPatch<domainIn, 4>patch)
{
	domainOut Out;
	//pos
	float4 p1 = lerp(patch[1].pos, patch[0].pos, uv.x);
	float4 p2 = lerp(patch[3].pos, patch[2].pos, uv.x);
	float4 p3 = lerp(p1, p2, uv.y);

	//uv
	float4 t1 = lerp(patch[1].texUV, patch[0].texUV, uv.x);
	float4 t2 = lerp(patch[3].texUV, patch[2].texUV, uv.x);
	float4 t3 = lerp(t1, t2, uv.y);

	p3.z -= texHeight.Load(int3(int(t3.x * 1023.0f), int(t3.y * 1023.0f), 0)).w * 5;

	Out.pos = p3;
	Out.texUV = t3;
	
	return Out;
}