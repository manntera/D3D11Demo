//==========================
//===【Window.cpp】
//==========================
//    windowの生成とそれの管理・保持を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"Window.h"

OGL::Window::Window()
{
}

OGL::Window::~Window()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：hInstanceを設定します。
//■■■ 引数1：HINSTANCE：hInstance
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::Window::SetHinstance(HINSTANCE*	hInstance)
{
	mp_hInstance = hInstance;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウ名を設定します。
//■■■ 引数1：char*：windowName
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::Window::SetWindowName(char* windowName)
{
	m_windowName = windowName;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウ名を設定します。
//■■■ 引数1：int：ウィンドウの幅
//■■■ 引数2：int：ウィンドウの高さ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::Window::SetWindowSize(int width, int height)
{
	m_winWidth = width;
	m_winHeight = height;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウを生成します。
//■■■ 引数1：int：nCmdShow
//■■■ 引数2：WNDPROC：ウィンドウプロシージャの関数ポインタ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::Window::CreateShowWindow(int nCmdShow, WNDPROC wndProc)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = *mp_hInstance;
	wc.lpszClassName = m_windowName.c_str();
	wc.lpfnWndProc = wndProc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ウィンドウクラスの構造体の初期化エラー", "", MB_OK);
	}
	m_hWnd = CreateWindow(wc.lpszClassName,
		m_windowName.c_str(),
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_winWidth,
		m_winHeight,
		NULL,
		NULL,
		*mp_hInstance,
		NULL);
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウに指定されたhInstanceを取得します。
//■■■ 引数1：void
//■■■   返値：HINSTANCE*
//■■■■■■■■■■■■■■■■■■■■■■
HINSTANCE*	OGL::Window::GetHinstance(void)
{
	return mp_hInstance;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウハンドルを取得します。
//■■■ 引数1：void
//■■■   返値：HWND：ウィンドウハンドル
//■■■■■■■■■■■■■■■■■■■■■■
HWND*			OGL::Window::GetHwnd(void)
{
	return &m_hWnd;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウの幅を取得します。
//■■■ 引数1：void
//■■■   返値：int：幅
//■■■■■■■■■■■■■■■■■■■■■■
int	OGL::Window::GetWidth(void)
{
	return m_winWidth;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ウィンドウの高さを取得します。
//■■■ 引数1：void
//■■■   返値：int：高さ
//■■■■■■■■■■■■■■■■■■■■■■
int	OGL::Window::GetHeight(void)
{
	return m_winHeight;
}