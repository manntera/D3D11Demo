//==========================
//===�yViewPort.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �r���[�|�[�g�ݒ��
//    �Ǘ��E�ێ����s���܂�
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"ViewPort.h"

OGL::ViewPort::ViewPort()
{
	D3D11_VIEWPORT temp;
	temp.TopLeftX = 0;
	temp.TopLeftY = 0;
	temp.Width = 0;
	temp.Height = 0;
	temp.MinDepth = 0.0f;
	temp.MaxDepth = 1.0f;
	mp_viewPort = std::make_shared<D3D11_VIEWPORT>(temp);
}

OGL::ViewPort::~ViewPort()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�r���[�|�[�g�̍L����ݒ肵�܂��B
//������ ����1�Ffloat�FX�J�n�n�_(�������̏ꏊ)
//������ ����2�Ffloat�FY�J�n�n�_(������̏ꏊ)
//������ ����3�Ffloat�F��
//������ ����4�Ffloat�F����
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::ViewPort::SetRange(float topLeftX, float topLeftY, float Width, float height)
{
	mp_viewPort->TopLeftX = topLeftX;
	mp_viewPort->TopLeftY = topLeftY;
	mp_viewPort->Width = Width;
	mp_viewPort->Height = height;
}

//��������������������������������������������
//�������@�@�\�F�[�x���̍L����ݒ肵�܂��B
//������ ����1�Ffloat�F�ŏ�
//������ ����2�Ffloat�F�ő�
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::ViewPort::SetDepth(float min, float max)
{
	mp_viewPort->MinDepth = min;
	mp_viewPort->MaxDepth = max;
}
