//==========================
//===�yBaseShader.h�z
//==========================
//    DirectX11�ɂ�����
//    �V�F�[�_�[���Ǘ�����N���X�̊��N���X�ł��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"

namespace	OGL
{
	class	BaseShader
	{
	public:
		BaseShader();
		virtual ~BaseShader();

		virtual bool	CreateShader(char* shaderFileName, char* functionName, char* profile) = 0;

	protected:
		HRESULT	CompileShader(ID3DBlob**	p_compileShader, char* shaderFileName, char* functionName, char* profile);
	};	//EndOf__class_BaseShader
}	//EndOf__namespace_OGL
