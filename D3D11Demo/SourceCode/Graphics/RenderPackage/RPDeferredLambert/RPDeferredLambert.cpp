//==========================
//===【RPDeferredLambert.cpp】
//==========================
//    ディファードレンダリングによるGBufferの描画に必要なデータと機能を管理します。
//    ランバートモデルの描画に必要なデータと機能を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPDeferredLambert.h"
#include"../../../Window/Window.h"

OGL::RPDeferredLambert::RPDeferredLambert()
{
	VertexShader	vs;
	PixelShader		ps;
	vs.SetInputLayoutNum(2);
	vs.SetInputLayoutData(0, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.SetInputLayoutData(1, "TEX_UV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
	vs.CreateShader("SourceCode/Graphics/RenderPackage/RPDeferredLambert/DeferredLambertHLSL/dfLamVS.hlsl", "VS", "vs_5_0");
	ps.CreateShader("SourceCode/Graphics/RenderPackage/RPDeferredLambert/DeferredLambertHLSL/dfLamPS.hlsl", "PS", "ps_5_0");

	SamplerState ss;
	ss.Create();

	RasterizerState rs;
	rs.Create();

	DepthStencilState dss;
	dss.SetDepthTestEnable(false);
	dss.SetStencilEnable(false);
	dss.Create();

	BlendState bs;
	bs.SetRenderTargetBlendDesc(0, true, D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL);
	bs.Create();

	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());

	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_renderData.SetPsSamplerState(&ss, 0);
	m_renderData.SetRasterizerState(&rs);
	m_renderData.SetDepthStencilState(&dss);
	m_renderData.SetBlendState(&bs);
	m_renderData.SetViewPort(&vp);
	m_renderData.SetVertexShader(&vs);
	m_renderData.SetPixelShader(&ps);

	int idx[4] = { 0, 1, 2, 3 };
	m_indexBuff.Create(4, idx);
	D3DXVECTOR4 pos[4] = { { -1, -1, 1, 1 }, { -1, 1, 1, 1 }, { 1, -1, 1, 1 }, { 1, 1, 1, 1 } };
	m_posBuff.Create(4, pos);
	D3DXVECTOR4 uv[4] = { { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 1, 0, 0, 0 } };
	m_uvBuff.Create(4, uv);
}

OGL::RPDeferredLambert::~RPDeferredLambert()
{
}

void	OGL::RPDeferredLambert::SetPointLight(CBPPointLight* light)
{
	m_pointLight = light;
}
void	OGL::RPDeferredLambert::SetSpotLight(CBPSpotLight* light)
{
	m_spotLight = light;
}
void	OGL::RPDeferredLambert::SetProjectionMatrix(ProjectionMatrix* mat)
{
	m_matrix.SetProjectionMatrix(mat);
}
void	OGL::RPDeferredLambert::SetViewMatrix(ViewMatrix* mat)
{
	m_matrix.SetViewMatrix(mat);
}
void	OGL::RPDeferredLambert::SetInputTexture(InputTexture* tex)
{
	m_inputTex = tex;
}
void	OGL::RPDeferredLambert::Draw(OutputTexture* tex)
{
	m_matrix.Update();

	D3D11RenderManager::SetPsConstantBuffer(m_matrix.GetConstantBuffer(), 1);
	D3D11RenderManager::SetPsConstantBuffer(m_pointLight->GetConstantBuffer(), 2);
//	D3D11RenderManager::SetPsConstantBuffer(m_spotLight->GetConstantBuffer(), 3);
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetIndexBuffer(&m_indexBuff);
	D3D11RenderManager::SetVertexBuffer(&m_posBuff, 0);
	D3D11RenderManager::SetVertexBuffer(&m_uvBuff, 1);
	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetPsInputTexture(m_inputTex);
	D3D11RenderManager::Draw(4, 0, 0);
	D3D11RenderManager::ClearPsInputTexture(m_inputTex);
	D3D11RenderManager::ClearOutputTexture(tex);
}