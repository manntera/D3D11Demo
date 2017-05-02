//==========================
//===【Demo0.h】
//==========================
//    タイトル画面の管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../GameScene.h"
#include"../../../Graphics/RenderPackage/RPLambertModel/RPLambertModel.h"
#include"../../../Graphics/RenderPackage/RPGaussFilter/RPGaussFilter.h"
#include"../../../Graphics/RenderPackage/RPGBuffer/RPGBuffer.h"

namespace	OGL
{
	class	Demo0:public GameScene
	{
	private:
		RPLambertModel	m_RPLambert;
		RPGaussFilter		m_GaussFilter;
	
		ViewMatrix			m_view;
		WorldMatrix			m_world;
		ModelData			m_modelData;
		ModelData			m_stageData;
		CBPPointLight		m_pointLight;

		OutputTexture		m_OutLambert;
		InputTexture		m_InGauss;
		OutputTexture		m_OutBackBuffer;

		BackBuffer			m_backBuffer;
		RenderTargetTexture	m_rtv;
		DepthStencilTexture	m_depthStencilTex;

	public:
		static	Demo0*	GetInstance(void)
		{
			static std::unique_ptr<Demo0>	instance = nullptr;
			instance.reset(new Demo0);
			return instance.get();
		}
		virtual ~Demo0(){};
	public:
		void	Init(void);
		void	Update(void);
		void	Draw(void);
		void	Uninit(void);
	private:
		Demo0(){};
		Demo0(const Demo0 &hoge){};
		Demo0 &operator=(const Demo0 &){ return *this; }
	};	//EndOf__class_Demo0
}	//EndOf__namespace_OGL
