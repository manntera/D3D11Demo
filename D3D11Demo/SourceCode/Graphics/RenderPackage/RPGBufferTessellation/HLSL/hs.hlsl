//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼各種行列▼▼▼*/
cbuffer cbTessPram:register(b1)
{
	float4	tessPram;
};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼ハルIN▼▼▼*/
struct hullIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*▼▼▼ハルパッチ定数OUT▼▼▼*/
struct constHullOut
{
	float edges[4]:SV_TessFactor;
	float inside[2]:SV_InsideTessFactor;
};
/*▼▼▼ハルOUT▼▼▼*/
struct hullOut
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ハルパッチ定数シェーダ▼▼▼*/
constHullOut ConstHS(InputPatch<hullIn, 4> ip, uint PatchID :SV_PrimitiveID)
{
	constHullOut Out;

	Out.edges[0] = Out.edges[1] = Out.edges[2] = Out.edges[3] = tessPram.x;
	Out.inside[0] = Out.inside[1] = tessPram.y;

	return Out;
}
/*▼▼▼ハルシェーダ▼▼▼*/
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstHS")]
hullOut HS(InputPatch<hullIn, 4> In, uint i:SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
	hullOut Out;

	Out.pos = In[i].pos;
	Out.texUV = In[i].texUV;

	return Out;
}