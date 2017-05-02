//==========================
//===�yGeometryShader.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �W�I���g���V�F�[�_�[�̊Ǘ����s���܂�
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"GeometryShader.h"

OGL::GeometryShader::GeometryShader()
{
}

OGL::GeometryShader::~GeometryShader()
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
bool	OGL::GeometryShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("GeometryShader::CreateShader �W�I���g���V�F�[�_�̃R���p�C���Ɏ��s���܂����B");
		return false;
	}
	HRESULT hr = D3D11Device::GetDevice()->CreateGeometryShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_geometryShader.GetAddressOf());
	if (FAILED(hr))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("GeometryShader::CreateShader �W�I���g���V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}
