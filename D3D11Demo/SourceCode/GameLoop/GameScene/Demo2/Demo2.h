//==========================
//===【Demo2.h】
//==========================
//    ゲーム本体画面の管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../GameScene.h"
#include"../../../Graphics/D3D11RenderManager/D3D11RenderManager.h"
#include"../../../Graphics/RenderPackage/RPRect/RPRect.h"

namespace	OGL
{
	class	Demo2 :public GameScene
	{
	private:
		D3D11RenderData		m_renderData;
		ConstantBuffer			m_windowScale;
		InputTexture			m_inputTexture;
		ImageTexture			m_imageTexture;
		BackBuffer				m_backBuffer;
		OutputTexture			m_outPutTexture;
		IndexBuffer				m_indexBuffer;
		VertexBuffer			m_rectBuffer;
		VertexBuffer			m_colorBuffer;
		VertexBuffer			m_uvBuffer;

		RPRect					m_rpRect;
	public:
		static	Demo2*	GetInstance(void)
		{
			static std::unique_ptr<Demo2>	instance=nullptr;
			instance.reset(new Demo2);
			return instance.get();
		}
		virtual ~Demo2(){};
	public:
		void	Init(void);
		void	Update(void);
		void	Draw(void);
		void	Uninit(void);
	private:
		Demo2(){};
		Demo2(const Demo2 &hoge){};
		Demo2 &operator=(const Demo2 &){ return *this; }
	};	//EndOf__class_Title
}	//EndOf__namespace_OGL
