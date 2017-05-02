//==========================
//===【RPLambertModel.cpp】
//==========================
//    LambertModel描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPLambertModel.h"
#include"../../../Window/Window.h"

OGL::RPLambertModel::RPLambertModel()
{
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	VertexShader vs;
	vs.SetInputLayoutNum(3);
	vs.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.SetInputLayoutData(1, "NORMAL", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.SetInputLayoutData(2, "TEX_UV", 2, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.CreateShader("SourceCode/Graphics/RenderPackage/RPLambertModel/LambertHLSL/LambertVs.hlsl", "VS", "vs_5_0");
	m_renderData.SetVertexShader(&vs);

	PixelShader ps;
	ps.CreateShader("SourceCode/Graphics/RenderPackage/RPLambertModel/LambertHLSL/LambertPs.hlsl", "PS", "ps_5_0");
	m_renderData.SetPixelShader(&ps);

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
	bs.SetRenderTargetBlendDesc(0, true, D3D11_BLEND_SRC_ALPHA, 
		D3D11_BLEND_INV_SRC_ALPHA, 
		D3D11_BLEND_OP_ADD, 
		D3D11_BLEND_ONE, 
		D3D11_BLEND_ZERO, 
		D3D11_BLEND_OP_ADD, 
		D3D11_COLOR_WRITE_ENABLE_ALL);
	bs.Create();
	m_renderData.SetBlendState(&bs);

	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	m_renderData.SetViewPort(&vp);
}

OGL::RPLambertModel::~RPLambertModel()
{
}

bool	OGL::RPLambertModel::SetProjectionMatrix(ProjectionMatrix*	matObj)
{
	m_transfoam.SetProjectionMatrix(matObj);
	return true;
}
bool	OGL::RPLambertModel::SetViewMatrix(ViewMatrix*	matObj)
{
	m_transfoam.SetViewMatrix(matObj);
	return true;
}
bool	OGL::RPLambertModel::SetWorldMatrix(WorldMatrix*	matObj)
{
	m_transfoam.SetWorldMatrix(matObj);
	return true;
}
bool	OGL::RPLambertModel::SetPointLight(CBPPointLight* data)
{
	mp_pointLight = data;
	return true;
}
bool	OGL::RPLambertModel::SetModelData(ModelData*		modelData)
{
	mp_modelData = modelData;
	return true;
}
bool	OGL::RPLambertModel::Draw(OutputTexture* tex)
{
	m_transfoam.Update();
	mp_pointLight->Update();
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(m_transfoam.GetConstantBuffer(), 0);
	D3D11RenderManager::SetPsConstantBuffer(mp_pointLight->GetConstantBuffer(), 2);
	D3D11RenderManager::SetIndexBuffer(&mp_modelData->m_indexBuffer);
	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_posBuffer,0);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_normalBuffer,1);
	D3D11RenderManager::SetVertexBuffer(&mp_modelData->m_uvBuffer,2);

	int indexTemp = 0;
	InputTexture inTex;
	for (int i = 0; i < mp_modelData->m_materialRefVertexIndexCount.size(); i++)
	{
		inTex.SetTexture(&mp_modelData->m_imageTexture[mp_modelData->m_textureIndex[i].diffuse], 0);
		inTex.SetTexture(&mp_modelData->m_imageTexture[mp_modelData->m_textureIndex[i].toon], 1);
		inTex.SetTexture(&mp_modelData->m_imageTexture[mp_modelData->m_textureIndex[i].addSphere], 2);
		inTex.SetTexture(&mp_modelData->m_imageTexture[mp_modelData->m_textureIndex[i].mulSphere], 3);
		D3D11RenderManager::SetPsInputTexture(&inTex);
		D3D11RenderManager::SetPsConstantBuffer(&mp_modelData->m_materialData[i], 1);
		D3D11RenderManager::Draw(mp_modelData->m_materialRefVertexIndexCount[i], indexTemp, 0);
		indexTemp += mp_modelData->m_materialRefVertexIndexCount[i];
	}
	D3D11RenderManager::ClearOutputTexture(tex);
	return true;
}