//==========================
//===【Demo0.cpp】
//==========================
//    タイトル画面の管理を行います。
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
void	OGL::Demo0::Init(void)
{
	ProjectionMatrix prj;
	prj.SetAspect(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	prj.SetClippingPlane(1, 1000);
	prj.SetFovangle(45);

	m_view.SetCenterPos(0, 7, 0);
	m_view.SetRotation(19, 0, 0);
	m_view.SetLength(58);
	
	m_world.SetTransPos(0, 0, 0);
	m_RPLambert.SetProjectionMatrix(&prj);
	m_RPLambert.SetWorldMatrix(&m_world);
	m_modelData.LoadOgmData("model/puronama/puronama.ogm");
	m_stageData.LoadOgmData("model/stage/stage.ogm");
	m_backBuffer.Create();
	m_depthStencilTex.Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DSTEX_FORMAT::DSF_D24S8, false);

	m_pointLight.SetSlotCount(2);
	m_pointLight.SetPos(0, D3DXVECTOR3(0, 0, 0));
	m_pointLight.SetDecrement(0, 1, 2);
	m_pointLight.SetDiffuseCollar(0, D3DXVECTOR4(1, 1, 1, 1));
	m_RPLambert.SetPointLight(&m_pointLight);

	m_rtv.Create(1280, 720, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM);
	
	m_OutLambert.SetTexture(&m_rtv, 0);
	m_OutLambert.SetTexture(&m_depthStencilTex);

	m_InGauss.SetTexture(&m_rtv, 0);

	m_OutBackBuffer.SetTexture(&m_backBuffer, 0);

	m_GaussFilter.SetInputTexture(&m_InGauss);
	m_GaussFilter.SetTexSize(1280, 720);
	m_GaussFilter.SetDivision(0.3);
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの更新を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo0::Update(void)
{

	if (!GetKeyboardPress(DIK_LSHIFT))
	{
		m_view.UpdateDebugCamera();
	}
	else
	{
		if (GetKeyboardPress(DIK_W))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(0, 0.3, 0));
		}
		if (GetKeyboardPress(DIK_S))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(0, -0.3, 0));
		}
		if (GetKeyboardPress(DIK_A))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(-0.3, 0, 0));
		}
		if (GetKeyboardPress(DIK_D))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(0.3, 0, 0));
		}
		
		if (GetKeyboardPress(DIK_Z))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(0, 0, -0.3));
		}
		if (GetKeyboardPress(DIK_X))
		{
			m_pointLight.AddPos(0, D3DXVECTOR3(0, 0, 0.3));
		}
		if (GetKeyboardPress(DIK_R))
		{
			m_pointLight.AddDecrement(0, 0.1, 0);
		}
		if (GetKeyboardPress(DIK_F))
		{
			m_pointLight.AddDecrement(0, -0.1, 0);
		}
		if (GetKeyboardPress(DIK_T))
		{
			m_pointLight.AddDecrement(0, 0, 0.1);
		}
		if (GetKeyboardPress(DIK_G))
		{
			m_pointLight.AddDecrement(0, 0, -0.1);
		}
		static float gaussPrm = 0.3;
		if (GetKeyboardPress(DIK_Y))
		{
			gaussPrm += 0.03;
			m_GaussFilter.SetDivision(gaussPrm);
		}
		if (GetKeyboardPress(DIK_H))
		{
			gaussPrm -= 0.03;
			m_GaussFilter.SetDivision(gaussPrm);
		}
	}
 	if (GetKeyboardTrigger(DIK_SPACE))
	{
		this->nextScene = Demo1::GetInstance();
	}
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの描画を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo0::Draw(void)
{
	m_rtv.Clear(1, 1, 1, 1);	
	m_depthStencilTex.Clear(1, 0);
	m_backBuffer.Clear(0, 0, 1, 1);

	m_RPLambert.SetViewMatrix(&m_view);
	m_RPLambert.SetModelData(&m_stageData);
	m_RPLambert.Draw(&m_OutLambert);
	m_RPLambert.SetModelData(&m_modelData);
	m_RPLambert.Draw(&m_OutLambert);
	m_GaussFilter.Draw(&m_OutBackBuffer);
}

//■■■■■■■■■■■■■■■■■■■■//
//■■■シーンの終了処理を行います。■■■//
//■■■■■■■■■■■■■■■■■■■■//
void	OGL::Demo0::Uninit(void)
{

}