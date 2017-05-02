//==========================
//===【ViewPort.cpp】
//==========================
//    DirectX11における
//    ビューポート設定の
//    管理・保持を行います
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"ViewPort.h"

OGL::ViewPort::ViewPort()
{
	D3D11_VIEWPORT temp;
	temp.TopLeftX = 0;
	temp.TopLeftY = 0;
	temp.Width = 0;
	temp.Height = 0;
	temp.MinDepth = 0.0f;
	temp.MaxDepth = 1.0f;
	mp_viewPort = std::make_shared<D3D11_VIEWPORT>(temp);
}

OGL::ViewPort::~ViewPort()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ビューポートの広さを設定します。
//■■■ 引数1：float：X開始地点(左方向の場所)
//■■■ 引数2：float：Y開始地点(上方向の場所)
//■■■ 引数3：float：幅
//■■■ 引数4：float：高さ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::ViewPort::SetRange(float topLeftX, float topLeftY, float Width, float height)
{
	mp_viewPort->TopLeftX = topLeftX;
	mp_viewPort->TopLeftY = topLeftY;
	mp_viewPort->Width = Width;
	mp_viewPort->Height = height;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：深度をの広さを設定します。
//■■■ 引数1：float：最小
//■■■ 引数2：float：最大
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::ViewPort::SetDepth(float min, float max)
{
	mp_viewPort->MinDepth = min;
	mp_viewPort->MaxDepth = max;
}
