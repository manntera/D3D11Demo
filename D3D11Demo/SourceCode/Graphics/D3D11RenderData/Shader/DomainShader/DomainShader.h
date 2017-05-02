//==========================
//===�yDomainShader.h�z
//==========================
//    DirectX11�ɂ�����
//    �h���C���V�F�[�_�[�̊Ǘ����s���܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../BaseShader/BaseShader.h"
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class D3D11RenderData;

	class	DomainShader :public BaseShader
	{
	public:
		bool	CreateShader(char* shaderFileName, char* functionName, char* profile);

	private:
		WRL::ComPtr<ID3D11DomainShader>	mp_domainShader;

	public:
		DomainShader();
		~DomainShader();

		friend D3D11RenderData;
	};	//EndOf__class_PixelShader
}	//EndOf__namespace_OGL
