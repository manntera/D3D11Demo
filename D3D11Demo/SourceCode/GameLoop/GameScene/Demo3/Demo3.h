//==========================
//===【Title.h】
//==========================
//    タイトル画面の管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../GameScene.h"
#include"../../../Graphics/RenderPackage/RPGBufferTessellation/RPGBufferTessellation.h"
#include"../../../Graphics/RenderPackage/RPDeferredLambert/RPDeferredLambert.h"

namespace	OGL
{
	class	Demo3:public GameScene
	{
	private:
		RPGBufferTessellation m_gBufferTessellation;
		RPDeferredLambert	m_defLam;

		ViewMatrix			m_view;
		WorldMatrix			m_world;
		CBPPointLight		m_pointLight;

		OutputTexture		m_outGBuffer;
		InputTexture		m_inDefLam;
		OutputTexture		m_outBackBuffer;

		BackBuffer			m_backBuffer;
		RenderTargetTexture	m_gBufferTex[3];
		DepthStencilTexture	m_depthStencilTex;

	public:
		static	Demo3*	GetInstance(void)
		{
			static std::unique_ptr<Demo3>	instance = nullptr;
			instance.reset(new Demo3);
			return instance.get();
		}
		virtual ~Demo3(){};
	public:
		void	Init(void);
		void	Update(void);
		void	Draw(void);
		void	Uninit(void);
	private:
		Demo3(){};
		Demo3(const Demo3 &hoge){};
		Demo3 &operator=(const Demo3 &){ return *this; }
	};	//EndOf__class_Demo3
}	//EndOf__namespace_OGL
