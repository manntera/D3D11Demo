//==========================
//===【Demo1.cpp】
//==========================
//    タイトル画面の管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"../GameSceneList.h"
#include	"../../GameLoopManager/GameLoopManager.h"
#include	"../../../Window/Window.h"

#include <random>

//■■■■■■■■■■■■■■■■■■■//
//■■■シーンの初期化を行います。■■■//
//■■■■■■■■■■■■■■■■■■■//
void	OGL::Demo1::Init(void)
{
	//---行列生成
	ProjectionMatrix prj;
	prj.SetAspect(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	prj.SetClippingPlane(1, 1000);
	prj.SetFovangle(45);

	m_view.SetCenterPos(0, 7, 0);
	m_view.SetRotation(19, 0, 0);
	m_view.SetLength(58);
	
	m_world.SetTransPos(0, 0, 0);
	//---リソースロード
	m_modelData.LoadOgmData("model/puronama/puronama.ogm");
	m_stageData.LoadOgmData("model/stage/stage.ogm");
	//---テクスチャ生成
	m_backBuffer.Create();
	m_depthStencilTex.Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DSTEX_FORMAT::DSF_D24S8, false);
	for (int i = 0; i < 2; i++)
	{
		m_gBufferTex[i].Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM);
	}
	m_gBufferTex[2].Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_shadowDepthTex.Create(1024, 1024, DSF_D32, true);
	//---テクスチャ設定
	for (int i = 0; i < 3; i++)
	{
		m_outGBuffer.SetTexture(&m_gBufferTex[i], i);
		m_inDefLam.SetTexture(&m_gBufferTex[i], i);
	}
	m_outGBuffer.SetTexture(&m_depthStencilTex);
	m_outBackBuffer.SetTexture(&m_backBuffer, 0);
	m_shadowOutTex.SetTexture(&m_shadowDepthTex);
	//---ライトのセッティング
	const float posRange = 70.0;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colL(0.0, 1.0);
	std::uniform_real_distribution<float> posXZL(-posRange, posRange);
	std::uniform_real_distribution<float> posYL(0, posRange);
	std::uniform_real_distribution<float> decMinL(0.1, 20.0);
	std::uniform_real_distribution<float> decMaxL(20.0, 50.0);
	std::uniform_real_distribution<float> spotRange(0, 1);
	std::uniform_real_distribution<float> spotLength(1, 30);
	std::uniform_real_distribution<float> spotRot(0, 360);
	m_pointLight.SetSlotCount(MAX_POINT_LIGHT_COUNT);
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; i++)
	{
//		m_pointLight.SetPos(i, D3DXVECTOR3(posXZL(mt), posYL(mt), posXZL(mt)));
		m_pointLight.SetPos(i, D3DXVECTOR3(((i % 10) * 20) - 100, 5, ((i / 10) * 20) - 30));
		m_pointLight.SetDecrement(i, decMinL(mt), decMaxL(mt));
		m_pointLight.SetDiffuseCollar(i, D3DXVECTOR4(colL(mt), colL(mt), colL(mt), colL(mt)));
	}

	m_spotLight.SetSlotCount(MAX_SPOT_LIGHT_COUNT);		//MAX_SPOT_LIGHT_COUNT
	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; i++)
	{
		m_spotLight.GetTransform(i)->SetTransPos(((i % 10) * 20) - 100, 5, ((i / 10) * 20) - 40);
	//	m_spotLight.GetTransform(i)->SetTransPos(10,10, 20);
		m_spotLight.GetTransform(i)->SetRotationDegree(spotRot(mt), spotRot(mt), spotRot(mt));
	//	m_spotLight.GetTransform(i)->SetRotationDegree(-90, 0, 0);
		m_spotLight.SetRange(i, spotRange(mt));
//		m_spotLight.SetRange(i, 0.9);
		m_spotLight.SetDecrement(i, decMinL(mt), decMaxL(mt));
		m_spotLight.SetDiffuseCollar(i, D3DXVECTOR4(colL(mt), colL(mt), colL(mt), colL(mt)));
	//	m_spotLight.SetDiffuseCollar(i, D3DXVECTOR4(1,1,1,1));
	}
	//ビュー追従光源
	//D3DXMATRIX tempV;
	//D3DXMatrixInverse(&tempV, nullptr, m_view.Getmatrix());
	//m_pointLight.SetPos(0, D3DXVECTOR3(tempV._41, tempV._42, tempV._43));
	//m_pointLight.SetDecrement(0, 10,1000 );
	//m_pointLight.SetDiffuseCollar(0, D3DXVECTOR4(1,1,1,1));

	//---RenderPackageにセッティング
	//GBufferの設定
	m_gBuffer.SetProjectionMatrix(&prj);
	m_gBuffer.SetWorldMatrix(&m_world);
	//DeferredLambertの設定
	m_defLam.SetProjectionMatrix(&prj);
	m_defLam.SetInputTexture(&m_inDefLam);
	m_defLam.SetPointLight(&m_pointLight);
	m_defLam.SetSpotLight(&m_spotLight);

	m_RPshadow.SetMapSize(20);
	m_shadowViewMat.SetCenterPos(0, 0, 0);
	m_shadowViewMat.SetLength(30);
	m_shadowViewMat.SetRotation(30, 20, 10);
	m_RPshadow.SetWorldMatrix(&m_world);
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの更新を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo1::Update(void)
{

	if (!GetKeyboardPress(DIK_LSHIFT))
	{
		m_view.UpdateDebugCamera();
	}
	else
	{
		if (GetKeyboardPress(DIK_W))
		{
			m_spotLight.GetTransform(0)->AddTransVector(0, 0.3, 0);
		//	m_spotLight.AddPos(0, D3DXVECTOR3(0, 0.3, 0));
		}
		if (GetKeyboardPress(DIK_S))
		{
			m_spotLight.GetTransform(0)->AddTransVector(0, -0.3, 0);
		//	m_spotLight.AddPos(0, D3DXVECTOR3(0, -0.3, 0));
		}
		if (GetKeyboardPress(DIK_A))
		{
			m_spotLight.GetTransform(0)->AddTransVector(-0.3, 0, 0);
//			m_spotLight.AddPos(0, D3DXVECTOR3(-0.3, 0, 0));
		}
		if (GetKeyboardPress(DIK_D))
		{
			m_spotLight.GetTransform(0)->AddTransVector(0.3, 0, 0);
//			m_spotLight.AddPos(0, D3DXVECTOR3(0.3, 0, 0));
		}
		
		if (GetKeyboardPress(DIK_Z))
		{
			m_spotLight.GetTransform(0)->AddTransVector(0, 0,-0.3);
//			m_spotLight.AddPos(0, D3DXVECTOR3(0, 0, -0.3));
		}
		if (GetKeyboardPress(DIK_X))
		{
			m_spotLight.GetTransform(0)->AddTransVector(0, 0, 0.3);
//			m_spotLight.AddPos(0, D3DXVECTOR3(0, 0, 0.3));
		}
		if (GetKeyboardPress(DIK_R))
		{
			m_spotLight.AddDecrement(0, 0.1, 0);
		}
		if (GetKeyboardPress(DIK_F))
		{
			m_spotLight.AddDecrement(0, -0.1, 0);
		}
		if (GetKeyboardPress(DIK_T))
		{
			m_spotLight.AddDecrement(0, 0, 0.1);
		}
		if (GetKeyboardPress(DIK_G))
		{
			m_spotLight.AddDecrement(0, 0, -0.1);
		}
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		this->nextScene = Demo2::GetInstance();
	}
	D3DXMATRIX tempV;
	D3DXMatrixInverse(&tempV, nullptr, m_view.Getmatrix());
	m_pointLight.SetPos(0, D3DXVECTOR3(tempV._41, tempV._42, tempV._43));
}

