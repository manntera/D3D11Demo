//==========================
//===【PixelShader.cpp】
//==========================
//    DirectX11における
//    ピクセルシェーダーの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"PixelShader.h"

OGL::PixelShader::PixelShader():
mp_pixelShader(nullptr)
{
}

OGL::PixelShader::~PixelShader()
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
bool	OGL::PixelShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
//	SAFE_RELEASE_SP(mp_pixelShader);

	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("PixelShader::CreateShader ピクセルシェーダのコンパイルに失敗しました。");
		return false;
	}
	HRESULT hr = D3D11Device::GetDevice()->CreatePixelShader(
		p_compiledShader->GetBufferPointer(),
		p_compiledShader->GetBufferSize(),
		NULL,
		mp_pixelShader.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ピクセルシェーダーオブジェクトの生成に失敗しました。"), TEXT("Err"), MB_OK);
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("PixelShader::CreateShader ピクセルシェーダーオブジェクトの生成に失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}