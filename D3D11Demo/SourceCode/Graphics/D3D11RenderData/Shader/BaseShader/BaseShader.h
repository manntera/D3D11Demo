//==========================
//===【BaseShader.h】
//==========================
//    DirectX11における
//    シェーダーを管理するクラスの基底クラスです。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
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
