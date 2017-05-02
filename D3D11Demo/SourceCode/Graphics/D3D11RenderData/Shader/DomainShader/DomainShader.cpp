//==========================
//===【DomainShader.cpp】
//==========================
//    DirectX11における
//    ドメインシェーダーの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"DomainShader.h"

OGL::DomainShader::DomainShader() :
mp_domainShader(nullptr)
{
}

OGL::DomainShader::~DomainShader()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：シェーダーをコンパイルしセッティングします。
//■■■ 引数1：char*：シェーダーファイル名
//■■■ 引数2：char*：コンパイルする関数名
//■■■ 引数3：char*：シェーダーバージョン
//■■■   返値：bool：true…成功 false…失敗
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DomainShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("DomainShader::CreateShader ドメインシェーダのコンパイルに失敗しました。");
		return false;
	}
	HRESULT hr = D3D11Device::GetDevice()->CreateDomainShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_domainShader.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ドメインシェーダーオブジェクトの生成に失敗しました。"), TEXT("Err"), MB_OK);
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("DomainShader::CreateShader ドメインシェーダーオブジェクトの生成に失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}