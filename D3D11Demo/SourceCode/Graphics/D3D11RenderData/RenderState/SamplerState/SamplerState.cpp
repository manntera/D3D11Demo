//==========================
//===�ySamplerState.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �T���v���[�X�e�[�g�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"SamplerState.h"

OGL::SamplerState::SamplerState()
{
	mp_state = nullptr;
	CD3D11_SAMPLER_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::SamplerState::~SamplerState()
{
}
//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�e�N�X�`���̃t�B���^�����O���[�h���w�肵�܂��B
//������ ����1�FD3D11_FILTER�F�t�B���^�����O���\�b�h�̐ݒ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetFilter(D3D11_FILTER filter)
{
	m_desc.Filter = filter;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�w�肵��UV��0~1�ȊO�Ɏw�肳��Ă���ꍇ�̐ݒ�����܂��B
//������ ����1�FD3D11_TEXTURE_ADDRESS_MODE�FU�l�Ɋւ���ݒ�����܂��B
//������ ����1�FD3D11_TEXTURE_ADDRESS_MODE�FV�l�Ɋւ���ݒ�����܂��B
//������ ����1�FD3D11_TEXTURE_ADDRESS_MODE�FW�l�Ɋւ���ݒ�����܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetAddresMode(D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w)
{
	m_desc.AddressU = u;
	m_desc.AddressV = v;
	m_desc.AddressW = w;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�~�b�v�}�b�v���x���̃I�t�Z�b�g�l��ݒ肵�܂��B
//������ ����1�Ffloat�F�I�t�Z�b�g�l
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetMipLODBias(float bias)
{
	m_desc.MipLODBias = bias;
	return true;
}

//��������������������������������������������
//�������@�@�\�FSetFilter��D3D11_FILTER_ANISOTROPIC�܂��́A
//�������@�@�@�@D3D11_FILTER_COMPARISON_ANISOTROPIC ���ݒ肳��Ă����
//�������@�@�@�@�ٕ�����Ԃ̃N�����v�l��ݒ肵�܂��B
//������ ����1�Funsigned int�F�P�`�P�U�̃N�����v�l
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetMaxAnisotropy(unsigned int anisotropy)
{
	if (anisotropy > 16 || anisotropy<=0)
	{
		ErrorMessage("SamplerState::SetMaxAnisotropy �w�肳�ꂽ�N�����v�l�͍ő啝�𒴂��Ďw�肳��Ă��܂��B");
		return false;
	}
	m_desc.MaxAnisotropy = anisotropy;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�����T���v�����O�f�[�^�ɑ΂���f�[�^���r����֐���ݒ肵�܂��B
//������ ����1�FD3D11_COMPARISON_FUNC�F�t�B���^�����O���\�b�h�̐ݒ�
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetComparisonFunc(D3D11_COMPARISON_FUNC func)
{
	m_desc.ComparisonFunc = func;
	return true;
}

//��������������������������������������������
//�������@�@�\�FSetFilter��D3D11_TEXTURE_ADDRESS_BORDER ���ݒ肳��Ă����
//�������@�@�@�@���E�̐F��ݒ肵�܂��B
//������ ����1�Ffloat�Fr�F�ԐF�̐ݒ�����܂��B
//������ ����2�Ffloat�Fg�F�ΐF�̐ݒ�����܂��B
//������ ����3�Ffloat�Fb�F�F�̐ݒ�����܂��B
//������ ����4�Ffloat�Fa�F���̐ݒ�����܂��B
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetBorderColor(float r, float g, float b, float a)
{
	if (r > 1 || r < 0 || g>1 || g < 0 || b>1 || b < 0 || a>1 || a < 0)
	{
		ErrorMessage("SamplerState::SetBorderColor �w�肳�ꂽ�F�̒���0�`1�͈̔͊O���w�肵�Ă��镨������܂��B");
		return false;
	}

	m_desc.BorderColor[0] = r;
	m_desc.BorderColor[1] = g;
	m_desc.BorderColor[2] = b;
	m_desc.BorderColor[3] = a;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�A�N�Z�X���N�����v����~�b�v�}�b�v�͈͂̉����E����l��ݒ肵�܂��B
//������ ����1�Ffloat�F�����l
//������ ����2�Ffloat�F����l
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::SetLOD(float min, float max)
{
	if (min > max)
	{
		ErrorMessage("SamplerState::SetLOD min�l��max�l�𒴂��Ďw�肳��Ă��܂��B");
		return false;
	}
	m_desc.MinLOD = min;
	m_desc.MaxLOD = max;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�T���v���X�e�[�g�I�u�W�F�N�g�𐶐����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fbool�F�����ɐ������������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::SamplerState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateSamplerState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("SamplerState::Create �T���v���I�u�W�F�N�g�𐶐��ł��܂���ł���");
		return false;
	}
	return true;
}