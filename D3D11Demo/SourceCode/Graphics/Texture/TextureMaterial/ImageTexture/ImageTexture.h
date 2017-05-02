//==========================
//===【ImageTexture.h】
//==========================
//    DirectX11における
//    画像ファイルを読み込んだテクスチャの管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"
#include<string>

namespace	OGL
{
	class	ImageTexture
	{

	public:
		bool	LoadFile(std::string fileName);
		bool	LoadFileArray(std::string* fileName, UINT fileNum);
		ID3D11ShaderResourceView*	GetSRV(void);
		void	Release(void);

	private:
		ID3D11ShaderResourceView*	mp_srv;

	public:
		ImageTexture();
		~ImageTexture();
	};	//EndOf__class_ImageTexture
}	//EndOf__namespace_OGL
