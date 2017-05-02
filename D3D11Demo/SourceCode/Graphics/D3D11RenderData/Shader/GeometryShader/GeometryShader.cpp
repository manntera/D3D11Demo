//==========================
//===【GeometryShader.cpp】
//==========================
//    DirectX11における
//    ジオメトリシェーダーの管理を行います
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"GeometryShader.h"

OGL::GeometryShader::GeometryShader()
{
}

OGL::GeometryShader::~GeometryShader()
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
bool	OGL::GeometryShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("GeometryShader::CreateShader ジオメトリシェーダのコンパイルに失敗しました。");
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
		ErrorMessage("GeometryShader::CreateShader ジオメトリシェーダーオブジェクトの生成に失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}
