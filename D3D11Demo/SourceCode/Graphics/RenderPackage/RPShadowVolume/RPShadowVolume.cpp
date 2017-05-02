//==========================
//===【RPShadowVolume.cpp】
//==========================
//    シャドウボリューム用いるGBufferの描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPShadowVolume.h"
#include"../../../Window/Window.h"

OGL::RPShadowVolume::RPShadowVolume()
{
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VertexShader vs;
	vs.SetInputLayoutNum(2);
	vs.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.SetInputLayoutData(1, "NORMAL", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);

	vs.CreateShader("SourceCode/Graphics/RenderPackage/RPShadowVolume/HLSL/vs.hlsl", "VS", "vs_5_0");
	m_renderData.SetVertexShader(&vs);

	GeometryShader gs;
	gs.CreateShader("SourceCode/Graphics/RenderPackage/RPShadowVolume/HLSL/gs.hlsl", "GS", "gs_5_0");
	m_renderData.SetGeometryShader(&gs);

	//PixelShader ps;
	//ps.CreateShader("SourceCode/Graphics/RenderPackage/RPShadowVolume/HLSL/ps.hlsl", "PS", "ps_5_0");
	//m_renderData.SetPixelShader(&ps);

	SamplerState ss;
	ss.Create();
	m_renderData.SetPsSamplerState(&ss, 0);

	RasterizerState rs;
	rs.SetCullMode(D3D11_CULL_FRONT);
	rs.Create();
	m_renderData.SetRasterizerState(&rs);

	DepthStencilState dss;
	dss.SetDepthTestEnable(true);
	dss.SetDepthBufferWriteEnable(true);
	dss.SetDepthTestComparisonFunc(D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS);
	dss.SetStencilEnable(true);
	dss.SetStencilReadMask(0xff);
	dss.SetStencilWriteMask(0xff);
	dss.SetFrontFace(D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_INCR, D3D11_COMPARISON_ALWAYS);
	dss.SetBackFace(D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_DECR, D3D11_COMPARISON_ALWAYS);
	dss.Create();
	m_renderData.SetDepthStencilState(&dss);

	BlendState bs;
	bs.Create();
	m_renderData.SetBlendState(&bs);

	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	m_renderData.SetViewPort(&vp);

	m_lightVector.Create(sizeof(D3DXVECTOR4));
	D3DXVECTOR4 temp = D3DXVECTOR4(1, 1, 0, 1);
	D3DXVec4Normalize(&temp, &temp);
	m_lightVector.SetResource(&temp);
}

OGL::RPShadowVolume::~RPShadowVolume()
{
}

bool	OGL::RPShadowVolume::SetProjectionMatrix(ProjectionMatrix*	matObj)
{
	m_transfoam.SetProjectionMatrix(matObj);
	return true;
}
bool	OGL::RPShadowVolume::SetViewMatrix(ViewMatrix*	matObj)
{
	m_transfoam.SetViewMatrix(matObj);
	return true;
}
bool	OGL::RPShadowVolume::SetWorldMatrix(WorldMatrix*	matObj)
{
	m_transfoam.SetWorldMatrix(matObj);
	return true;
}
bool	OGL::RPShadowVolume::SetModelData(ModelData*	modelData)
{
	mp_modelData = modelData;
	return true;
}
bool	OGL::RPShadowVolume::Draw(OutputTexture* tex)
{
	m_transfoam.Update();

	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(m_transfoam.GetConstantBuffer(), 0);
	D3D11RenderManager::SetGsConstantBuffer(&m_lightVector, 1);
	D3D11RenderManager::SetIndexBuffer(&mp_modelData->m_indexBuffer);

	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_posBuffer, 0);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_normalBuffer, 1);

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