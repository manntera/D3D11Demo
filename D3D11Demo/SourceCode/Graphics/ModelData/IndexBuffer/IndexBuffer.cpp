//==========================
//===�yIndexBuffer.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �C���f�b�N�X�o�b�t�@���Ǘ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"IndexBuffer.h"

OGL::IndexBuffer::IndexBuffer()
{
	mp_buffer = nullptr;
	m_count = 0;
}

OGL::IndexBuffer::~IndexBuffer()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�C���f�b�N�X�o�b�t�@�𐶐����܂��B
//������ ����1�FUINT�F�C���f�b�N�X��
//������ ����2�Fint*�F�C���f�b�N�X��
//������   �Ԓl�Fbool�F�Z�b�g�o�������ǂ���
//��������������������������������������������
bool	OGL::IndexBuffer::Create(UINT indexCount, int* indexData)
{
	m_count = indexCount;
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.ByteWidth = sizeof(int)* indexCount;
	hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA hSubResourceData;
	hSubResourceData.pSysMem = indexData;
	hSubResourceData.SysMemPitch = 0;
	hSubResourceData.SysMemSlicePitch = 0;
	HRESULT hr = D3D11Device::GetDevice()->CreateBuffer(&hBufferDesc, &hSubResourceData, &mp_buffer);
	if (FAILED(hr))
	{
		ErrorMessage("IndexBuffer::Create �o�b�t�@�̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}