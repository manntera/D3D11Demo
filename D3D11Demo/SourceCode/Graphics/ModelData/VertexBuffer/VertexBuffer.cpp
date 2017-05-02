//==========================
//===�yVertexBuffer.cpp�z
//==========================
//    DirectX11�ɂ�����A
//    ���_�o�b�t�@���Ǘ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"VertexBuffer.h"
#include<string.h>

OGL::VertexBuffer::VertexBuffer()
{
	mp_buffer = nullptr;
	mp_data = nullptr;
	m_count = 0;
	m_updateEnable = false;
}

OGL::VertexBuffer::~VertexBuffer()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F���_�o�b�t�@�𐶐����܂��B
//������ ����1�FUINT�F���_��
//������ ����2�FD3DXVECTOR4*�F���_�f�[�^
//������ ����3�Fbool�F���㒸�_�f�[�^���X�V����\�肪����̂ł����true,�����̂ł����false
//������   �Ԓl�Fbool�F�Z�b�g�o�������ǂ���
//��������������������������������������������
bool	OGL::VertexBuffer::Create(UINT vertexCount, D3DXVECTOR4* vertexData, bool	updateEnable)
{
	m_count = vertexCount;
	m_updateEnable = updateEnable;

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(D3DXVECTOR4) * m_count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertexData;
	if (FAILED(D3D11Device::GetDevice()->CreateBuffer(&bd, &InitData, &mp_buffer)))
	{
		ErrorMessage("VertexBuffer::Create ���_�o�b�t�@�̐����Ɏ��s���܂����B");
		return false;
	}

	if (updateEnable)
	{
		std::unique_ptr<D3DXVECTOR4[]> temp(new D3DXVECTOR4[m_count]);
		mp_data = std::move(temp);
		memcpy(mp_data.get() , vertexData, sizeof(D3DXVECTOR4) * m_count);
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�ێ����Ă��钸�_�f�[�^��Ԃ��܂��B�������A�X�V�\�Ȓ��_�o�b�t�@�Ɍ���܂��B
//������ ����1�FUINT�F�Ԃ����������_�̏ꏊ
//������   �Ԓl�FD3DXVECTOR4�F���_���
//��������������������������������������������
D3DXVECTOR4	OGL::VertexBuffer::GetUpdateVertexData(UINT vertexNum)
{
	if (vertexNum > m_count)
	{
		ErrorMessage("VertexBuffer::GetUpdateVertexData �w�肵�����_�������߂��Ă��܂��B");
		return D3DXVECTOR4(0, 0, 0, 0);
	}
	if (m_updateEnable)
	{
		return mp_data[vertexNum];
	}
	else
	{
		ErrorMessage("VertexBuffer::GetUpdateVertexData ���̒��_�o�b�t�@�ɂ͍X�V�p�f�[�^�����݂��܂���B");
		return D3DXVECTOR4(0, 0, 0, 0);
	}
}

//��������������������������������������������
//�������@�@�\�F�X�V���钸�_�f�[�^���Z�b�g���܂��B�������A�X�V�\�Ȓ��_�o�b�t�@�Ɍ���܂��B
//������ ����1�FUINT�F�Z�b�g���钸�_�̏ꏊ
//������ ����2�FD3DXVECTOR4�F���_���
//������   �Ԓl�Fbool�F�ݒ�o�������ǂ���
//��������������������������������������������
bool	OGL::VertexBuffer::SetUpdateVertexData(UINT vertexNum, D3DXVECTOR4 vertexData)
{
	if (vertexNum > m_count)
	{
		ErrorMessage("VertexBuffer::SetUpdateVertexData �w�肵�����_�������߂��Ă��܂��B");
		return false;
	}
	if (m_updateEnable)
	{
		mp_data[vertexNum] = vertexData;
		return true;
	}
	else
	{
		ErrorMessage("VertexBuffer::SetUpdateVertexData ���̒��_�o�b�t�@�ɂ͍X�V�p�f�[�^�����݂��܂���B");
		return false;
	}
}

//��������������������������������������������
//�������@�@�\�F���̒��_�o�b�t�@�͍X�V�\�ł��邩���m�F���܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�X�V�\�ł����true,�X�V�ł��Ȃ��̂ł����false
//��������������������������������������������
bool	OGL::VertexBuffer::IsUpdate(void)
{
	return m_updateEnable;
}

//��������������������������������������������
//�������@�@�\�F���_�o�b�t�@���X�V���܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�X�V�o�������ǂ���
//��������������������������������������������
bool OGL::VertexBuffer::UpdateBuffer(void)
{
	if (m_updateEnable)
	{
		D3D11Device::GetDeviceConText()->UpdateSubresource
			(mp_buffer.Get(), 0, NULL, mp_data.get(), 0, 0);
		return true;
	}
	else
	{
		ErrorMessage("VertexBuffer::UpdateBuffer ���̒��_�o�b�t�@�ɂ͍X�V�p�f�[�^�����݂��܂���B");
		return false;
	}
}