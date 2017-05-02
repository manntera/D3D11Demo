//==========================
//===�ymain.cpp�z
//==========================
//    �Q�[���̃G���g���[�|�C���g�ł��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include<Windows.h>
#include<thread>
#include"Window\Window.h"
#include"GameLoop\GameLoopManager\GameLoopManager.h"
#include"Graphics\D3D11Device\D3D11Device.h"

using namespace std;
#define _CRTDBG_MAP_ALLOC

//��������������������������������//
//�������y�v���g�^�C�v�錾�z������//
//��������������������������������//
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//��������������������������������//
//�������y�G���g���|�C���g�z������//
//��������������������������������//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;

	OGL::Window* hWindow =OGL::Window::GetInstance();

	hWindow->SetHinstance(&hInstance);
	hWindow->SetWindowName("DirectX11Demo");
	hWindow->SetWindowSize(1280, 720);
	hWindow->CreateShowWindow(nCmdShow, (WNDPROC)WndProc);
	OGL::D3D11Device::GetInstance()->Create(OGL::Window::GetInstance()->GetHwnd(),
		OGL::Window::GetInstance()->GetWidth(),
		OGL::Window::GetInstance()->GetHeight());

	OGL::GameLoopManager*	gameLoopMng = OGL::GameLoopManager::GetInstance();
	gameLoopMng->BeginGameLoopManager(60);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)
			{
				gameLoopMng->EndGameLoopManager();
			//	OGL::D3D11Device::GetInstance()->OutputDebugLog();
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//��������������������������������������//
//�������y�E�B���h�E�v���V�[�W���z������//
//��������������������������������������//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message){
	case	WM_DESTROY:
		PostQuitMessage(0);
		break;
	case	WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}