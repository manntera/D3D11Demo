//==========================
//===�yRasterizerState.h�z
//==========================
//    DirectX11�ɂ�����
//    ���X�^���C�U�X�e�[�g�̊Ǘ����s���܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class D3D11RenderData;

	class	RasterizerState
	{
	public:
		enum ROTATORY_FRONT_MODE
		{
			LEFT_ROTATORY_FRONT,
			RIGHT_ROTATORY_FRONT,
		};

		bool	SetWireFrameEnable(bool enable);
		bool	SetCullMode(D3D11_CULL_MODE mode);
		bool	SetRotatoryFrontMode(ROTATORY_FRONT_MODE mode);
		bool	SetDepthBias(int depthBias=0, float depthBiasClamp=0, float slopeScaledDepthBias=0);
		bool	SetDepthClippingEnable(bool enable);
		bool	SetMultisampleEnable(bool enable);
		bool	SetAntialiasedLineEnable(bool enable);

		bool	Create(void);

	private:
		D3D11_RASTERIZER_DESC	m_desc;
		WRL::ComPtr<ID3D11RasterizerState>	mp_state;

	public:
		RasterizerState();
		~RasterizerState();

		friend D3D11RenderData;
	};	//EndOf__class_RasterizerState
}	//EndOf__namespace_OGL
