//==========================
//===ÅyD3D11RenderManager.hÅz
//==========================
//    DirectX11Ç…Ç®ÇØÇÈ
//    ï`âÊê›íËÇÃä«óùÇçsÇ¢Ç‹Ç∑ÅB
//==========================
#pragma	once
//=====================//
//===ÅyÉCÉìÉNÉãÅ[ÉhãLèqÅz ===//
//=====================//
#include"../D3D11Device/D3D11Device.h"
#include"../D3D11RenderData/D3D11RenderData.h"
#include"../Texture/ShaderTexture/InputTexture/InputTexture.h"
#include"../Texture/ShaderTexture/OutputTexture/OutputTexture.h"
#include"../ConstantBuffer/ConstantBuffer.h"
#include"../ModelData/IndexBuffer/IndexBuffer.h"
#include"../ModelData/VertexBuffer/VertexBuffer.h"

namespace	OGL
{	
	class D3D11RenderData;
	class InputTexture;
	class OutputTexture;
	class ConstantBuffer;
	class VertexBuffer;
	class IndexBuffer;

	class	D3D11RenderManager
	{
	public:
		static	void	SetRenderData(D3D11RenderData* data);
		static	void	SetIndexBuffer(IndexBuffer* buff);
		static	void	SetVertexBuffer(VertexBuffer* buff, UINT slot);
		static	void	SetVsConstantBuffer(ConstantBuffer* buffer,UINT slot);
		static	void	SetHsConstantBuffer(ConstantBuffer* buffer, UINT slot);
		static	void	SetDsConstantBuffer(ConstantBuffer* buffer, UINT slot);
		static	void	SetGsConstantBuffer(ConstantBuffer* buffer, UINT slot);
		static	void	SetPsConstantBuffer(ConstantBuffer* buffer, UINT slot);
		static	void	SetVsInputTexture(InputTexture* inputTex);
		static	void	SetHsInputTexture(InputTexture* inputTex);
		static	void	SetDsInputTexture(InputTexture* inputTex);
		static	void	SetGsInputTexture(InputTexture* inputTex);
		static	void	SetPsInputTexture(InputTexture* inputTex);
		static	void	SetOutputTexture(OutputTexture* outputTex);
		static	void	ClearVsInputTexture(InputTexture* inputTex);
		static	void	ClearHsInputTexture(InputTexture* inputTex);
		static	void	ClearDsInputTexture(InputTexture* inputTex);
		static	void	ClearGsInputTexture(InputTexture* inputTex);
		static	void	ClearPsInputTexture(InputTexture* inputTex);
		static	void	ClearOutputTexture(OutputTexture* outputTex);
		static	void	Draw(UINT drawIndexCount,UINT startIndexOffset,int addIndex);

	private:
		D3D11RenderManager();
	public:
		~D3D11RenderManager();
	};	//EndOf__class_D3D11RenderManager
}	//EndOf__namespace_OGL
