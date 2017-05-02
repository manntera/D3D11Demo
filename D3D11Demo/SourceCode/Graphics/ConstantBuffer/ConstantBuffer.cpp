//==========================
//===�yConstantBuffer.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �R���X�^���g�o�b�t�@(�萔�o�b�t�@)���Ǘ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"ConstantBuffer.h"

OGL::ConstantBuffer::ConstantBuffer()
{
}

OGL::ConstantBuffer::~ConstantBuffer()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�萔�o�b�t�@�𐶐����܂��B
//������ ����1�FUINT�F�Z�b�g����X���b�g���w�肵�܂��B
//������ ����2�FUINT�F�Z�b�g����萔�o�b�t�@�̃T�C�Y���w�肵�܂��B(16�̔{���ł��鎖)
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::ConstantBuffer::Create(UINT byteSize)
{
	if ((byteSize % 16) != 0)
	{
		ErrorMessage("ConstantBuffer::Create �萔�o�b�t�@�̃T�C�Y�͂P�U�̔{���Ŏw�肵�ĉ�����");
		return false;
	}
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = byteSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	m_bufferSize = byteSize;

	if (FAILED(D3D11Device::GetDevice()->CreateBuffer(&desc,nullptr,&mp_buffer)))
	{
		ErrorMessage("ConstantBuffer::Create �R���X�^���g�o�b�t�@�̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�萔�o�b�t�@�Ƀf�[�^��ݒ肵�܂��B
//������ ����1�Fvoid*�F�Z�b�g���郊�\�[�X�z��
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::ConstantBuffer::SetResource(void* resource)
{
	D3D11Device::GetDeviceConText()->UpdateSubresource
		(mp_buffer.Get(), 0, NULL, resource, 0, 0);
	return true;
}
