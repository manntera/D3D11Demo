//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yθobt@z‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘

//‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘y\’ΜιΎz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_IN₯₯₯*/
struct vertexIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*₯₯₯Έ_OUT₯₯₯*/
struct vertexOut
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yVF[_[R[hz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_VF[_₯₯₯*/
vertexOut VS(vertexIn In)
{
	vertexOut Out;
	Out.pos = In.pos;
	Out.texUV = In.texUV;

	return Out;
}