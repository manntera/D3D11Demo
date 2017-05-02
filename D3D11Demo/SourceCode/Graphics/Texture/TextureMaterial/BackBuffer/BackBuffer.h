//==========================
//===�yBackBuffer.h�z
//==========================
//    DirectX11�ɂ�����
//    �o�b�N�o�b�t�@���Ǘ����܂��B
//==========================
#pragma	once
#include"../../../D3D11Device/D3D11Device.h"

//=====================//
//===�y�C���N���[�h�L�q�z ===//
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
