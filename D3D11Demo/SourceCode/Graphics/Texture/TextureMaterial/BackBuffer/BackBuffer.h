//==========================
//===【BackBuffer.h】
//==========================
//    DirectX11における
//    バックバッファを管理します。
//==========================
#pragma	once
#include"../../../D3D11Device/D3D11Device.h"

//=====================//
//===【インクルード記述】 ===//
//=====================//
namespace	OGL
{
	class	BackBuffer
	{
	public:
		bool	Create(void);
		void	Clear(float r, float g, float b, float a);
		void	Release(void);
		ID3D11RenderTargetView*	GetRTV(void);

	private:
		ID3D11RenderTargetView*		mp_backBufferView;

	public:
		BackBuffer();
		~BackBuffer();
	};	//EndOf__class_BackBuffer
}	//EndOf__namespace_OGL
