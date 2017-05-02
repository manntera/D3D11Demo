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
#include"../../../Graphics/RenderPackage/RPLambertModel/RPLambertModel.h"
#include"../../../Graphics/RenderPackage/RPGBuffer/RPGBuffer.h"
#include"../../../Graphics/RenderPackage/RPDeferredLambert/RPDeferredLambert.h"
#include"../../../Graphics/RenderPackage/RPDepthBuffer/RPDepthBuffer.h"

namespace	OGL
{
	class	Demo1:public GameScene
	{
	private:
		RPDepthBuffer		m_RPshadow;
		RPGBuffer			m_gBuffer;
		RPDeferredLambert	m_defLam;

		ViewMatrix			m_shadowViewMat;
		ViewMatrix			m_view;
		WorldMatrix			m_world;
		ModelData			m_modelData;
		ModelData			m_stageData;
		CBPPointLight		m_pointLight;
		CBPSpotLight		m_spotLight;

		OutputTexture		m_shadowOutTex;
		OutputTexture		m_outGBuffer;
		InputTexture		m_inDefLam;
		OutputTexture		m_outBackBuffer;

		DepthStencilTexture	m_shadowDepthTex;
		BackBuffer			m_backBuffer;
		RenderTargetTexture	m_gBufferTex[3];
		DepthStencilTexture	m_depthStencilTex;

	public:
		static	Demo1*	GetInstance(void)
		{
			static std::unique_ptr<Demo1>	instance = nullptr;
			instance.reset(new Demo1);
			return instance.get();
		}
		virtual ~Demo1(){};
	public:
		void	Init(void);
		void	Update(void);
		void	Draw(void);
		void	Uninit(void);
	private:
		Demo1(){};
		Demo1(const Demo1 &hoge){};
		Demo1 &operator=(const Demo1 &){ return *this; }
	};	//EndOf__class_Demo1
}	//EndOf__namespace_OGL