//■■■■■■■■■■■■■■■■■■//
//■■■シーンの描画を行います。■■■//
//■■■■■■■■■■■■■■■■■■//
void	OGL::Demo1::Draw(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_gBufferTex[i].Clear(1, 1, 1, 1);
	}
	m_depthStencilTex.Clear(1, 0);
	m_backBuffer.Clear(0, 0, 1, 1);

	m_pointLight.Update();
	m_spotLight.Update();

	//m_RPshadow.SetViewMatrix(&m_shadowViewMat);
	//m_RPshadow.SetModelData(&m_modelData);
	//m_RPshadow.Draw(&m_shadowOutTex, 1024, 1024);
	m_defLam.SetViewMatrix(&m_view);
	m_gBuffer.SetViewMatrix(&m_view);
	m_gBuffer.SetModelData(&m_stageData);
	m_gBuffer.Draw(&m_outGBuffer);
	m_gBuffer.SetModelData(&m_modelData);
	m_gBuffer.Draw(&m_outGBuffer);

	m_defLam.Draw(&m_outBackBuffer);
}

//■■■■■■■■■■■■■■■■■■■■//
//■■■シーンの終了処理を行います。■■■//
//■■■■■■■■■■■■■■■■■■■■//
void	OGL::Demo1::Uninit(void)
{

}