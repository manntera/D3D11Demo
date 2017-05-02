//==========================
//===�yHullShader.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �s�N�Z���V�F�[�_�[�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"HullShader.h"

OGL::HullShader::HullShader() :
mp_hullShader(nullptr)
{
}

OGL::HullShader::~HullShader()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�V�F�[�_�[���R���p�C�����Z�b�e�B���O���܂��B
//������ ����1�Fchar*�F�V�F�[�_�[�t�@�C����
//������ ����2�Fchar*�F�R���p�C������֐���
//������ ����3�Fchar*�F�V�F�[�_�[�o�[�W����
//������   �Ԓl�Fbool�Ftrue�c���� false�c���s
//��������������������������������������������
bool	OGL::HullShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("HullShader::CreateShader �n���V�F�[�_�̃R���p�C���Ɏ��s���܂����B");
		return false;
	}
	HRESULT hr = D3D11Device::GetDevice()->CreateHullShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_hullShader.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("�n���V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s���܂����B"), TEXT("Err"), MB_OK);
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("HullShader::CreateShader �n���V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}