//==========================
//===�yVertexShader.cpp�z
//==========================
//    DirectX11�ɂ�����
//    ���_�V�F�[�_�[�̊Ǘ����s���܂�
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"VertexShader.h"

OGL::VertexShader::VertexShader():
m_layoutum(0),
mp_layoutData(nullptr),
mp_vertexShader(nullptr),
mp_vertexLayout(nullptr)
{
}

OGL::VertexShader::~VertexShader()
{
	SAFE_DELETE_ARRAY(mp_layoutData);
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�C���v�b�g���C�A�E�g�̐����w�肵�܂��B
//������ ����1�FUINT�F�C���v�b�g���C�A�E�g�̐�
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::VertexShader::SetInputLayoutNum(UINT num)
{
	SAFE_DELETE_ARRAY(mp_layoutData);
	m_layoutum = num;
	mp_layoutData = new D3D11_INPUT_ELEMENT_DESC[num];
}

//��������������������������������������������
//�������@�@�\�F�C���v�b�g���C�A�E�g��ݒ肵�܂��B
//������ ����1�FUINT�F�ݒ肷��z��ӏ�
//������ ����2�Fchar*�F�Z�}���e�B�N�X��
//������ ����3�FUINT�F�ݒ肷��X���b�g�ӏ�
//������ ����4�FDXGI_FORMAT�F�ݒ肷�钸�_�̃t�H�[�}�b�g
//������ ����5�FUINT�F�Z�}���e�B�N�X�C���f�b�N�X(default�F0)(�d������Z�}���e�B�N�X��������ۂɕ��ʂ���ׂɎg�p)
//������ ����6�FUINT�F�o�C�g�I�t�Z�b�g(default�F0)
//������ ����7�FD3D11_INPUT_CLASSIFICATION�F�C���X�^���X�`�������ۂ�D3D11_INPUT_PER_INSTANCE_DATA���w��(default�FD3D11_INPUT_PER_VERTEX_DATA)
//������ ����8�FUINT�F�C���X�^���V���O���[�g(default�F0)
//������   �Ԓl�Fbool�Ftrue�c���� false�c���s
//��������������������������������������������
bool	OGL::VertexShader::SetInputLayoutData(UINT arrayNum, char* semanticName, UINT inputSlot, DXGI_FORMAT format,
	UINT semanticIndex, UINT byteOffset,
	D3D11_INPUT_CLASSIFICATION instanceFlg,UINT InstanceDataStepRate)
{
	if (m_layoutum < arrayNum)
	{
		ErrorMessage("VertexShader::SetInputLayoutData �ݒ肵�����C�A�E�g���𒴉߂��Ă��܂��BSetInputLayoutNum�ōĐݒ肵�ĉ������B");
		return false;
	}
	mp_layoutData[arrayNum].SemanticName = semanticName;
	mp_layoutData[arrayNum].SemanticIndex = semanticIndex;
	mp_layoutData[arrayNum].Format = format;
	mp_layoutData[arrayNum].InputSlot = inputSlot;
	mp_layoutData[arrayNum].AlignedByteOffset = byteOffset;
	mp_layoutData[arrayNum].InputSlotClass = instanceFlg;
	mp_layoutData[arrayNum].InstanceDataStepRate = InstanceDataStepRate;
	return true;
}

//��������������������������������������������
//�������@�@�\�F�V�F�[�_�[���R���p�C�����Z�b�e�B���O���܂��B
//������ ����1�Fchar*�F�V�F�[�_�[�t�@�C����
//������ ����2�Fchar*�F�R���p�C������֐���
//������ ����3�Fchar*�F�V�F�[�_�[�o�[�W����
//������   �Ԓl�Fbool�Ftrue�c���� false�c���s
//��������������������������������������������
bool	OGL::VertexShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("VertexShader::CreateShader ���_�V�F�[�_�̃R���p�C���Ɏ��s���܂����B");
		return false;
	}

	HRESULT hr = D3D11Device::GetDevice()->CreateVertexShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_vertexShader.GetAddressOf());
	if (FAILED(hr))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("VertexShader::CreateShader ���_�V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
		return false;
	}
	hr = D3D11Device::GetDevice()->CreateInputLayout(
		mp_layoutData,
		m_layoutum,
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		mp_vertexLayout.GetAddressOf());
	if (FAILED(hr))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("���_���C�A�E�g�̐����Ɏ��s���܂����B");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}