//==========================
//===�yBlendState.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �u�����h�X�e�[�g�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"BlendState.h"

OGL::BlendState::BlendState()
{
	mp_state = nullptr;
	CD3D11_BLEND_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
	m_desc.IndependentBlendEnable = false;
}

OGL::BlendState::~BlendState()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�FAlphaToCoverage�@�\�̃Z�b�g�����܂��B
//������ ����1�Fbool
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::BlendState::SetAlphaToCoverageEnable(bool enable)
{
	m_desc.AlphaToCoverageEnable = enable;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�����_�[�^�[�Q�b�g�ʂ̃u�����h������ݒ肵�܂��B
//������ ����1�FUINT�F�ݒ肷�郌���_�[�^�[�Q�b�g(0~7)
//������ ����2�Fbool�FBlendEnable
//������ ����3�FD3D11_BLEND�FSrcBlend
//������ ����4�FD3D11_BLEND�FDestBlend
//������ ����5�FD3D11_BLEND_OP�FBlendOp
//������ ����6�FD3D11_BLEND�FSrcBlendAlpha
//������ ����7�FD3D11_BLEND�FDestBlendAlpha
//������ ����8�FD3D11_BLEND_OP�FBlendOpAlpha
//������ ����9�FUINT8�FRenderTargetWriteMask
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::BlendState::SetRenderTargetBlendDesc(UINT targetNum, bool BlendEnable, D3D11_BLEND SrcBlend,
	D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcBlendAlpha,
	D3D11_BLEND DestBlendAlpha, D3D11_BLEND_OP BlendOpAlpha, UINT8 RenderTargetWriteMask)
{
	if (targetNum != 0)
	{
		m_desc.IndependentBlendEnable = true;
	}
	if (targetNum > 8)
	{
		ErrorMessage("BlendState::SetRenderTargetBlendDesc �w�肳�ꂽ�����_�[�^�[�Q�b�g�͍ő吔�𒴉߂��Ă��܂��B");
		return false;
	}
	m_desc.RenderTarget[targetNum].BlendEnable = BlendEnable;
	m_desc.RenderTarget[targetNum].SrcBlend = SrcBlend;
	m_desc.RenderTarget[targetNum].DestBlend = DestBlend;
	m_desc.RenderTarget[targetNum].BlendOp = BlendOp;
	m_desc.RenderTarget[targetNum].SrcBlendAlpha = SrcBlendAlpha;
	m_desc.RenderTarget[targetNum].DestBlendAlpha = DestBlendAlpha;
	m_desc.RenderTarget[targetNum].BlendOpAlpha = BlendOpAlpha;
	m_desc.RenderTarget[targetNum].RenderTargetWriteMask = RenderTargetWriteMask;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�u�����h�X�e�[�g�I�u�W�F�N�g�𐶐����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�����ɐ������������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::BlendState::Create(void)
{
	
	if (FAILED(D3D11Device::GetDevice()->CreateBlendState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("BlendState::Create �u�����h�X�e�[�g�̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}