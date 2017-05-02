//==========================
//===【RPRect.cpp】
//==========================
//    四角形の描画に必要なデータと機能を管理します。
//    この際、ピクセルシェーダーを外部から指定する事で
//    ポストプロセスの処理に用います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RPRect.h"
#include"../../../Window/Window.h"

OGL::RPRect::RPRect()
{
	VertexShader		vsSprite;
	GeometryShader	gsSprite;

	vsSprite.SetInputLayoutNum(1);
	vsSprite.SetInputLayoutData(0, "RECT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	vsSprite.CreateShader("SourceCode/Graphics/RenderPackage/RPRect/RectHLSL/RectVs.hlsl", "VS", "vs_5_0");
	gsSprite.CreateShader("SourceCode/Graphics/RenderPackage/RPRect/RectHLSL/RectGs.hlsl", "GS", "gs_5_0");

	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_renderData.SetVertexShader(&vsSprite);
	m_renderData.SetGeometryShader(&gsSprite);

	m_rectData.Create(sizeof(D3DXVECTOR4));
	int index[1] = { 0 };
	m_index.Create(1, index);
	D3DXVECTOR4 rect[1] = { { 0, 0, 1, 1 }};
	m_vertex.Create(1, rect,true);
	m_rectData.SetResource(D3DXVECTOR4(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(),1,1 ));
}

OGL::RPRect::~RPRect()
{
}

bool	OGL::RPRect::SetRectSize(float xPos, float yPos, float xLen, float yLen)
{
	ViewPort vp;
	vp.SetDepth(0, 1);
	vp.SetRange(0, 0, xLen, yLen);
	m_renderData.SetViewPort(&vp);
	m_vertex.SetUpdateVertexData(0, D3DXVECTOR4(xPos, yPos, xLen, yLen));
	m_vertex.UpdateBuffer();
	return true;
}
bool	OGL::RPRect::SetInputTexture(InputTexture* tex)
{
	m_inputTex = tex;
	return true;
}
bool	OGL::RPRect::SetSampler(SamplerState* smp, UINT slot)
{
	m_renderData.SetPsSamplerState(smp, slot);
	return true;
}
bool	OGL::RPRect::SetPixelShader(char* fileName)
{
	PixelShader			psSprite;
	psSprite.CreateShader(fileName, "PS", "ps_5_0");
	m_renderData.SetPixelShader(&psSprite);
	return true;
}
bool	OGL::RPRect::SetConstantBuffer(ConstantBuffer* buff, UINT slot)
{
	for (int i = 0; i < m_constantBuffer.size(); i++)
	{
		if (m_constantBuffer[i].slot == slot)
		{
			m_constantBuffer[i].cb = buff;
			return true;
		}
	}
	T_PsConstantBuffer temp;
	temp.cb = buff;
	temp.slot = slot;
	m_constantBuffer.push_back(temp);
	return true;
}
bool	OGL::RPRect::Draw(OutputTexture* tex)
{
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(&m_rectData, 0);
	D3D11RenderManager::SetIndexBuffer(&m_index);
	D3D11RenderManager::SetOutputTexture(tex);
	D3D11RenderManager::SetPsInputTexture(m_inputTex);
	D3D11RenderManager::SetVertexBuffer(&m_vertex, 0);
	for (int i = 0; i < m_constantBuffer.size(); i++)
	{
		D3D11RenderManager::SetPsConstantBuffer(m_constantBuffer[i].cb, m_constantBuffer[i].slot);
	}
	D3D11RenderManager::Draw(1, 0, 0);
	return true;
}