//==========================
//===【BaseShader.cpp】
//==========================
//    DirectX11における
//    シェーダーを管理するクラスの基底クラスです。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"BaseShader.h"

OGL::BaseShader::BaseShader()
{
}

OGL::BaseShader::~BaseShader()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■//
//■■■【private】■■■//
//■■■■■■■■■■■■//
HRESULT	OGL::BaseShader::CompileShader(ID3DBlob**	p_compileShader, char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_errors = NULL;

	HRESULT hr = D3DX11CompileFromFile(
		shaderFileName,
		NULL,
		NULL,
		functionName,
		profile,
		D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		p_compileShader,
		&p_errors,
		NULL);
	if (FAILED(hr))
	{
		char* errorCode = (char*)p_errors->GetBufferPointer();
		MessageBox(NULL, TEXT(errorCode), TEXT("Err"), MB_OK);
		SAFE_RELEASE(p_errors);
		ErrorMessage("BaseShader::CompileShader シェーダーのコンパイルに失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_errors);
	return true;
}
