//==========================
//===【Demo2.cpp】
//==========================
//    ゲーム本体画面の管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"../GameSceneList.h"
#include	"../../GameLoopManager/GameLoopManager.h"
#include	"../../../Window/Window.h"

//■■■■■■■■■■■■■■■■■■■//
//■■■シーンの初期化を行います。■■■//
//■■■■■■■■■■■■■■■■■■■//
void	OGL::Demo2::Init(void)
{
	//--------
	// RenderDataの設定
	//--------
	ViewPort				viewPort;
	VertexShader		vsSprite;
	GeometryShader	gsSprite;
	PixelShader			psSprite;
	//ビューポート設定
	viewPort.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	//シェーダー関連設定
	vsSprite.SetInputLayoutNum(2);
	vsSprite.SetInputLayoutData(0, "RECT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	vsSprite.SetInputLayoutData(1, "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	vsSprite.CreateShader("HLSL/vsSprite.hlsl", "VS", "vs_5_0");
	gsSprite.CreateShader("HLSL/gsSprite.hlsl", "GS", "gs_5_0");
	psSprite.CreateShader("HLSL/psSprite.hlsl", "PS", "ps_5_0");
	//RenderDataにセット
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_renderData.SetViewPort(&viewPort);
	m_renderData.SetVertexShader(&vsSprite);
	m_renderData.SetGeometryShader(&gsSprite);
	m_renderData.SetPixelShader(&psSprite);

	//--------
	//コンスタントバッファの設定
	//--------
	m_windowScale.Create(sizeof(D3DXVECTOR4));
	m_windowScale.SetResource(D3DXVECTOR4(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), 0, 0));

	//--------
	//テクスチャの設定
	//--------
	//画像データロード
	m_imageTexture.LoadFile("Resource/image1.png");
	//インプットテクスチャに画像をセット
	m_inputTexture.SetTexture(&m_imageTexture, 0);

	//バックバッファの生成
	m_backBuffer.Create();
	//アウトプットテクスチャにバックバッファを設定
	m_outPutTexture.SetTexture(&m_backBuffer, 0);

	//--------
	//頂点データの設定
	//--------
	//インデックスバッファ生成
	int index[4] = { 0, 1, 2, 3 };
	m_indexBuffer.Create(4, index);
	//頂点バッファ生成
	D3DXVECTOR4 rect[4] = { { 110, 110, 100, 100 }, { 300, 300, 100, 120 }, { 600, 500, 50, 150 }, { 1000, 700, 100, 80 } };
	m_rectBuffer.Create(4, rect);
	D3DXVECTOR4 color[4] = { { 1, 1, 1, 1 }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 } };
	m_colorBuffer.Create(4, color);

	m_rpRect.SetInputTexture(&m_inputTexture);
	m_rpRect.SetPixelShader("HLSL/psSprite.hlsl");
	m_rpRect.SetRectSize(1280/2,720/2, 1280, 720);
	SamplerState ss;
	m_rpRect.SetSampler(&ss, 0);
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの更新を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo2::Update(void)
{
	//バックバッファを緑色に塗り潰す
	m_backBuffer.Clear(0, 1, 0, 1);
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		this->nextScene = Demo3::GetInstance();
	}
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの描画を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo2::Draw(void)
{
	m_rpRect.Draw(&m_outPutTexture);
	//描画情報を詰め込む
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(&m_windowScale,0);
	D3D11RenderManager::SetIndexBuffer(&m_indexBuffer);
	D3D11RenderManager::SetOutputTexture(&m_outPutTexture);
	D3D11RenderManager::SetPsInputTexture(&m_inputTexture);
	D3D11RenderManager::SetVertexBuffer(&m_rectBuffer, 0);
	D3D11RenderManager::SetVertexBuffer(&m_colorBuffer, 1);
	D3D11RenderManager::Draw(4, 0, 0);
}

//■■■■■■■■■■■■■■■■■■■■//
//■■■シーンの終了処理を行います。■■■//
//■■■■■■■■■■■■■■■■■■■■//
void	OGL::Demo2::Uninit(void)
{
	//テクスチャを破棄
//	m_imageTexture.Release();
//	m_backBuffer.Release();
}