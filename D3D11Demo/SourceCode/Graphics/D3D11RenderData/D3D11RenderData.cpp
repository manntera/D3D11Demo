//==========================
//===�yD3D11RenderData.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �����_�����O����ۂɕK�v�ȃp�C�v���C���f�[�^��ێ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"D3D11RenderData.h"

OGL::D3D11RenderData::D3D11RenderData()
{
	mp_inputLayout = nullptr;
	mp_vertexShader = nullptr;
	mp_geometryShader = nullptr;
	mp_pixelShader = nullptr;
	
	mp_rasterizerState = nullptr;
	mp_depthStencilState = nullptr;
	mp_blendState = nullptr;
	m_blendFactor[0] = 1;
	m_blendFactor[1] = 1;
	m_blendFactor[2] = 1;
	m_blendFactor[3] = 1;
	m_sampleMask = 0xffffffff;
	m_writeStencilNum = 1;
	mp_devCon=D3D11Device::GetInstance()->GetDeviceConText();
}
OGL::D3D11RenderData::~D3D11RenderData()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�v���~�e�B�u�g�|���W�[���Z�b�g���܂��B
//������ ����1�FVertexShader* �F���_�V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//�������������������������������������������� TODO: �C���X�^���X�`��p�̎d�g�ݍ�낤��
void OGL::D3D11RenderData::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	m_primitiveTopology = topology;
}

//��������������������������������������������
//�������@�@�\�F���_�V�F�[�_�[�̃Z�b�g���s���܂��B
//������ ����1�FVertexShader* �F���_�V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//�������������������������������������������� TODO: �C���X�^���X�`��p�̎d�g�ݍ�낤��
void OGL::D3D11RenderData::SetVertexShader(VertexShader* vertexShader)
{
	mp_vertexShader = vertexShader->mp_vertexShader.Get();
	mp_inputLayout = vertexShader->mp_vertexLayout.Get();
}

//��������������������������������������������
//�������@�@�\�F�n���V�F�[�_�[�̃Z�b�g���s���܂��B
//������ ����1�FHullShader* �F�n���V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//�������������������������������������������� TODO: �C���X�^���X�`��p�̎d�g�ݍ�낤��
void OGL::D3D11RenderData::SetHullShader(HullShader* hullShader)
{
	mp_hullShader = hullShader->mp_hullShader;
}

//��������������������������������������������
//�������@�@�\�F�h���C���V�F�[�_�[�̃Z�b�g���s���܂��B
//������ ����1�FDomainShader* �F�h���C���V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//�������������������������������������������� TODO: �C���X�^���X�`��p�̎d�g�ݍ�낤��
void OGL::D3D11RenderData::SetDomainShader(DomainShader* domainShader)
{
	mp_domainShader = domainShader->mp_domainShader;
}

//��������������������������������������������
//�������@�@�\�F�W�I���g���V�F�[�_�[�̃Z�b�g���s���܂��B
//������ ����1�FGeometryShader* �F�W�I���g���V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//�������������������������������������������� TODO: �C���X�^���X�`��p�̎d�g�ݍ�낤��
void OGL::D3D11RenderData::SetGeometryShader(GeometryShader* geometryShader)
{
	mp_geometryShader = geometryShader->mp_geometryShader;
}

//��������������������������������������������
//�������@�@�\�F�s�N�Z���V�F�[�_�[�̃Z�b�g���s���܂��B
//������ ����1�FPixelShader* �F�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetPixelShader(PixelShader* pixelShader)
{
	mp_pixelShader = pixelShader->mp_pixelShader;
}

