//==========================
//===【RPShadowVolume.cpp】
//==========================
//    シャドウボリューム用いるGBufferの描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"RPDepthBuffer.h"
#include"../../../Window/Window.h"

OGL::RPDepthBuffer::RPDepthBuffer()
{
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VertexShader vs;
	vs.SetInputLayoutNum(1);
	vs.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

	vs.CreateShader("SourceCode/Graphics/RenderPackage/RPDepthBuffer/HLSL/vs.hlsl", "VS", "vs_5_0");
	m_renderData.SetVertexShader(&vs);

//	PixelShader ps;
//	ps.CreateShader("SourceCode/Graphics/RenderPackage/RPDepthBuffer/HLSL/ps.hlsl", "PS", "ps_5_0");
//	m_renderData.SetPixelShader(&ps);

	SamplerState ss;
	ss.Create();
	m_renderData.SetPsSamplerState(&ss, 0);

	RasterizerState rs;
	rs.SetCullMode(D3D11_CULL_NONE);
	rs.Create();
	m_renderData.SetRasterizerState(&rs);

	DepthStencilState dss;
	dss.Create();
	m_renderData.SetDepthStencilState(&dss);

	BlendState bs;
	bs.Create();
	m_renderData.SetBlendState(&bs);

	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	m_renderData.SetViewPort(&vp);
}

OGL::RPDepthBuffer::~RPDepthBuffer()
{
}

bool	OGL::RPDepthBuffer::SetMapSize(float size)
{
	m_mapSize = size;
	return true;
}
bool	OGL::RPDepthBuffer::SetViewMatrix(ViewMatrix*	matObj)
{
	m_transfoam.SetViewMatrix(matObj);
	return true;
}
bool	OGL::RPDepthBuffer::SetWorldMatrix(WorldMatrix*	matObj)
{
	m_transfoam.SetWorldMatrix(matObj);
	return true;
}
bool	OGL::RPDepthBuffer::SetModelData(ModelData*	modelData)
{
	mp_modelData = modelData;
	return true;
}
bool	OGL::RPDepthBuffer::Draw(OutputTexture* tex, float texXsize, float texYsize)
{
	m_proj.SetPerspectiveEnable(false);
	m_proj.SetAspect(texXsize / m_mapSize, texYsize / m_mapSize);
	m_proj.SetClippingPlane(1, 1000);
	m_transfoam.SetProjectionMatrix(&m_proj);
	m_transfoam.Update();

	ViewPort vp;
	vp.SetDepth(1, 1000);
	vp.SetRange(0, 0, texXsize, texYsize);
	m_renderData.SetViewPort(&vp);

	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(m_transfoam.GetConstantBuffer(), 0);
	D3D11RenderManager::SetIndexBuffer(&mp_modelData->m_indexBuffer);

	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_posBuffer, 0);

	int indexTemp = 0;
	InputTexture inTex;
	for (int i = 0; i < mp_modelData->m_materialRefVertexIndexCount.size(); i++)
	{
		D3D11RenderManager::Draw(mp_modelData->m_materialRefVertexIndexCount[i], indexTemp, 0);
		indexTemp += mp_modelData->m_materialRefVertexIndexCount[i];
	}
	D3D11RenderManager::ClearOutputTexture(tex);
	return true;
}