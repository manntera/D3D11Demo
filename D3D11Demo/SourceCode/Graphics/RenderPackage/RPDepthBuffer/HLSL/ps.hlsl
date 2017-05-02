//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■


//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼ピクセルOUT▼▼▼*/
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

//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼ピクセルシェーダ▼▼▼*/
pixelOut PS(pixelIn In)
{
	pixelOut Out = (pixelOut)0;

	Out.albedo = float4(1, 1, 1, 1);

	Out.normalDepth.xyz = (In.normal.xyz) / 2;
	Out.normalDepth.w = In.pos.z / In.pos.w;

	Out.worldPos = In.wPos;
	return Out;
}
