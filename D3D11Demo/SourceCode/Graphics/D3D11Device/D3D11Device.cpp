//==========================
//===�yD3D11Device.cpp�z
//==========================
//    DirectX11�ɂ�����A
//    �f�o�C�X/�f�o�C�X�R���e�L�X�g��
//    �Ǘ��E�ێ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"D3D11Device.h"

OGL::D3D11Device::D3D11Device()
{
}

OGL::D3D11Device::~D3D11Device()
{
}
//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�f�o�C�X�𐶐����܂��B
//������ ����1�FHWND*�F�E�B���h�E�n���h��
//������ ����2�Fint�@�@ �F�E�B���h�E�̕�
//������ ����3�Fint      �F�E�B���h�E�̍���
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11Device::Create(HWND*	hWnd, int width, int height)
{
	this->CreateDevice(hWnd, width, height);
}

//��������������������������������������������
//�������@�@�\�FDirectX11�̃f�o�b�O���O���o�͂��܂��B
//������			�������A���̃��\�b�h��Windows8�ȉ��Ŏ��s���鎖�͏o���܂���B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�o�͂ɐ����������ǂ���
//��������������������������������������������
bool	OGL::D3D11Device::OutputDebugLog(void)
{
#ifdef _DEBUG
	HRESULT hr;
	hr = mp_device.Get()->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(m_pD3dDebug.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorMessage("D3D11Device::OutputDebugLog QueryInterface�Ɏ��s���܂����B");
		return false;
	}

	m_pD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	return true;
#endif
}

//������������������������//
//�������yprivate�z ������//
//������������������������//

//��������������������������������������������
//�������@�@�\�F�f�o�C�X�̐��������s���܂��B
//������ ����1�FHWND*�F�E�B���h�E�n���h��
//������ ����2�Fint�@�@ �F�E�B���h�E�̕�
//������ ����3�Fint      �F�E�B���h�E�̍���
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11Device::CreateDevice(HWND*	hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC	swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));
	swapDesc.BufferCount = 1;         //�o�b�N�o�b�t�@�̐�
	swapDesc.BufferDesc.Width = width;     //�o�b�t�@�̕�
	swapDesc.BufferDesc.Height = height;    //�o�b�t�@�̍���
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //�o�b�t�@�̃t�H�[�}�b�g
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;   //���t���b�V�����[�g
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = *hWnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = TRUE;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	UINT flags = 0;
#ifdef _DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL  FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, flags,
		&FeatureLevel, 1,
		D3D11_SDK_VERSION, &swapDesc,
		&mp_swapChain, &mp_device,
		NULL, &mp_deviceContext);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("�f�o�C�X�ƃX���b�v�`�F�C���̐����Ɏ��s���܂����B"), TEXT("Err"), MB_OK);
	}
}







void ErrorMessage(char* str)
{
	MessageBox(NULL, TEXT(str), TEXT("Err"), MB_OK);
}