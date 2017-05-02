//==========================
//===【GameLoopManager.h】
//==========================
//    ゲームループの管理を行います。
//==========================
#pragma	once
#include<memory>
#include<thread>
#include"../../Timer/Timer.h"
#include"../GameScene/GameScene.h"
#include"../../GameLoop/GameScene/GameSceneList.h"

//=====================//
//===【インクルード記述】 ===//
//=====================//
namespace	OGL
{
	class	GameLoopManager
	{
	public:
		void	BeginGameLoopManager(float frameRate);
		void	EndGameLoopManager(void);

	private:
		bool	m_loopFlg;
		float	m_frameRate;
		GameScene*	mp_gameScene;
		Timer	m_loopTimer;
		std::thread	m_loopThread;

		void	LoopMain(void);

	public:
		static	GameLoopManager*	GetInstance(void)
		{
			static GameLoopManager	instance;
			return &instance;
		}
		virtual ~GameLoopManager();

	private:
		GameLoopManager();
		GameLoopManager(const GameLoopManager &hoge){};
		GameLoopManager &operator=(const GameLoopManager &){ return *this; }



	};	//EndOf__class_GameLoopManager
}	//EndOf__namespace_OGL
