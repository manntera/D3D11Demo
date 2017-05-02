//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
struct T_material
{
	float4	diffuse;
	float4	specular;	//wはPower
	float4	ambient;
};
struct T_pointLight
{
	float4	pos;
	float4	diffuseCollar;
	float4	decrement;	//x=減衰開始距離 y=減衰終了距離
};

/*▼▼▼マテリアル▼▼▼*/
cbuffer cbMaterial:register(b1)
{
	T_material material;
};
cbuffer cbPointLight:register(b2)
{
	float4	lightCount;
	T_pointLight light[100];
};

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
	float4	sm			:	SM;
};
struct pixelOut
{
	float4 col		:	SV_TARGET0;
};

//■■■■■■■■■■■■■■■■
//■■■【テクスチャの設定】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼サンプラの設定▼▼▼*/
SamplerState mySampler	:	register(s0);

/*▼▼▼二次元テクスチャの設定▼▼▼*/
Texture2D texDiffuse			:	register(t0);
Texture2D texToon			:	register(t1);
Texture2D texAddSphere	:	register(t2);
Texture2D texMulSphere	:	register(t3);

//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ピクセルシェーダ▼▼▼*/
pixelOut PS(pixelIn In)
{
	pixelOut Out=(pixelOut)0;
	float4	diffuse = 0;
	float lightForce = length(light[0].pos - In.wPos);
	float min_ = min(light[0].decrement.x, lightForce);
	float max_ = max(light[0].decrement.y, lightForce);
	lightForce = lightForce / (min_ - max_) - max_ / (min_ - max_);
	lightForce = saturate(lightForce);
	float3 lVec = normalize(light[0].pos - In.wPos);
	float d = dot(lVec, In.normal);
	d = d*0.5 + 0.5;
	d = d*d;
	float3 lightcol = light[0].diffuseCollar.xyz*lightForce;
	float4 sphereAddCol = texAddSphere.Sample(mySampler, float2((In.sm.x / In.sm.w) + 0.5, (In.sm.y / In.sm.w) + 0.5));
	sphereAddCol.xyz = sphereAddCol.xyz*lightcol.xyz;
	float4 sphereMulCol = texMulSphere.Sample(mySampler, float2((In.sm.x / In.sm.w) + 0.5, (In.sm.y / In.sm.w) + 0.5));
	float4 def = float4(material.diffuse.xyz*texToon.Sample(mySampler, float2(1, 1 - d)).xyz*texDiffuse.Sample(mySampler, In.texUV.xy).xyz, texDiffuse.Sample(mySampler, In.texUV.xy).w);
	Out.col = float4((def.xyz*lightcol) + sphereAddCol.xyz, def.w);
	return Out;
}

//乗算合成する時にしよか