//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼WINDOWの広さ▼▼▼*/
cbuffer cbWindow:register(b0)
{
	float4 windowScale : packoffset(c0);
};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct vertexIn
{
	float4	rect			:	RECT;
};
/*▼▼▼頂点OUT▼▼▼*/
struct vertexOut
{
	float4	rect			:	RECT;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.rect.x = ((In.rect.x / windowScale.x) - 0.5) * 2;
	Out.rect.y = ((In.rect.y / windowScale.y) - 0.5) * 2;
	Out.rect.z = (In.rect.z / windowScale.x);
	Out.rect.w = (In.rect.w / windowScale.y);
	return Out;
}