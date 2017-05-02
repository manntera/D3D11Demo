//==========================
//===【GameLoopManager.cpp】
//==========================
//    ゲームループの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
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

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ゲームループを開始します。
//■■■ 引数1：float：ゲームループのフレームレート
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::GameLoopManager::BeginGameLoopManager(float frameRate)
{
	m_frameRate = frameRate;
	m_loopFlg = true;
	std::thread	tempThread(&OGL::GameLoopManager::LoopMain, this);
	std::swap(m_loopThread, tempThread);
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ゲームループを終了します。
//■■■ 引数1：void
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::GameLoopManager::EndGameLoopManager(void)
{
	m_loopFlg = false;
	if (m_loopThread.joinable())
	{
		m_loopThread.join();
	}
}

//■■■■■■■■■■■■//
//■■■【private】 ■■■//
//■■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ゲームループ本体です。
//■■■ 引数1：void
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
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

