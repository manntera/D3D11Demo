//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yθobt@z‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯}eA₯₯₯*/
cbuffer cbMaterial:register(b1)
{
	float4 matDiffuse;
	float4 matSpecular;	//wΝPower
	float4	matAmbient;
};
//cbuffer cbPointLight:register(b2)
//{
//	float4 lightPos;
//	float4 lightDiffuseCollar;
//	float4	lightDecrement;	//x=ΈJn£ y=ΈIΉ£
//};

//‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘y\’ΜιΎz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_OUT₯₯₯*/
struct pixelIn
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
struct pixelOut
{
	float4	albedo				:	SV_TARGET0;	//AxhF
	float4	normalDepth		:	SV_TARGET1;	//.xyz=@ό .w=[x
	float4	worldPos				:	SV_TARGET2;	//[hΐW
};

//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yeNX`Μέθz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯TvΜέθ₯₯₯*/
SamplerState mySampler	:	register(s0);

/*₯₯₯ρ³eNX`Μέθ₯₯₯*/
Texture2D texDiffuse			:	register(t0);
//Texture2D texToon			:	register(t1);
//Texture2D texAddSphere	:	register(t2);
//Texture2D texMulSphere	:	register(t3);

//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yVF[_[R[hz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯sNZVF[_₯₯₯*/
pixelOut PS(pixelIn In)
{
	pixelOut Out = (pixelOut)0;
	Out.albedo = texDiffuse.Sample(mySampler, In.texUV.xy)*matDiffuse;

	Out.normalDepth.xyz = (In.normal.xyz + 1) / 2;
	Out.normalDepth.w = In.pos.z / In.pos.w;

	Out.worldPos = In.wPos;
	return Out;
}
