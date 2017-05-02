//==========================
//===【InputTexture.cpp】
//==========================
//    Shaderに読み込ませるTextureを保持します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"InputTexture.h"

OGL::InputTexture::InputTexture()
{
}

OGL::InputTexture::~InputTexture()
{
}
//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：ImageTexture*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::InputTexture::SetTexture(ImageTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：ImageTexture*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::InputTexture::SetTexture(RenderTargetTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：ImageTexture*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::InputTexture::SetTexture(DepthStencilTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//■■■■■■■■■■■■//
//■■■【private】 ■■■//
//■■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：inputDataにShaderResourceをセットします。
//■■■ 引数1：ID3D11ShaderResourceView*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::InputTexture::SetSrv(ID3D11ShaderResourceView* srv, int slot)
{
	if (slot<0||slot >= D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
	{
		ErrorMessage("InputTexture::SetSrv 設定されたスロットは範囲外です。");
		return false;
	}
	if (srv == nullptr)
	{
		ErrorMessage("InputTexture::SetSrv シェーダーリソースビューが指定されていません。");
		return false;
	}

	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		if (inputData[i].slot == slot)
		{
			inputData[i].p_srv = srv;
			return true;
		}
	}
	T_srvData temp;
	temp.p_srv = srv;
	temp.slot = slot;
	inputData.push_back(temp);
	return true;
}