//==========================
//===【RPGaussFilter.cpp】
//==========================
//    ガウスフィルター描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPGaussFilter.h"

OGL::RPGaussFilter::RPGaussFilter()
{
	vsX.SetInputLayoutNum(2);
	vsX.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vsX.SetInputLayoutData(1, "TEX_UV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vsX.CreateShader("SourceCode/Graphics/RenderPackage/RPGaussFilter/GaussHLSL/GaussVS.hlsl", "VS_x", "vs_5_0");
	psX.CreateShader("SourceCode/Graphics/RenderPackage/RPGaussFilter/GaussHLSL/GaussPS.hlsl", "PS_x", "ps_5_0");
	
	vsY.SetInputLayoutNum(2);
	vsY.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vsY.SetInputLayoutData(1, "TEX_UV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vsY.CreateShader("SourceCode/Graphics/RenderPackage/RPGaussFilter/GaussHLSL/GaussVS.hlsl", "VS_y", "vs_5_0");
	psY.CreateShader("SourceCode/Graphics/RenderPackage/RPGaussFilter/GaussHLSL/GaussPS.hlsl", "PS_y", "ps_5_0");

	SamplerState ss;
	ss.SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	ss.SetAddresMode(D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP);
	ss.SetMipLODBias(0);
	ss.SetMaxAnisotropy(1);
	ss.SetComparisonFunc(D3D11_COMPARISON_ALWAYS);
	ss.SetBorderColor(0, 0, 0, 0);
	ss.SetLOD(0, D3D11_FLOAT32_MAX);
	ss.Create();

	RasterizerState rs;
	rs.Create();

	DepthStencilState dss;
	dss.Create();

	BlendState bs;
	//bs.SetRenderTargetBlendDesc(0, true, D3D11_BLEND_SRC_ALPHA,
	//	D3D11_BLEND_INV_SRC_ALPHA,
	//	D3D11_BLEND_OP_ADD,
	//	D3D11_BLEND_ONE,
	//	D3D11_BLEND_ZERO,
	//	D3D11_BLEND_OP_ADD,
	//	D3D11_COLOR_WRITE_ENABLE_ALL);
	bs.Create();

	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_renderData.SetPsSamplerState(&ss, 0);
	m_renderData.SetRasterizerState(&rs);
	m_renderData.SetDepthStencilState(&dss);
	m_renderData.SetBlendState(&bs);

	int idx[4] = { 0, 1, 2, 3 };
	m_indexBuff.Create(4, idx);
	D3DXVECTOR4 pos[4] = { { -1, -1, 1, 1 }, { -1, 1, 1, 1 }, { 1, -1, 1, 1 }, { 1, 1, 1, 1 } };
	m_posBuff.Create(4, pos);
	D3DXVECTOR4 uv[4] = { { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 1, 0, 0, 0 } };
	m_uvBuff.Create(4, uv);
	m_weight.Create(sizeof(T_GaussConstant));
	m_texSize.Create(sizeof(T_TexSize));
}

OGL::RPGaussFilter::~RPGaussFilter()
{
}

bool	OGL::RPGaussFilter::SetDivision(float Dispersion)
{
	float temp[8];
	T_GaussConstant cbTemp;
	float total = 0.0f;

	for (int i = 0; i < 8; i++)
	{
		float pos = (float)i * 2.0f;
		temp[i] = expf(-pos * pos * Dispersion);
		total += temp[i];
	}
	for (int i = 0; i < 8; i++)
	{
		temp[i] = temp[i] / total * 0.5f;
	}
	cbTemp.weight1.x = temp[0];
	cbTemp.weight1.y = temp[1];
	cbTemp.weight1.z = temp[2];
	cbTemp.weight1.w = temp[3];
	cbTemp.weight2.x = temp[4];
	cbTemp.weight2.y = temp[5];
	cbTemp.weight2.z = temp[6];
	cbTemp.weight2.w = temp[7];
	m_weight.SetResource(&temp);

	return true;
}

bool	OGL::RPGaussFilter::SetTexSize(float width,float height)
{
	T_TexSize temp;
	temp.texSize.x = width;
	temp.texSize.y = height;
	temp.texSize.z = 16.0f / width;
	temp.texSize.w = 16.0f / height;

	m_texSize.SetResource(&temp);

	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, width, height);
	m_renderData.SetViewPort(&vp);

	return true;
}
bool	OGL::RPGaussFilter::SetInputTexture(InputTexture* tex)
{
	m_inputTex = tex;
	return true;
}
bool	OGL::RPGaussFilter::Draw(OutputTexture* tex)
{
	m_renderData.SetVertexShader(&vsX);
	m_renderData.SetPixelShader(&psX);
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetIndexBuffer(&m_indexBuff);
	D3D11RenderManager::SetVertexBuffer(&m_posBuff, 0);
	D3D11RenderManager::SetVertexBuffer(&m_uvBuff, 1);
	D3D11RenderManager::SetVsConstantBuffer(&m_texSize, 0);
	D3D11RenderManager::SetPsConstantBuffer(&m_texSize, 0);
	D3D11RenderManager::SetPsConstantBuffer(&m_weight, 1);
	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetPsInputTexture(m_inputTex);
	D3D11RenderManager::Draw(4, 0, 0);
	m_renderData.SetVertexShader(&vsY);
	m_renderData.SetPixelShader(&psY);
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::Draw(4, 0, 0);
	D3D11RenderManager::ClearOutputTexture(tex);
	D3D11RenderManager::ClearPsInputTexture(m_inputTex);
	return true;
}