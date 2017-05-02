//==========================
//===�yGameLoopManager.cpp�z
//==========================
//    �Q�[�����[�v�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"GameLoopManager.h"
#include	"../../Window/Window.h"
#include	"../../Graphics/D3D11Device/D3D11Device.h"

OGL::GameLoopManager::GameLoopManager()
{
	m_loopFlg = false;
	mp_gameScene = Demo1::GetInstance();
}

OGL::GameLoopManager::~GameLoopManager()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�Q�[�����[�v���J�n���܂��B
//������ ����1�Ffloat�F�Q�[�����[�v�̃t���[�����[�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::GameLoopManager::BeginGameLoopManager(float frameRate)
{
	m_frameRate = frameRate;
	m_loopFlg = true;
	std::thread	tempThread(&OGL::GameLoopManager::LoopMain, this);
	std::swap(m_loopThread, tempThread);
}
//��������������������������������������������
//�������@�@�\�F�Q�[�����[�v���I�����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::GameLoopManager::EndGameLoopManager(void)
{
	m_loopFlg = false;
	if (m_loopThread.joinable())
	{
		m_loopThread.join();
	}
}

//������������������������//
//�������yprivate�z ������//
//������������������������//

//��������������������������������������������
//�������@�@�\�F�Q�[�����[�v�{�̂ł��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::GameLoopManager::LoopMain(void)
{
	mp_gameScene->Init();
	mp_gameScene->nextScene = mp_gameScene;
	InitInput(*Window::GetInstance()->GetHinstance(), *Window::GetInstance()->GetHwnd());
	m_loopTimer.StartLapTime();
	while (m_loopFlg)
	{
		if (m_loopTimer.GetLapTime() < 1000 / m_frameRate)
		{
			continue;
		}
		m_loopTimer.StartLapTime();
		UpdateInput();
		mp_gameScene->Update();
		mp_gameScene->Draw();
		D3D11Device::GetSwapChain()->Present(0, 0);
		if (mp_gameScene != mp_gameScene->GetNextScene())
		{
			mp_gameScene->Uninit();
			mp_gameScene = mp_gameScene->nextScene;
			mp_gameScene->nextScene = mp_gameScene;
			mp_gameScene->Init();
		}
	}
	mp_gameScene->Uninit();
	UninitInput();
}

