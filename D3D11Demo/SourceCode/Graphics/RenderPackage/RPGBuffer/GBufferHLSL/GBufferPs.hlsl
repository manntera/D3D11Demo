//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼マテリアル▼▼▼*/
cbuffer cbMaterial:register(b1)
{
	float4 matDiffuse;
	float4 matSpecular;	//wはPower
	float4	matAmbient;
};
//cbuffer cbPointLight:register(b2)
//{
//	float4 lightPos;
//	float4 lightDiffuseCollar;
//	float4	lightDecrement;	//x=減衰開始距離 y=減衰終了距離
//};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点OUT▼▼▼*/
struct pixelIn
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
struct pixelOut
{
	float4	albedo				:	SV_TARGET0;	//アルベド色
	float4	normalDepth		:	SV_TARGET1;	//.xyz=法線 .w=深度
	float4	worldPos				:	SV_TARGET2;	//ワールド座標
};

//■■■■■■■■■■■■■■■■
//■■■【テクスチャの設定】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼サンプラの設定▼▼▼*/
SamplerState mySampler	:	register(s0);

/*▼▼▼二次元テクスチャの設定▼▼▼*/
Texture2D texDiffuse			:	register(t0);
//Texture2D texToon			:	register(t1);
//Texture2D texAddSphere	:	register(t2);
//Texture2D texMulSphere	:	register(t3);

//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ピクセルシェーダ▼▼▼*/
pixelOut PS(pixelIn In)
{
	pixelOut Out = (pixelOut)0;
	Out.albedo = texDiffuse.Sample(mySampler, In.texUV.xy)*matDiffuse;

	Out.normalDepth.xyz = (In.normal.xyz + 1) / 2;
	Out.normalDepth.w = In.pos.z / In.pos.w;

	Out.worldPos = In.wPos;
	return Out;
}
