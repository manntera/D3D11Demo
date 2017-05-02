//==========================
//===�yWindow.cpp�z
//==========================
//    window�̐����Ƃ���̊Ǘ��E�ێ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"Window.h"

OGL::Window::Window()
{
}

OGL::Window::~Window()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�FhInstance��ݒ肵�܂��B
//������ ����1�FHINSTANCE�FhInstance
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::Window::SetHinstance(HINSTANCE*	hInstance)
{
	mp_hInstance = hInstance;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E����ݒ肵�܂��B
//������ ����1�Fchar*�FwindowName
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::Window::SetWindowName(char* windowName)
{
	m_windowName = windowName;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E����ݒ肵�܂��B
//������ ����1�Fint�F�E�B���h�E�̕�
//������ ����2�Fint�F�E�B���h�E�̍���
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::Window::SetWindowSize(int width, int height)
{
	m_winWidth = width;
	m_winHeight = height;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E�𐶐����܂��B
//������ ����1�Fint�FnCmdShow
//������ ����2�FWNDPROC�F�E�B���h�E�v���V�[�W���̊֐��|�C���^
//������   �Ԓl�Fvoid
//��������������������������������������������
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
		MessageBox(NULL, "�E�B���h�E�N���X�̍\���̂̏������G���[", "", MB_OK);
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

//��������������������������������������������
//�������@�@�\�F�E�B���h�E�Ɏw�肳�ꂽhInstance���擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FHINSTANCE*
//��������������������������������������������
HINSTANCE*	OGL::Window::GetHinstance(void)
{
	return mp_hInstance;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E�n���h�����擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FHWND�F�E�B���h�E�n���h��
//��������������������������������������������
HWND*			OGL::Window::GetHwnd(void)
{
	return &m_hWnd;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E�̕����擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fint�F��
//��������������������������������������������
int	OGL::Window::GetWidth(void)
{
	return m_winWidth;
}

//��������������������������������������������
//�������@�@�\�F�E�B���h�E�̍������擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fint�F����
//��������������������������������������������
int	OGL::Window::GetHeight(void)
{
	return m_winHeight;
}