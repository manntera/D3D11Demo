//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yθobt@z‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯eNX`ΜTCY₯₯₯*/
cbuffer cbWindow:register(b0)
{
	float4 texSize : packoffset(c0);	// xcWidth ycHeight zcoffsetX wcoffsetY
};

//‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘y\’ΜιΎz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_IN₯₯₯*/
struct vertexIn
{
	float4	pos		:	POSITION;
	float4	uv			:	TEX_UV;
};
/*₯₯₯Έ_OUT₯₯₯*/
struct vertexOut
{
	float4 pos    : SV_POSITION;
	float4 uv		 : TEX_UV;
	float4 sPos		:sPos;
};
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yVF[_[R[hz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_VF[_₯₯₯*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv = In.uv;
	Out.sPos = In.pos;
	return Out;
}