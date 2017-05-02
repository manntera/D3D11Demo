//==========================
//===�yDepthStencilState.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �f�v�X�X�e���V���X�e�[�g�̊Ǘ����s���܂�
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"DepthStencilState.h"

OGL::DepthStencilState::DepthStencilState()
{
	mp_state = nullptr;
	CD3D11_DEPTH_STENCIL_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::DepthStencilState::~DepthStencilState()
{
}

//��������������������������������������������
//�������@�@�\�F�[�x�e�X�g���s�����̐ݒ���s���܂��B
//������ ����1�Fbool�Ftrue=�s�� false=�s��Ȃ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetDepthTestEnable(bool enable)
{
	m_desc.DepthEnable = enable;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�[�x�o�b�t�@�ɏ������ނ��̐ݒ���s���܂��B
//������ ����1�Fbool�Ftrue=�s�� false=�s��Ȃ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetDepthBufferWriteEnable(bool enable)
{
	if (enable)
	{
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	}
	else
	{
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�[�x�o�b�t�@�ւ̏������ݕ��@���w�肵�܂��B
//������ ����1�FD3D11_COMPARISON_FUNC
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetDepthTestComparisonFunc(D3D11_COMPARISON_FUNC func)
{
	m_desc.DepthFunc = func;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�X�e���V���̏������݂��s�����̐ݒ�����܂��B
//������ ����1�Fbool�Ftrue=�s�� false=�s��Ȃ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetStencilEnable(bool enable)
{
	m_desc.StencilEnable = enable;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�X�e���V���ǂݍ��ݎ��Ƀ}�X�N����r�b�g���w�肵�܂��B
//������ ����1�FUINT8�F�}�X�N����r�b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetStencilReadMask(UINT8 mask)
{
	m_desc.StencilReadMask = mask;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�X�e���V���������ݎ��Ƀ}�X�N����r�b�g���w�肵�܂��B
//������ ����1�FUINT8�F�}�X�N����r�b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetStencilWriteMask(UINT8 mask)
{
	m_desc.StencilWriteMask = mask;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�@�����J�����̕����������Ă���s�N�Z���ɂ��Ă̏������w�肵�܂��B
//������ ����1�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�ŕs���i�ɂȂ������Ɏ��s���鏈�����w�肵�܂��B
//������ �����Q�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�ɍ��i���A�[�x�e�X�g�ŕs���i�ɂȂ������Ɏ��s���鏈�����w�肵�܂��B
//������ �����R�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�Ɛ[�x�e�X�g�ō��i�������Ɏ��s���鏈�����w�肵�܂��B
//������ �����S�FD3D11_COMPARISON_FUNC�F�X�e���V���o�b�t�@�̔�r���@���w�肵�܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetFrontFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp, D3D11_COMPARISON_FUNC StencilFunc)
{
	m_desc.FrontFace.StencilFailOp = StencilFailOp;
	m_desc.FrontFace.StencilDepthFailOp = StencilDepthFailOp;
	m_desc.FrontFace.StencilPassOp = StencilPassOp;
	m_desc.FrontFace.StencilFunc = StencilFunc;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�@�����J�����̕����������Ă��Ȃ��s�N�Z���ɂ��Ă̏������w�肵�܂��B
//������ ����1�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�ŕs���i�ɂȂ������Ɏ��s���鏈�����w�肵�܂��B
//������ �����Q�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�ɍ��i���A�[�x�e�X�g�ŕs���i�ɂȂ������Ɏ��s���鏈�����w�肵�܂��B
//������ �����R�FD3D11_STENCIL_OP�F�X�e���V���e�X�g�Ɛ[�x�e�X�g�ō��i�������Ɏ��s���鏈�����w�肵�܂��B
//������ �����S�FD3D11_COMPARISON_FUNC�F�X�e���V���o�b�t�@�̔�r���@���w�肵�܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::SetBackFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp, D3D11_COMPARISON_FUNC StencilFunc)
{
	m_desc.BackFace.StencilFailOp = StencilFailOp;
	m_desc.BackFace.StencilDepthFailOp = StencilDepthFailOp;
	m_desc.BackFace.StencilPassOp = StencilPassOp;
	m_desc.BackFace.StencilFunc = StencilFunc;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���X�e�[�g�𐶐����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::DepthStencilState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateDepthStencilState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("DepthStencilState::Create �f�v�X�X�e���V���X�e�[�g�̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}
