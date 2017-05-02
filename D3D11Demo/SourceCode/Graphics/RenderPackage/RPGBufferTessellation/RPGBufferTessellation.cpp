//==========================
//===【RPGBufferTessellation.cpp】
//==========================
//    ディファードレンダリングに用いるGBufferの描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPGBufferTessellation.h"
#include"../../../Window/Window.h"

OGL::RPGBufferTessellation::RPGBufferTessellation()
{
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	VertexShader vs;
	vs.SetInputLayoutNum(2);
	vs.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.SetInputLayoutData(1, "TEX_UV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.CreateShader("SourceCode/Graphics/RenderPackage/RPGBufferTessellation/HLSL/vs.hlsl", "VS", "vs_5_0");
	m_renderData.SetVertexShader(&vs);

	HullShader hs;
	hs.CreateShader("SourceCode/Graphics/RenderPackage/RPGBufferTessellation/HLSL/hs.hlsl", "HS", "hs_5_0");
	m_renderData.SetHullShader(&hs);

	DomainShader ds;
	ds.CreateShader("SourceCode/Graphics/RenderPackage/RPGBufferTessellation/HLSL/ds.hlsl", "DS", "ds_5_0");
	m_renderData.SetDomainShader(&ds);

	GeometryShader gs;
	gs.CreateShader("SourceCode/Graphics/RenderPackage/RPGBufferTessellation/HLSL/gs.hlsl", "GS", "gs_5_0");
	m_renderData.SetGeometryShader(&gs);

	PixelShader ps;
	ps.CreateShader("SourceCode/Graphics/RenderPackage/RPGBufferTessellation/HLSL/ps.hlsl", "PS", "ps_5_0");
	m_renderData.SetPixelShader(&ps);

	SamplerState ss;
	ss.Create();
	m_renderData.SetPsSamplerState(&ss, 0);

	RasterizerState rs;
	rs.SetCullMode(D3D11_CULL_NONE);
//	rs.SetWireFrameEnable(true);
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
	bs.SetRenderTargetBlendDesc(1, false, D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL);
	bs.SetRenderTargetBlendDesc(2, false, D3D11_BLEND_SRC_ALPHA,
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

	D3DXVECTOR4 tessParm;
	tessParm.x = 1000.0f;
	tessParm.y = 1000.0f;
	tessParm.z = 0.0f;
	tessParm.w = 0.0f;
	m_TessParmBuff.Create(sizeof(D3DXVECTOR4));
	m_TessParmBuff.SetResource(tessParm);

	int index[] = { 0, 1, 2, 3 };
	D3DXVECTOR4 pos[] = {
		D3DXVECTOR4(10, 10, 0, 1),
		D3DXVECTOR4(-10, 10, 0, 1),
		D3DXVECTOR4(10, -10, 0, 1),
		D3DXVECTOR4(-10, -10, 0, 1)
	};
	D3DXVECTOR4 uv[] = {
		D3DXVECTOR4(1, 0, 0, 0),
		D3DXVECTOR4(-0, 0, 0, 0),
		D3DXVECTOR4(1, 1, 0, 0),
		D3DXVECTOR4(0, 1, 0, 0) 
	};
	m_indexBuffer.Create(4,index);
	m_posBuffer.Create(4,pos);
	m_uvBuffer.Create(4,uv);

	m_mapTex.LoadFile("Resource/manntera.png");
	m_inputTex.SetTexture(&m_mapTex, 0);
}

OGL::RPGBufferTessellation::~RPGBufferTessellation()
{
}

bool	OGL::RPGBufferTessellation::SetProjectionMatrix(ProjectionMatrix*	matObj)
{
	m_transfoam.SetProjectionMatrix(matObj);
	return true;
}
bool	OGL::RPGBufferTessellation::SetViewMatrix(ViewMatrix*	matObj)
{
	m_transfoam.SetViewMatrix(matObj);
	return true;
}
bool	OGL::RPGBufferTessellation::SetWorldMatrix(WorldMatrix*	matObj)
{
	m_transfoam.SetWorldMatrix(matObj);
	return true;
}
//bool	OGL::RPGBufferTessellation::SetModelData(ModelData*		modelData)
//{
//	mp_modelData = modelData;
//	return true;
//}
bool	OGL::RPGBufferTessellation::Draw(OutputTexture* tex)
{
	m_transfoam.Update();

	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetGsConstantBuffer(m_transfoam.GetConstantBuffer(), 0);
	D3D11RenderManager::SetHsConstantBuffer(&m_TessParmBuff, 1);
	D3D11RenderManager::SetIndexBuffer(&m_indexBuffer);
	D3D11RenderManager::SetDsInputTexture(&m_inputTex);
	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetVertexBuffer(&m_posBuffer, 0);
	D3D11RenderManager::SetVertexBuffer(&m_uvBuffer, 1);

	//int indexTemp = 0;
	//InputTexture inTex;
	//for (int i = 0; i < mp_modelData->m_materialRefVertexIndexCount.size(); i++)
	//{
	//	inTex.SetTexture(&mp_modelData->m_imageTexture[mp_modelData->m_textureIndex[i].diffuse], 0);
	//	D3D11RenderManager::SetPsInputTexture(&inTex);
	//	D3D11RenderManager::SetPsConstantBuffer(&mp_modelData->m_materialData[i], 1);
	//	D3D11RenderManager::Draw(mp_modelData->m_materialRefVertexIndexCount[i], indexTemp, 0);
	//	indexTemp += mp_modelData->m_materialRefVertexIndexCount[i];
	//}
	
	//D3D11RenderManager::SetPsInputTexture(&inTex);
	D3D11RenderManager::Draw(4, 0, 0);
	D3D11RenderManager::ClearOutputTexture(tex);
	D3D11RenderManager::ClearDsInputTexture(&m_inputTex);
	return true;
}