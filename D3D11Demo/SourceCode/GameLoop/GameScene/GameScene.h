//==========================
//===�yGameScene.h�z
//==========================
//    �Q�[���̖{�̏������L�q���܂��B
//    ���̃N���X���p�����Ďg�p���ĉ�����
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include<memory>

namespace	OGL
{
	class GameScene
	{
	public:
		GameScene();
		virtual ~GameScene();
		GameScene(const GameScene &hoge){};
		GameScene &operator=(const GameScene &){ return *this; }
	public:
		GameScene* nextScene;
		virtual	void	Init(void)=0;
		virtual	void	Update(void) = 0;
		virtual	void	Draw(void) = 0;
		virtual	void	Uninit(void) = 0;
		GameScene*	GetNextScene(void);
	protected:
	};	//EndOf__class_GameLoop
}	//EndOf__namespace_OGL
