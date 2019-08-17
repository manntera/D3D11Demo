//==========================
//===�yDemo3.cpp�z
//==========================
//    �^�C�g����ʂ̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"../GameSceneList.h"
#include	"../../GameLoopManager/GameLoopManager.h"
#include	"../../../Window/Window.h"

#include <random>

//��������������������������������������//
//�������V�[���̏��������s���܂��B������//
//��������������������������������������//
void	OGL::Demo3::Init(void)
{
	//---�s�񐶐�
	ProjectionMatrix prj;
	prj.SetAspect(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	prj.SetClippingPlane(1, 1000);
	prj.SetFovangle(45);

	m_view.SetCenterPos(0, 7, 0);
	m_view.SetRotation(19, 0, 0);
	m_view.SetLength(58);
	
	m_world.SetTransPos(0, 0, 0);

	//---�e�N�X�`������
	m_backBuffer.Create();
	m_depthStencilTex.Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DSTEX_FORMAT::DSF_D24S8, false);
	for (int i = 0; i < 2; i++)
	{
		m_gBufferTex[i].Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM);
	}
	m_gBufferTex[2].Create(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//---�e�N�X�`���ݒ�
	for (int i = 0; i < 3; i++)
	{
		m_outGBuffer.SetTexture(&m_gBufferTex[i], i);
		m_inDefLam.SetTexture(&m_gBufferTex[i], i);
	}
	m_outGBuffer.SetTexture(&m_depthStencilTex);
	m_outBackBuffer.SetTexture(&m_backBuffer, 0);
	//---���C�g�̃Z�b�e�B���O
	const float posRange = 40.0;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colL(0.0, 1.0);
	std::uniform_real_distribution<float> posXZL(-posRange, posRange);
	std::uniform_real_distribution<float> posYL(0, posRange);
	std::uniform_real_distribution<float> decMinL(0.1, 20.0);
	std::uniform_real_distribution<float> decMaxL(20.0, 50.0);
	m_pointLight.SetSlotCount(MAX_POINT_LIGHT_COUNT);
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; i++)
	{
		m_pointLight.SetPos(i, D3DXVECTOR3(posXZL(mt), posYL(mt), posXZL(mt)));
		m_pointLight.SetDecrement(i, decMinL(mt), decMaxL(mt));
		m_pointLight.SetDiffuseCollar(i, D3DXVECTOR4(colL(mt), colL(mt), colL(mt), colL(mt)));
	}

	//---RenderPackage�ɃZ�b�e�B���O
	//GBufferTessellation
	m_gBufferTessellation.SetProjectionMatrix(&prj);
	m_gBufferTessellation.SetWorldMatrix(&m_world);
	//DeferredLambert�̐ݒ�
	m_defLam.SetProjectionMatrix(&prj);
	m_defLam.SetInputTexture(&m_inDefLam);
	m_defLam.SetPointLight(&m_pointLight);
}

//������������������������������������//
//�������V�[���̍X�V���s���܂��B������//
//������������������������������������//
void	OGL::Demo3::Update(void)
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
	}
	D3DXMATRIX tempV;
	D3DXMatrixInverse(&tempV, nullptr, m_view.Getmatrix());
	m_pointLight.SetPos(0, D3DXVECTOR3(tempV._41, tempV._42, tempV._43));
	
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		this->nextScene = Demo0::GetInstance();
	}
}

//������������������������������������//
//�������V�[���̕`����s���܂��B������//
//������������������������������������//
void	OGL::Demo3::Draw(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_gBufferTex[i].Clear(1, 1, 1, 1);
	}
	m_depthStencilTex.Clear(1, 0);
	m_backBuffer.Clear(0, 0, 1, 1);

	m_pointLight.Update();

	m_defLam.SetViewMatrix(&m_view);

	m_gBufferTessellation.SetViewMatrix(&m_view);
	m_gBufferTessellation.Draw(&m_outGBuffer);

	m_defLam.Draw(&m_outBackBuffer);
}

//����������������������������������������//
//�������V�[���̏I���������s���܂��B������//
//����������������������������������������//
void	OGL::Demo3::Uninit(void)
{

}