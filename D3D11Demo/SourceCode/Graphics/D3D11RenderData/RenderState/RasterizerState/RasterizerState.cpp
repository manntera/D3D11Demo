//==========================
//===�yRasterizerState.cpp�z
//==========================
//    DirectX11�ɂ�����
//    ���X�^���C�U�X�e�[�g�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"RasterizerState.h"

OGL::RasterizerState::RasterizerState()
{
	mp_state = nullptr;
	CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::RasterizerState::~RasterizerState()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F���C���[�t���[�����g������ݒ肵�܂��B
//������ ����1�Fbool�Fture�̏ꍇ�̓��C���[�t���[����K�p���܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetWireFrameEnable(bool enable)
{
	if (enable)
	{
		m_desc.FillMode = D3D11_FILL_WIREFRAME;
	}
	else
	{
		m_desc.FillMode = D3D11_FILL_SOLID;
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�|���S���̃J�����O��ݒ肵�܂��B
//������ ����1�FD3D11_CULL_MODE�F�J�����O�ݒ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetCullMode(D3D11_CULL_MODE mode)
{
	m_desc.CullMode = mode;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�|���S���̉�]�����ɂ�闠�\��ݒ肵�܂��B
//������ ����1�FROTATORY_FRONT_MODE�F�ݒ荀��
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetRotatoryFrontMode(ROTATORY_FRONT_MODE mode)
{
	m_desc.FrontCounterClockwise = mode;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�[�x�o�C�A�X�Ɋւ���ݒ���s���܂��B
//������ ����1�Fint�F�s�N�Z���ɉ��Z����[�x�l��ݒ肵�܂��B
//������ ����2�Ffloat�F�s�N�Z���̍ő�[�x�o�C�A�X��ݒ肵�܂��B
//������ ����3�Ffloat�F�w��s�N�Z���̃X���[�v�ɑ΂���X�J���l��ݒ肵�܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetDepthBias(int depthBias, float depthBiasClamp, float slopeScaledDepthBias)
{
	m_desc.DepthBias = depthBias;
	m_desc.DepthBiasClamp = depthBiasClamp;
	m_desc.SlopeScaledDepthBias = slopeScaledDepthBias;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�����N���b�s���O��ݒ肵�܂��B
//������ ����1�Fbool�F�L���ɂ��邩���Ȃ���
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetDepthClippingEnable(bool enable)
{
	m_desc.DepthClipEnable = enable;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�}���`�T���v�����O�̃G�A���`�G�C���A�V���O��ݒ肵�܂��B
//������ ����1�Fbool�F�L���ɂ��邩���Ȃ���
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetMultisampleEnable(bool enable)
{
	m_desc.MultisampleEnable = enable;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�}���`�T���v�����O�̃G�A���`�G�C���A�V���O��ݒ肵�܂��B
//�������@         SetMultisampleEnable��false���w�肵�Ă���K�v������܂��B
//������ ����1�Fbool�F�L���ɂ��邩���Ȃ���
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::SetAntialiasedLineEnable(bool enable)
{
	m_desc.AntialiasedLineEnable = enable;
	return true;
}
//��������������������������������������������
//�������@�@�\�F���X�^���C�U�X�e�[�g�I�u�W�F�N�g�𐶐����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�����ɐ������������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::RasterizerState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateRasterizerState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("RasterizerState::Create ���X�^���C�U�X�e�[�g�����Ɏ��s���܂����B");
		return false;
	}
	return true;

}