//��������������������������������������������
//�������@�@�\�F���_�V�F�[�_�[�ɃT���v���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FSamplerState* �F�T���v���[�X�e�[�g�I�u�W�F�N�g
//������ ����2�Fint �F�Z�b�g����X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetVsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_vsSamplerState.size(); i++)
	{
		if (m_vsSamplerState[i].slot == slot)
		{
			m_vsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_vsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_vsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//��������������������������������������������
//�������@�@�\�F�n���V�F�[�_�[�ɃT���v���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FSamplerState* �F�T���v���[�X�e�[�g�I�u�W�F�N�g
//������ ����2�Fint �F�Z�b�g����X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetHsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_hsSamplerState.size(); i++)
	{
		if (m_hsSamplerState[i].slot == slot)
		{
			m_hsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_hsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_hsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//��������������������������������������������
//�������@�@�\�F�h���C���V�F�[�_�[�ɃT���v���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FSamplerState* �F�T���v���[�X�e�[�g�I�u�W�F�N�g
//������ ����2�Fint �F�Z�b�g����X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetDsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_dsSamplerState.size(); i++)
	{
		if (m_dsSamplerState[i].slot == slot)
		{
			m_dsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_dsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_dsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}
//��������������������������������������������
//�������@�@�\�F�W�I���g���V�F�[�_�[�ɃT���v���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FSamplerState* �F�T���v���[�X�e�[�g�I�u�W�F�N�g
//������ ����2�Fint �F�Z�b�g����X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetGsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_gsSamplerState.size(); i++)
	{
		if (m_gsSamplerState[i].slot == slot)
		{
			m_gsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_gsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_gsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//��������������������������������������������
//�������@�@�\�F�s�N�Z���V�F�[�_�[�ɃT���v���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FSamplerState* �F�T���v���[�X�e�[�g�I�u�W�F�N�g
//������ ����2�Fint �F�Z�b�g����X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetPsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_psSamplerState.size(); i++)
	{
		if (m_psSamplerState[i].slot == slot)
		{
			m_psSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_psSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_psSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//��������������������������������������������
//�������@�@�\�F���X�^���C�U�̃Z�b�g���s���܂��B
//������ ����1�FRasterizerState* �F���X�^���C�U�X�e�[�g�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetRasterizerState(RasterizerState* rasterizerState)
{
	mp_rasterizerState = rasterizerState->mp_state;
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FDepthStencilState* �F�f�v�X�X�e���V���X�e�[�g�I�u�W�F�N�g
//������ ����2�FUINT                     �F�X�e���V���ɏ������ސ��l���L�q���܂��B
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetDepthStencilState(DepthStencilState* depthStencilState, UINT writeStencilNum)
{
	mp_depthStencilState = depthStencilState->mp_state;
	m_writeStencilNum = writeStencilNum;
}

//��������������������������������������������
//�������@�@�\�F�u�����h�X�e�[�g�̃Z�b�g���s���܂��B
//������ ����1�FVertexShader*�F�u�����h�X�e�[�g�I�u�W�F�N�g
//������ ����2�FUINT				�F�T���v���K�o���b�W(�K��l��0xffffffff)
//������ ����3�Ffloat				�FSetRenderTargetBlendDesc��D3D11_BLEND_BLEND_FACTOR��I�������ۂɗp������F���w�肵�܂��B(r)
//������ ����4�Ffloat				�F����(g)
//������ ����5�Ffloat				�F����(b)
//������ ����6�Ffloat				�F����(a)
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetBlendState(BlendState* blendState, UINT sampleMask, float factor_r, float factor_g, float factor_b, float factor_a)
{
	mp_blendState = blendState->mp_state;
	m_sampleMask = sampleMask;
	m_blendFactor[0] = factor_r;
	m_blendFactor[1] = factor_g;
	m_blendFactor[2] = factor_b;
	m_blendFactor[3] = factor_a;
}

//��������������������������������������������
//�������@�@�\�F�r���[�|�[�g�̃Z�b�g���s���܂��B
//������ ����1�FViewPort* �F�r���[�|�[�g�I�u�W�F�N�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void OGL::D3D11RenderData::SetViewPort(ViewPort* viewPort)
{
	mp_viewPort = viewPort->mp_viewPort;
}

