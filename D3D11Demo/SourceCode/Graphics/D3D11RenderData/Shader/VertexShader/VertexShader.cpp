//==========================
//===【VertexShader.cpp】
//==========================
//    DirectX11における
//    頂点シェーダーの管理を行います
//==========================

//=====================//
//===【インクルード記述】 ===//
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

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：インプットレイアウトの数を指定します。
//■■■ 引数1：UINT：インプットレイアウトの数
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::VertexShader::SetInputLayoutNum(UINT num)
{
	SAFE_DELETE_ARRAY(mp_layoutData);
	m_layoutum = num;
	mp_layoutData = new D3D11_INPUT_ELEMENT_DESC[num];
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：インプットレイアウトを設定します。
//■■■ 引数1：UINT：設定する配列箇所
//■■■ 引数2：char*：セマンティクス名
//■■■ 引数3：UINT：設定するスロット箇所
//■■■ 引数4：DXGI_FORMAT：設定する頂点のフォーマット
//■■■ 引数5：UINT：セマンティクスインデックス(default：0)(重複するセマンティクス名がある際に分別する為に使用)
//■■■ 引数6：UINT：バイトオフセット(default：0)
//■■■ 引数7：D3D11_INPUT_CLASSIFICATION：インスタンス描画をする際はD3D11_INPUT_PER_INSTANCE_DATAを指定(default：D3D11_INPUT_PER_VERTEX_DATA)
//■■■ 引数8：UINT：インスタンシングレート(default：0)
//■■■   返値：bool：true…成功 false…失敗
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::VertexShader::SetInputLayoutData(UINT arrayNum, char* semanticName, UINT inputSlot, DXGI_FORMAT format,
	UINT semanticIndex, UINT byteOffset,
	D3D11_INPUT_CLASSIFICATION instanceFlg,UINT InstanceDataStepRate)
{
	if (m_layoutum < arrayNum)
	{
		ErrorMessage("VertexShader::SetInputLayoutData 設定したレイアウト数を超過しています。SetInputLayoutNumで再設定して下さい。");
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

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：シェーダーをコンパイルしセッティングします。
//■■■ 引数1：char*：シェーダーファイル名
//■■■ 引数2：char*：コンパイルする関数名
//■■■ 引数3：char*：シェーダーバージョン
//■■■   返値：bool：true…成功 false…失敗
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::VertexShader::CreateShader(char* shaderFileName, char* functionName, char* profile)
{
	ID3DBlob *p_compiledShader = NULL;
	if (FAILED(CompileShader(&p_compiledShader, shaderFileName, functionName, profile)))
	{
		SAFE_RELEASE(p_compiledShader);
		ErrorMessage("VertexShader::CreateShader 頂点シェーダのコンパイルに失敗しました。");
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
		ErrorMessage("VertexShader::CreateShader 頂点シェーダーオブジェクトの生成に失敗しました。");
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
		ErrorMessage("頂点レイアウトの生成に失敗しました。");
		return false;
	}
	SAFE_RELEASE(p_compiledShader);
	return true;
}