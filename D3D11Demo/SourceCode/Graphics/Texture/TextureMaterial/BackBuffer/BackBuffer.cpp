//==========================
//===�yBackBuffer.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �o�b�N�o�b�t�@���Ǘ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"BackBuffer.h"

OGL::BackBuffer::BackBuffer()
:mp_backBufferView(nullptr)
{

}

OGL::BackBuffer::~BackBuffer()
{
	this->Release();
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�o�b�N�o�b�t�@�𐶐����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
bool	OGL::BackBuffer::Create(void)
{
	HRESULT	hr;
	ID3D11Texture2D *BackBuffer = nullptr;
	D3D11Device::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
	hr=D3D11Device::GetDevice()->CreateRenderTargetView(BackBuffer, NULL, &mp_backBufferView);
	SAFE_RELEASE(BackBuffer);
	if (FAILED(hr))
	{
		ErrorMessage("BackBuffer::Create �o�b�N�o�b�t�@�̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�o�b�N�o�b�t�@�̃e�N�X�`�����N���A����F�œh��Ԃ��܂��B
//������ ����1�Ffloat�F��
//������ ����2�Ffloat�F��
//������ ����3�Ffloat�F��
//������ ����4�Ffloat�F�A���t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::BackBuffer::Clear(float r, float g, float b, float a)
{
	float col[4] = { r, g, b, a };
	D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_backBufferView, col);
}

//��������������������������������������������
//�������@�@�\�F�o�b�N�o�b�t�@��j�����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::BackBuffer::Release(void)
{
	SAFE_RELEASE(mp_backBufferView);
}

//��������������������������������������������
//�������@�@�\�F�o�b�N�o�b�t�@�r���[���擾���܂��B
//������ ����1�FID3D11RenderTargetView*�F�o�b�N�o�b�t�@�̃r���[
//������   �Ԓl�Fvoid
//��������������������������������������������
ID3D11RenderTargetView*	OGL::BackBuffer::GetRTV(void)
{
	return mp_backBufferView;
}