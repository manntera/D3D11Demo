//==========================
//===【HullShader.cpp】
//==========================
//    DirectX11における
//    ピクセルシェーダーの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"HullShader.h"

OGL::HullShader::HullShader() :
mp_hullShader(nullptr)
{
}

OGL::HullShader::~HullShader()
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
bool	OGL::HullShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("HullShader::CreateShader ハルシェーダのコンパイルに失敗しました。");
		return false;
	}
	HRESULT hr = D3D11Device::GetDevice()->CreateHullShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_hullShader.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ハルシェーダーオブジェクトの生成に失敗しました。"), TEXT("Err"), MB_OK);
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("HullShader::CreateShader ハルシェーダーオブジェクトの生成に失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}