#pragma once
#include "CommonClass.h"
#include "Resource.h"
//�I�u�W�F�N�g�ȊO�̃Q�[���̌����ڂ��ꊇ�Ǘ�����N���X
class GameMgr;

class C_View {
public:
	C_Graph Back_G;//�w�i�摜
	C_Graph Timer_G;
	C_Graph HpFrame_G;
	C_Graph HpBar_G;
	C_Font OldEng_F;
	void init();
	void Draw();
	void Draw2();
	void Process();

	GameMgr *mgr;
};

extern C_View View;